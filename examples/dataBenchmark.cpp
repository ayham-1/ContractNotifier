#include <iostream>
#include <cstdio>
#include <ctime>
#include "lib/notify.h"
#include "lib/db.h"
#include "lib/export.h"
#include "lib/import.h"

#define DB_CNT 1000000

int main() {
    std::clock_t start;
    double duration;

    DB db;
    Category category;
    category._name = "All";
    category._desc = "Default Category";
    db._categories.push_back(category);

    std::cout << "Making " << DB_CNT << " contracts" << std::endl;
    start = std::clock();
    for (int i = 0; i < DB_CNT; i++) {
        Contract contract;
        contract._name = std::to_string(i);
        contract._desc = "This is an average description.";
        contract._expiry = "01/01/2000";
        contract._notify_from_months = 3;
        contract._notify_from_days = 15;
        db._categories[0]._contracts.push_back(contract);
    }
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Made " <<  DB_CNT << " contracts in " << duration << "s" << std::endl;
    std::cout << "Size of " << DB_CNT << " contracts: " << sizeof(db) << " bytes" << std::endl;

    std::cout << "Saving " << DB_CNT << " contracts." << std::endl;
    start = std::clock();
    export_db_as_db(db, "db.db");
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Saved " << DB_CNT <<  " contracts in " << duration << "s" << std::endl;

    std::cout << "Reading " << DB_CNT << " contracts." << std::endl;
    start = std::clock();
    import_db_as_db(db, "db.db");
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Read " << DB_CNT << " contracts in " << duration << "s" << std::endl;

    return 0;
}
