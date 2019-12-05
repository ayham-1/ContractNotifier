#include "mainwindow.h"
#include <QApplication>
#include "lib/contract.h"
#include "lib/category.h"
#include "lib/db.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    Contract contract;
    QDate date;
    date = QDate::currentDate();
    contract_setExpiry(contract, date);

    Category category;
    category._name = "khello";
    category._desc = "this is a desc";
    category._contracts.push_back(contract);

    DB db;
    db._categories.push_back(category);
    db._notifier_email = "lol@gmail.com";

    std::ofstream ofs("filename");
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << category;
        // archive and stream closed when destructors are called
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
