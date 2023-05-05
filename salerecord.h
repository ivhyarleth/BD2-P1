#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

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

    int pos;
    char page;
    int next;
    int prev;
    int next_del;

    SaleRecord();
    SaleRecord(char[], char[], char[], char[], char[], char[], char[],
        unsigned int, double, double, long double, long double, long double);
    SaleRecord(string, string, string, string, string, string, string,
        unsigned int, double, double, long double, long double, long double);
    void print_headers();
    void print_info(int, char);
};

SaleRecord::SaleRecord() { }

SaleRecord::SaleRecord(char country[35], char region[35], char item_type[20], 
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
        next_del = 0;
    }

SaleRecord::SaleRecord(string country, string region, string item_type, string channel, 
    string order_date, string ship_date, string order_id,
    unsigned int units_sold, double unit_price, double unit_cost, 
    long double total_revenue, long double total_cost, long double total_profit) {
        strcpy(this->country, country.c_str());
        strcpy(this->region, region.c_str());
        strcpy(this->item_type, item_type.c_str());
        strcpy(this->channel, channel.c_str());
        strcpy(this->order_date, order_date.c_str());
        strcpy(this->ship_date, ship_date.c_str());
        strcpy(this->order_id, order_id.c_str());
        this->units_sold = units_sold;
        this->unit_price = unit_price;
        this->unit_cost = unit_cost;
        this->total_revenue = total_revenue;
        this->total_cost = total_cost;
        this->total_profit = total_profit;
        next_del = 0;
    }

void SaleRecord::print_headers() {
    cout << left << setw(35) << "ID\tCOUNTRY";
    ////cout << left << setw(35) << "\tREGION";
    //cout << left << setw(20) <<  "\tITEM_TYPE";
    ////cout << left << setw(8) << "\tCHANNEL";
    //cout << left << setw(10) << "\tORDER_DATE";
    ////cout << left << setw(10) << ship_date << "\t";
    //cout << left << setw(12) << "\tORDER_ID";
    //cout << left << setw(5) << "\tUSOLD";
    //cout << left << setw(5) << "\tUPRICE";
    //cout << left << setw(5) << "\tUCOST";
    //cout << left << setw(11) << "\tTOTAL_REV";
    //cout << left << setw(11) << "\tTOTA_COST";
    //cout << left << setw(11) << "\tTOTAL_PROFIT";
    cout << left << setw(3) << "\tNEXT";
    cout << left << setw(3) << "\tPREV";
    cout << left << setw(3) << "\tNEXTDEL" << endl;
}

void SaleRecord::print_info(int count, char page) {
    cout << count << page << "\t"
         << left << setw(35) << country << "\t"
         ////<< left << setw(35) << region << "\t"
         //<< left << setw(20) << item_type << "\t"
         ////<< left << setw(8) << channel << " \t"
         //<< left << setw(10) << order_date << "\t"
         ////<< left << setw(10) << ship_date << "\t"
         //<< left << setw(12) << order_id << "\t"
         //<< left << setw(5) << units_sold << "\t"
         //<< left << setw(5) << unit_price << "\t"
         //<< left << setw(5) << unit_cost << "\t"
         //<< left << setw(11) << total_revenue << "\t"
         //<< left << setw(11) << total_cost << "\t"
         //<< left << setw(11) << total_profit << "\t"    
         << next << page << "\t"
         << prev << page << "\t"
         << next_del << page << endl;
}