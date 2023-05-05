#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct SaleRecord {
    char country[35];
    char region[35];
    char item_type[20];
    char channel[8];
    char order_date[12];
    char ship_date[12];
    char order_id[12];
    unsigned int units_sold;
    double unit_price;
    double unit_cost;
    long double total_revenue;
    long double total_cost;
    long double total_profit;

    SaleRecord(){};

    SaleRecord(char country[35], char region[35], char item_type[20], 
    char channel[8], char order_date[12], char ship_date[12], char order_id[12],
    unsigned int units_sold, double unit_price, double unit_cost, 
    long double total_revenue, long double total_cost, long double total_profit) {
        strcpy(this->country, country);
        strcpy(this->region, region);
        strcpy(this->item_type, item_type);
        strcpy(this->channel, channel);
        strcpy(this->order_date, order_date);
        strcpy(this->ship_date, ship_date);
        strcpy(this->order_id, order_id);
        this->units_sold = units_sold;
        this->unit_price = unit_price;
        this->unit_cost = unit_cost;
        this->total_revenue = total_revenue;
        this->total_cost = total_cost;
        this->total_profit = total_profit;
    }
};

struct Bucket
{
    int size;
    int local_depth;
    Bucket* next_bucket;
    vector<pair<string, long>> registros;
    string name;
    Bucket(){};
};

template <typename R>
class Hash{
    private:
        unordered_map<string, Bucket*> hash;
        fstream archData;
        string archDataName;
        int max_global_depth;
        int global_depth;
        int block_factor;
        int cont_split;
    public:
        Hash(string dataName)
        {
            archDataName = dataName;
            cout << "Inserte factor de bloque: ";
            cin >> block_factor;
            cout << "Inserte maximo de nivel global: ";
            cin >> max_global_depth;
            global_depth = 1;
            Bucket* zero = new Bucket();
            Bucket* one = new Bucket();
            zero->next_bucket = nullptr;
            one->next_bucket = nullptr;
            zero->size = 0;
            one->size = 0;
            zero->local_depth = 1;
            one->local_depth = 1;
            zero->name = "0";
            one->name = "1";
            hash["0"] = zero;
            hash["1"] = one;
        }
        
        void insert(R registro, string key){
            fstream removedData;
            removedData.open("eliminados.dat", ios::binary | ios::in);
            long address = -1;
            int size = 0;
            if (removedData.is_open())
            {
                removedData.seekg(0, ios::end);
                size = (int)removedData.tellg();
                removedData.seekg(0, ios::beg);
            }
            if (size > 0){
                cout << "holi" << endl;
                int valid = 0;
                int cont =-1;
                while (valid == 0 & !removedData.eof())
                {
                    removedData.read((char *)&address, sizeof(address));
                    removedData.read((char *)&valid, sizeof(valid));
                    cont++;
                }
                if (valid != 0){
                    valid = 0;
                    removedData.close();
                    removedData.open("eliminados.dat", ios::binary | ios::out);
                    removedData.seekg(cont * (sizeof(long) + sizeof(int)) + sizeof(long));
                    removedData.write((char *)&valid, sizeof(valid));
                    archData.open(archDataName, ios::binary | ios::in);
                    archData.seekg(address);
                }
                cout << size << " " << address << endl;
            }
            if (size == 0 || address == -1) {
                archData.open(archDataName, ios::binary | ios::app);
                address = archData.tellp();
            }
            archData.write((char *)&registro, sizeof(registro));
            archData.close();
            removedData.close();
            string hashCode = hashing(key);
            string newHash;
            Bucket* bucket;
            int contDepth = 0;
            bool encontrado = false;
            while (contDepth < global_depth && !encontrado)
            {
                contDepth++;
                newHash = hashCode.substr(hashCode.length() - contDepth);
                if (hash.find(newHash) != hash.end())
                {
                    bucket = hash[newHash];
                    encontrado = true;
                }
            }
            while (bucket->next_bucket != nullptr)
            {
                bucket = bucket->next_bucket;
            }
            if (bucket->size < block_factor){
                bucket->size = bucket->size + 1;
                bucket->registros.push_back(make_pair(hashCode, address));
                cout << "se inserto en " << bucket->name << endl;
            }
            else
            {
                bool inserted = false;
                while (bucket->local_depth < max_global_depth && !inserted)
                {
                    Bucket *newBucket = new Bucket();
                    newBucket->local_depth = ++bucket->local_depth;
                    newBucket->next_bucket = nullptr;
                    string baseHash = bucket->name;
                    string hashToReallocate;
                    string newHash0 = "0" + baseHash;
                    string newHash1 = "1" + baseHash;
                    for (int i = 0; i < bucket->size; i++)
                    {
                        hashToReallocate = bucket->registros[i].first;
                        if (hashToReallocate.substr(hashToReallocate.length() - bucket->local_depth) == newHash1){
                            newBucket->registros.push_back(bucket->registros[i]);
                            bucket->registros.erase(bucket->registros.begin() + i);
                            bucket->size--;
                            newBucket->size++;
                        }
                    }
                    bucket->name = newHash0;
                    newBucket->name = newHash1;
                    hash.erase(baseHash);
                    hash[newHash0] = bucket;
                    hash[newHash1] = newBucket;
                    cont_split++;
                    if (global_depth < bucket->local_depth){
                        global_depth++;
                    }
                    string newHashCode = hashCode.substr(hashCode.length() - bucket->local_depth);
                    auto bucketToInsert = hash[newHashCode];
                    if (bucketToInsert->size < block_factor)
                    {
                        inserted = true;
                        bucketToInsert->registros.push_back(make_pair(hashCode, address));
                        cout << "se inserto en " << bucketToInsert->name << endl;
                        return;
                    }
                }
                if (!inserted){
                    Bucket *newBucket = new Bucket();
                    newBucket->local_depth = bucket->local_depth;
                    newBucket->next_bucket = nullptr;
                    newBucket->size = 1;
                    newBucket->registros.push_back(make_pair(hashCode, address));
                    newBucket->name = bucket->name + "+";
                    cout << "se inserto en " << newBucket->name << endl;
                    bucket->next_bucket = newBucket;
                }
            }
        };

