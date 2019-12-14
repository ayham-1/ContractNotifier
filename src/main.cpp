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
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
