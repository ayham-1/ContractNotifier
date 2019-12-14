#include "addCategoryWin.h"

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
    // Make category
    Category category;
    category._name = this->nameBox->text().toUtf8().constData();
    category._desc = this->descBox->text().toUtf8().constData();
    _db->_categories.push_back(category);
    this->close();
}
