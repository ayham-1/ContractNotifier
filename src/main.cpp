#include "mainwindow.h"
#include <QApplication>
#include "lib/contract.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Contract contract;
    QDate date;
    date = QDate::currentDate();
    contract_setExpiry(contract, date);
    QDate date1;
    date1 = contract_getExpiry(contract);

    std::cout << contract._expiry;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
