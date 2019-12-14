#ifndef EXPORTWIN_H
#define EXPORTWIN_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QString>
#include <QFileDialog>
#include "ui_export.h"
#include "lib/db.h"
#include "lib/export.h"

namespace Ui {
    class exportWin;
}

class exportWindow : public QMainWindow, private Ui::exportWin {
    Q_OBJECT

public:
    explicit exportWindow(DB *db, QWidget *parent = nullptr);
    ~exportWindow();

private slots:
    void on_closeBtn_clicked();
    void on_exportBtn_clicked();
    void on_browseBtn_clicked();

private:
    DB* _db;
};

#endif // EXPORTWIDNOW_H
