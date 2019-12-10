#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace Ui {
    class mainWin;
}

class MainWindow : public QMainWindow, private Ui::mainWin {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    
};

#endif // MAINWINDOW_H
