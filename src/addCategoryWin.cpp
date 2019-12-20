#include "addCategoryWin.h"
#include "mainwindow.h"

addCategoryWindow::addCategoryWindow(DB *db,QWidget *parent)
    : QMainWindow(parent), _db(db) {
        setupUi(this);
}

addCategoryWindow::~addCategoryWindow() {
}

auto addCategoryWindow::on_closeBtn_clicked() -> void {
    this->close();
}

auto addCategoryWindow::on_addBtn_clicked() -> void {
    // Check if name is empty.
    if (this->nameBox->text().toStdString() == "") {
        QMessageBox msgBox;
        msgBox.setText("Name of contract can not be empty!");
        msgBox.exec();
        return;
    }   
    // Check if name is already there.
    if (!db_isNameAvaliable(*_db, this->nameBox->text().toStdString())) {
        QMessageBox msgBox;
        msgBox.setText("Name is already taken!");
        msgBox.exec();
        return;
    }

    // Make category
    Category category;
    category._name = this->nameBox->text().toUtf8().constData();
    category._desc = this->descBox->text().toUtf8().constData();
    _db->_categories.push_back(category);
    ((MainWindow*)(this->parent()))->updateDB();
    db_makeList(*(this->_db));
    this->close();
}
