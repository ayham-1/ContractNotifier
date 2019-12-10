#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include "ui_mainwindow.h"

namespace Ui {
    class mainWin;
}

class MainWindow : public QMainWindow, private Ui::mainWin {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCloseBtn_clicked();
    //void onSettingsBtn_clicked();
    //void onDeleteBtn_clicked();
    //void onInfoBtn_clicked();
    void closeEvent(QCloseEvent *event) override;

private:
    void checkDB(); // Does checks and notifies.
    bool closing = false;
};

#endif // MAINWINDOW_H
