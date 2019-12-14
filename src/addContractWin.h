#ifndef ADDCNTRCT_WIN_H
#define ADDCNTRCT_WIN_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QString>
#include <QFileDialog>
#include "ui_addContract.h"
#include "lib/db.h"
#include "lib/contract.h"
#include "lib/category.h"

namespace Ui {
    class addContractWin;
}

class addContractWindow : public QMainWindow, private Ui::addContractWin {
    Q_OBJECT

public:
    explicit addContractWindow(DB *db, QWidget *parent = nullptr);
    ~addContractWindow();

private slots:
    void on_closeBtn_clicked();
    void on_addBtn_clicked();

private:
    DB* _db;
};

#endif // EXPORTWIDNOW_H
