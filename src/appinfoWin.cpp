#include "settingsWin.h"
#include "mainwindow.h"

appInfoWindow::appInfoWindow(QWidget *parent)
    : QMainWindow(parent) {
        setupUi(this);
}

appInfoWindow::~appInfoWindow() {
}

auto appInfoWindow::on_closeBtn_clicked() -> void {
    this->close();
}
