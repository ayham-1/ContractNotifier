#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>
#include <ctime>
#include <QDate>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#define DATE_FORMAT "dd/MM/yyyy"

struct Contract {
    std::string _name = "";
    std::string _desc = "";
    std::string _expiry = "";
    int _notify_from_months = 0;
    int _notify_from_days = 0;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & _name;
        ar & _desc;
        ar & _expiry;
        ar & _notify_from_months;
        ar & _notify_from_days;
    }
};

auto contract_getExpiry(const Contract &contract) -> QDate {
    return (QDate::fromString(QString::fromStdString(contract._expiry), DATE_FORMAT));
}

auto contract_setExpiry(Contract &contract, QDate date) -> void {
    contract._expiry = date.toString(DATE_FORMAT).toUtf8().constData();
}


#endif
