#ifndef INFO_WIN_H
#define INFO_WIN_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QString>
#include <string>
#include "ui_info.h"
#include "lib/contract.h"

namespace Ui {
    class contractInfoWin;
}

class infoWindow : public QMainWindow, private Ui::contractInfoWin {
    Q_OBJECT

public:
    explicit infoWindow(DB *db, Contract *contract, std::string category, QWidget *parent = nullptr);
    ~infoWindow();

private slots:
    void on_closeBtn_clicked();
    void on_applyBtn_clicked();

private:
    Contract *_contract;
    std::string _category;
    DB *_db;
};

#endif // INFO_WIN_H
