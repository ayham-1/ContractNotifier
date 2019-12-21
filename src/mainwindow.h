#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <thread>
#include <mutex>
#include <fstream>

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QThread>
#include "lib/notify.h"
#include "ui_mainwindow.h"
#include "settingsWin.h"
#include "exportWin.h"
#include "importWin.h"
#include "addContractWin.h"
#include "addCategoryWin.h"
#include "infoWin.h"
#include "categoryInfoWin.h"
#include "appinfoWin.h"
#include "dbchecker.h"

namespace Ui {
    class mainWin;
}

class MainWindow : public QMainWindow, private Ui::mainWin {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_closeBtn_clicked();
    void on_infoBtn_clicked();
    void on_settingsBtn_clicked();
    void on_deleteBtn_clicked();
    void closeEvent(QCloseEvent *event) override;
    void on_treeView_itemClicked(QTreeWidgetItem* _item, int column);
    void on_searchBox_textChanged(const QString &text);
    void on_clearBtn_clicked();
    void on_actionExport_triggered();
    void on_actionImport_triggered();
    void on_actionAdd_Contract_triggered();
    void on_actionAdd_Category_triggered();
    void on_actionInfo_triggered();
    void on_actionSettings_triggered();
    void on_actionExit_triggered();

    void listDB();
    void updateDB();
private:
    bool closing = false;
    bool need_update = false;
    
    DB _db;

    Contract *_selectedContract = nullptr;
    Category *_selectedCategory = nullptr;
    std::string _selectedCategoryName = "";

    DBChecker* _checker = nullptr;
    std::thread *_checkingThread = nullptr;
};
#endif // MAINWINDOW_H
