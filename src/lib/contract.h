#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>
#include <QDate>

struct Contract {
    std::string _name;
    std::string _desc;
    QDate _expiry;
    int _notify_from_months;
    int _notify_from_days;
};

#endif
