#ifndef APPINFO_H
#define APPINFO_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QString>
#include "ui_appinfo.h"

namespace Ui {
    class appInfoWin;
}

class appInfoWindow : public QMainWindow, private Ui::appInfoWin {
    Q_OBJECT

public:
    explicit appInfoWindow(QWidget *parent = nullptr);
    ~appInfoWindow();

private slots:
    void on_closeBtn_clicked();

private:
};

#endif // INFO_WIN_H
