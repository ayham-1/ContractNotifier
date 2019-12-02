#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>
#include <vector>
#include "contract.h"

struct Category {
    std::string _name;
    std::string _desc;
    std::vector<Contract> _contracts;

    auto operator==(const Category &lhs, const Category &rhs) -> bool {
        if (lhs._name == rhs._name &&
                lhs._desc == rhs._desc &&
                lhs._contracts == rhs._contracts)
            return true;
        else return false;
    }
};

auto category_removeContract(Category &category, Contract &item) -> void {
    // Search for the item to remove.
    for (int i = 0; i < category._contracts.size(); i++) {
        if (category._contracts[i] == item) {
            category._contracts.erase(category._contracts.begin()+i);
            break;
        }
    }
    throw std::runtime_error("Contract to remove does not exist.");
}

auto category_addContract(Category &category, Contract item) -> void {
    // Check if the item is not already in Category.
    for (auto i : category._contracts) {
        if (i == item) {
            throw std::runtime_error("Contract already exists.");
        }
    }

    // Add the contract.
    category._contracts.push_back(item);
}

auto category_moveContract(Category &src, Category &dest, Contract &item) -> void {
    // Check if the item is in dest.
    // TODO: Decide whether it is hard or soft check.
    for (auto i : dest._contracts) {
        if (i == item) {
            throw std::runtime_error("Contract already exists in destination.");
        }
    }

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

auto category_getContract(Category &category, std::string _name) -> Contract& {
    for (auto item : category._contracts)
        if (item._name = _name)
            return item;
    throw std::runtime_error("Contract does not exist.");
}

#endif
