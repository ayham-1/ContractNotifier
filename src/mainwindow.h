#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include "ui_mainwindow.h"
#include "settingsWin.h"
#include "exportWin.h"

namespace Ui {
    class mainWin;
}

class MainWindow : public QMainWindow, private Ui::mainWin {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_closeBtn_clicked();
    void on_settingsBtn_clicked();
    //void onDeleteBtn_clicked();
    //void onInfoBtn_clicked();
    void closeEvent(QCloseEvent *event) override;
    void on_actionExport_triggered();

private:
    void checkDB(); // Does checks and notifies.
    bool closing = false;
    
    DB _db;
};

#endif // MAINWINDOW_H
