#ifndef CATEGORYINFO_WIN_H
#define CATEGORYINFO_WIN_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QString>
#include <QFileDialog>
#include "ui_categoryInfo.h"
#include "lib/category.h"

namespace Ui {
    class categoryInfoWin;
}

class categoryInfoWindow : public QMainWindow, private Ui::categoryInfoWin {
    Q_OBJECT

public:
    explicit categoryInfoWindow(Category *category, QWidget *parent = nullptr);
    ~categoryInfoWindow();

private slots:
    void on_closeBtn_clicked();
    void on_applyBtn_clicked();

private:
    Category* _category;
};

#endif // CATEGORYINFO_WIN_H
