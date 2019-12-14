#ifndef IMPORTWIN_H
#define IMPORTWIN_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QString>
#include <QFileDialog>
#include "ui_import.h"
#include "lib/db.h"
#include "lib/import.h"

namespace Ui {
    class importWin;
}

class importWindow : public QMainWindow, private Ui::importWin {
    Q_OBJECT

public:
    explicit importWindow(DB *db, QWidget *parent = nullptr);
    ~importWindow();

private slots:
    void on_closeBtn_clicked();
    void on_importBtn_clicked();
    void on_browseBtn_clicked();

private:
    DB* _db;
};

#endif // IMPORTWIDNOW_H
