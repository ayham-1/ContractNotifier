#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QString>
#include "ui_settings.h"
#include "lib/db.h"

namespace Ui {
    class settingsWin;
}

class settingsWindow : public QMainWindow, private Ui::settingsWin {
    Q_OBJECT

public:
    explicit settingsWindow(DB *db, QWidget *parent = nullptr);
    ~settingsWindow();

private slots:
    void on_closeBtn_clicked();
    void on_helpBtn_clicked();
    void on_applyBtn_clicked();

private:
    DB* _db;
};

#endif // MAINWINDOW_H
