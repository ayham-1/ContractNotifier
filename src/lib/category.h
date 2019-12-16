#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include "contract.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

struct Category {
    std::string _name;
    std::string _desc;
    std::vector<Contract> _contracts;

    friend bool operator==(const Category &lhs, const Category &rhs) {
        if (lhs._name == rhs._name &&
                lhs._desc == rhs._desc &&
                lhs._contracts == rhs._contracts)
            return true;
        else return false;
    }

    template<typename Archive>
        void serialize(Archive & ar, const unsigned int version) {
            ar & _name;
            ar & _desc;
            ar & _contracts;
    }
};

static auto category_removeContract(Category &category, Contract &item) -> void {
    // Search for the item to remove.
    for (int i = 0; i < category._contracts.size(); i++) {
        if (category._contracts[i] == item) {
            category._contracts.erase(category._contracts.begin()+i);
            break;
        }
    }
}

static auto category_addContract(Category &category, Contract item) -> void {
    // Check if the item is not already in Category.
    for (auto i : category._contracts)
        if (i == item)
            return;

    // Add the contract.
    category._contracts.push_back(item);
}

static auto category_moveContract(Category &src, Category &dest, Contract &item) -> void {
    // Check if the item is in dest.
    for (auto i : dest._contracts)
        if (i == item)
            return;

    // Copy the contract to local var.
    auto local = Contract{item};

    // Find the index of contract in src.
    int index = 0;
    for (; index < src._contracts.size(); index++)
        if (src._contracts[index] == item) break;

    // Remove the contract from src.
    src._contracts.erase(src._contracts.begin()+index);

    // Add the contract to dest.
    dest._contracts.push_back(local);
}

static auto category_getContract(Category &category, std::string _name) -> Contract* {
    for (int i = 0; i < category._contracts.size(); i++)
        if (category._contracts[i]._name == _name)
            return &category._contracts[i];
    return nullptr;
}

#endif
