#include "mainwindow.h"
#include <QApplication>
#include "lib/contract.h"
#include "lib/category.h"
#include "lib/db.h"
#include "lib/export.h"
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

    export_db_as_db(db, "db.db");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
