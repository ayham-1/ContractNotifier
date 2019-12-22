#ifndef DBCHECKER_H
#define DBCHECKER_H

#include <iostream>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <thread>
#include "lib/db.h"
#include "lib/notify.h"

class DBChecker : public QObject {
    Q_OBJECT

public:
        explicit DBChecker(DB *db, QObject *parent = 0) : QObject(parent), _db(db) {}    

        void setClosing(bool val) {closing = val;}
        void checkDBthread();
        void checkDBiter();
signals:    
        void checkDBepoch();

private:
        DB *_db;
        bool closing = false;
};
#endif // DBCHECKER_H
