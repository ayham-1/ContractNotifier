#include "mainwindow.h"
#include <QApplication>
#include "lib/contract.h"
#include "lib/category.h"
#include "lib/db.h"
#include "lib/export.h"
#include "lib/import.h"
#include "lib/notify.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    Contract contract;
    QDate date;
    date = QDate::currentDate();
    date = date.addDays(2);
    contract_setExpiry(contract, date);
    contract._name = "akham";
    contract._desc = "This is akham";
    contract._notify_from_months = 0;
    contract._notify_from_days = 2;

    Category category;
    category._name = "khello";
    category._desc = "this is a desc";
    category._contracts.push_back(contract);

    DB db;
    db._categories.push_back(category);
    db._notifier_email = "ayhamaboualfadl@gmail.com";

    export_db_as_db(db, "db.db");
    notify_check(db, false, true);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
