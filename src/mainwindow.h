#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <thread>
#include <mutex>

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTreeWidgetItem>
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

namespace Ui {
    class mainWin;
}

class MainWindow : public QMainWindow, private Ui::mainWin {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void listDB();
private slots:
    void on_closeBtn_clicked();
    void on_infoBtn_clicked();
    void on_settingsBtn_clicked();
    //void onDeleteBtn_clicked();
    void closeEvent(QCloseEvent *event) override;
    void on_treeView_itemClicked();
    void on_actionExport_triggered();
    void on_actionImport_triggered();
    void on_actionAdd_Contract_triggered();
    void on_actionAdd_Category_triggered();
    void on_actionInfo_triggered();

private:
    void checkDB(); // Does checks and notifies.
    bool closing = false;
    
    DB _db;

    Contract *_selectedContract = nullptr;
    Category *_selectedCategory = nullptr;
    std::string _selectedCategoryName = "";

    std::thread* _checkingThread = nullptr;
};

#endif // MAINWINDOW_H
