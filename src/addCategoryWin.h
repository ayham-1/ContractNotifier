#ifndef ADDCATEGORY_WIN_H
#define ADDCATEGORY_WIN_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QString>
#include <QFileDialog>
#include "ui_addCategory.h"
#include "lib/db.h"
#include "lib/contract.h"
#include "lib/category.h"

namespace Ui {
    class addCategoryWin;
}

class addCategoryWindow : public QMainWindow, private Ui::addCategoryWin {
    Q_OBJECT

public:
    explicit addCategoryWindow(DB *db, QWidget *parent = nullptr);
    ~addCategoryWindow();

private slots:
    void on_closeBtn_clicked();
    void on_addBtn_clicked();

private:
    DB* _db;
};

#endif // ADDCATEGORY_WIN_H
