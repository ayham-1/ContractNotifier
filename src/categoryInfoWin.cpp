#include "categoryInfoWin.h"
#include "mainwindow.h"

categoryInfoWindow::categoryInfoWindow(Category *category,QWidget *parent)
    : QMainWindow(parent), _category(category) {
        setupUi(this);

        this->nameBox->setText(QString::fromStdString(category->_name));
        this->descBox->setText(QString::fromStdString(category->_desc));
}

categoryInfoWindow::~categoryInfoWindow() {
}

auto categoryInfoWindow::on_closeBtn_clicked() -> void {
    this->close();
}

auto categoryInfoWindow::on_applyBtn_clicked() -> void {
    _category->_name = this->nameBox->text().toUtf8().constData();
    _category->_desc = this->descBox->text().toUtf8().constData();
    ((MainWindow*)(this->parent()))->updateDB();
}
