#ifndef DB_H
#define DB_H

#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include "contract.h"
#include "category.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

struct DB {
    std::vector<Category> _categories;
    Category _deactivatedCategory;
    std::string _notifier_email = "";
    bool _notify_by_email = true;
    bool _notify_by_notify = true;
    std::vector<Contract*> *_contractList = nullptr;

    template<typename Archive>
        void serialize(Archive & ar, const unsigned int version) {
            ar & _notifier_email;
            ar & _notify_by_email;
            ar & _notify_by_notify;
            ar & _deactivatedCategory;
            ar & _categories;
        }
};

static auto db_search_getCorrectness(const std::string &str, const Contract &contract) -> int {
    int val = 0;
    if (contract._name.size() < str.size())
        for (auto c : contract._name)
            if (c == str[val]) val++;
    else if (contract._name.size() > str.size())
        for (auto c : str)
            if (c == contract._name[val++]) val++;
    return val;
}

static auto db_search_sort(DB &db, const std::string &str) -> void {
    std::stable_sort(db._contractList->begin(), db._contractList->end(), [=](const Contract *l, const Contract *r) -> bool {return db_search_getCorrectness(str, *l)>db_search_getCorrectness(str, *r);});
}

static auto db_makeList(DB &db) -> void {
    std::mutex mtx;
    mtx.lock();
    // Make the list
    if (!db._contractList)
        db._contractList = new std::vector<Contract*>();
    db._contractList->clear();

    // Iterate over deactivated category.
    for (int i = 0; i < db._deactivatedCategory._contracts.size(); i++)
        db._contractList->push_back(&db._deactivatedCategory._contracts[i]);
    // Iterate over categories.
    for (int i = 0; i < db._categories.size(); i++)
        for (int j = 0; j < db._categories[i]._contracts.size(); j++)
            db._contractList->push_back(&db._categories[i]._contracts[j]);

    // Sort the list.
    std::stable_sort(db._contractList->begin(), db._contractList->end(), [=](const Contract *l, const Contract *r) -> bool {return l->_name[0]>r->_name[0];});
    mtx.unlock();
}

static auto db_cleanList(DB &db) -> void {
    delete db._contractList;
}

static auto  db_addCategory(DB &db, Category &item) -> void {
    // Check if category is already present.
    for (auto i : db._categories)
        if (i == item)
            return;

    // Add the category.
    db._categories.push_back(item);
}

static auto db_removeCategory(DB &db, Category &item) -> void {
    // Search for the item to remove.
    for (int i = 0; i < db._categories.size(); i++)
        if (db._categories[i] == item) {
            db._categories.erase(db._categories.begin()+i);
            break;
        }
}

#endif
