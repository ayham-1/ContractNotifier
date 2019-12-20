#include <iostream>
#include <cstdio>
#include <ctime>
#include "lib/notify.h"
#include "lib/db.h"
#include "lib/export.h"
#include "lib/import.h"

#define DB_CNT 1000000
#define RND_CNT 1000

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

    std::cout << "Making list of " << DB_CNT << " contracts." << std::endl;
    start = std::clock();
    db_makeList(db);
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Made list of " << DB_CNT << " contracts in " << duration << std::endl;

    std::cout << "Searching for last contract." << std::endl;
    start = std::clock();
    db_search_sort(db, std::to_string(DB_CNT-1));
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Searching for last contract too: " << duration << std::endl;

    double total_duration;
    for (int i = 0; i < RND_CNT; i++) {
        int random = rand()%((DB_CNT-1)-0 + 1) + 0;
        std::cout << "Searching for random contract number: " << random << std::endl;
        start = std::clock();
        db_search_sort(db, std::to_string(random));
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Searching for random contract took: " << duration << std::endl;
        total_duration += duration;
    }
    std::cout << "Average search time: " << total_duration / RND_CNT << std::endl;

    return 0;
}
