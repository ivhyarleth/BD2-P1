//
#include "sequentialfile.h"
//#include "extensiblehashing.h"
//
#include "parser.h"
#include "time.h"
#include <iomanip>
using namespace std;

int main() {

    ios_base::sync_with_stdio(false); 
    clock_t start, end; 
    Parser parser("sales-records.csv",100);
    auto sale_records = parser.get_sale_records();

    SequentialFile<SaleRecord> sequientialfile1("data-temp.dat");
    SaleRecord record1 ((char*)"Alemania", (char*)"uno", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    SaleRecord record2 ((char*)"Brasil", (char*)"dos", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    SaleRecord record3 ((char*)"Colombia", (char*)"tres", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    SaleRecord record4 ((char*)"Dinamarca", (char*)"cuatro", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    
    //sequientialfile1.add_record(record2);
    //sequientialfile1.add_record(record3);
    //sequientialfile1.add_record(record4);
    start = clock(); 
    sequientialfile1.insert_all(*sale_records);
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "El tiempo que tarda el programa es: " << std::fixed  
         << time_taken / 1000 << setprecision(4) << " ms " << endl;
    //sequientialfile1.delete_record(13);
    //sequientialfile1.delete_record(11);
    //sequientialfile1.delete_record(17);
    sequientialfile1.print_all();
    //sequientialfile1.print_sorted();


    /*____________________________________________*/
    /*Hash<SaleRecord> extensibleHash ("data-temp2.dat");
    start = clock(); 
    SaleRecord record1 ((char*)"Alemania", (char*)"uno", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    SaleRecord record2 ((char*)"Brasil", (char*)"dos", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    SaleRecord record3 ((char*)"Colombia", (char*)"tres", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    SaleRecord record4 ((char*)"Dinamarca", (char*)"cuatro", (char*)"item_type", (char*)"channel", (char*)"01/02/2000", (char*)"01/02/2000", (char*)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    SaleRecord record7((char *)"Eslovenia", (char *)"cinco", (char *)"item_type", (char *)"channel", (char *)"01/02/2000", (char *)"01/02/2000", (char *)"123456", 500, 345.2, 234.3, 1231.2, 1345.3, 324235.3);
    extensibleHash.insert(record1, record1.country);
    extensibleHash.insert(record2, record2.country);
    extensibleHash.insert(record3, record3.country);
    extensibleHash.insert(record4, record4.country);
    extensibleHash.insert(record7, record4.country);
    extensibleHash.printTable();
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "El tiempo que tarda el programa es: " << std::fixed  
          << time_taken / 1000 << setprecision(4) << " ms " << endl;
    SaleRecord result1 = extensibleHash.search(record3.country);
    cout << result1.country << endl;
    

    // extensibleHash.remove(record3.country);
    // extensibleHash.remove(record4.country);
    // extensibleHash.insert(record7, record7.country);
    // SaleRecord result2 = extensibleHash.search(record7.country);
    // cout << result2.country << endl;*/

    return 0;
};