        string hashing(string key){
            //convierte la cadena a 0, 1,01, 001,
            int suma;
            for (int i = 0; i < key.length(); i++){
                suma += (int)key[i];
            }
            string hashCode;
            for (int i = 0; suma > 0; i++)
            {    
                hashCode += to_string(suma%2);    
                suma = suma/2;  
            }
            return hashCode;
        };

        void remove(string key){
            string hashCode = hashing(key);
            bool encontrado = false;
            int contDepth = 0;
            string prevHash;
            Bucket *bucket;
            while (contDepth < global_depth && !encontrado)
            {
                contDepth++;
                prevHash = hashCode.substr(hashCode.length() - contDepth);
                if (hash.find(prevHash) != hash.end())
                {
                    bucket = hash[prevHash];
                    encontrado = true;
                }
            }
            fstream removedData;
            removedData.open("eliminados.dat", ios::binary | ios::app);
            Bucket *prevBucket;
            bool overflow = false;
            bool deleted = false;
            pair<string, long> registro;
            while (bucket->next_bucket != nullptr && !deleted)
            {
                prevBucket = bucket;
                int i = 0;
                while(i < bucket->registros.size() && !deleted){
                    registro = bucket->registros[i];
                    if (registro.first == hashCode)
                    {
                        bucket->registros.erase(bucket->registros.begin() + i);
                        if (bucket->size == 1){
                            if (overflow){
                                prevBucket->next_bucket = nullptr;
                                delete bucket;
                            } else {
                                string newHash = prevHash.substr(1, prevHash.size() - 1);
                                string indexToRemove = (prevHash[0] == '0') ? "1" + newHash : "0" + newHash;
                                prevBucket = hash[indexToRemove];
                                hash.erase(indexToRemove);
                                hash.erase(prevHash);
                                prevBucket->local_depth--;
                                hash[newHash] = prevBucket;
                                cont_split--;
                                if (cont_split == 0)
                                {
                                    global_depth--;
                                }
                            }
                        }
                        bucket->size--;
                        deleted = true;
                    }
                    i++;
                }
                overflow = true;
                bucket = bucket->next_bucket;
            }
            if (removedData){
                int valid = 1;
                cout << registro.second << endl;
                removedData.write((char *)&registro.second, sizeof(long));
                removedData.write((char *)&valid, sizeof(int));
            }
            removedData.close();
        }
        
        R search(string key){
            R registro;
            string hashCode = hashing(key);
            bool encontrado = false;
            int contDepth = 0;
            string hashToSearch;
            Bucket *bucket;
            while (contDepth < global_depth && !encontrado)
            {
                contDepth++;
                hashToSearch = hashCode.substr(hashCode.length() - contDepth);
                if (hash.find(hashToSearch) != hash.end())
                {
                    bucket = hash[hashToSearch];
                    encontrado = true;
                }
            }
            encontrado = false;
            while (bucket->next_bucket != nullptr) {
                int i = 0;
                while (i < bucket->registros.size() && !encontrado)
                {
                    if (bucket->registros[i].first == hashCode)
                    {
                        archData.open(archDataName, ios::binary | ios::in);
                        archData.seekg(bucket->registros[i].second);
                        archData.read((char *)&registro, sizeof(registro));
                        encontrado = true;
                        archData.close();
                        return registro;
                    }
                    i++;
                }
                if (!encontrado){
                    bucket = bucket->next_bucket;
                }
            }
            cerr << "No se encontro el registro" << endl;
            return registro;
        };

        void printTable() {
            cout << "Índice     País" << endl;
            for (auto it = hash.begin(); it != hash.end(); it++) {
                auto bucket = it->second;
                for (auto registro : bucket->registros) {
                    cout << registro.second;
                    cout << registro.first << "     " << registro.second << endl;
                }
                while (bucket->next_bucket != nullptr) {
                    bucket = bucket->next_bucket;
                    for (auto registro : bucket->registros) {
                        cout << registro.first << "     " << registro.second << endl;
                    }
                }
            }
        }

};