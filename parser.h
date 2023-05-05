#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <sstream>
#include <algorithm>
#include "salerecord.h"

using namespace std;

class Parser {
    vector<SaleRecord>* sale_records;
    SaleRecord* create_sale_record(const string& info) {
        vector<string> fields;
        stringstream ss(info);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        SaleRecord* sale_record;
        if (fields.size() == 13) {
            string country = fields[0];
            string region = fields[1];   
            string item_type = fields[2];
            string channel = fields[3];
            string order_date = fields[4];
            string ship_date = fields[5];
            string order_id = fields[6];
            unsigned int units_sold = stoi(fields[7]);
            double unit_price = stod(fields[8]);
            double unit_cost = stod(fields[9]);
            long double total_revenue = stold(fields[10]);
            long double total_cost = stold(fields[11]);
            long double total_profit = stold(fields[12]);
            
            sale_record = new SaleRecord(country, region, item_type, channel, 
                order_date, ship_date, order_id, units_sold, unit_price, unit_cost, 
                total_revenue, total_cost, total_profit);
        }
        return sale_record;
    }
public:
    Parser(const string& file_name, int cant_records){ 
        sale_records = new vector<SaleRecord>();
        fstream* file = new fstream(file_name, ios::in);

        if (!file)
            cout << "No se pudo abrir el archivo" << file_name << endl;

        string line;
        getline(*file, line);
        int recordCount = 0; // Contador de registros leídos
        while (getline(*file, line) && recordCount < cant_records) {
            SaleRecord* rec_temp = create_sale_record(line);
            sale_records->push_back(*rec_temp);
            recordCount++;
        }
        file->close();
        delete file;
    };

    ~Parser(){
        delete sale_records;
    };

    vector<SaleRecord>* get_sale_records() const{
        string filename("data-temp.dat");
        string filename("data-temp2.dat");
        fstream outfile;
        outfile.open(filename, ios_base::out);
        return sale_records;
    }

};
