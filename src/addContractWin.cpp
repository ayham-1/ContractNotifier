#include "addContractWin.h"
#include "mainwindow.h"

addContractWindow::addContractWindow(DB *db,QWidget *parent)
    : QMainWindow(parent), _db(db) {
        setupUi(this);
        // Load categories.
        for (auto i : _db->_categories) {
            this->categoryBox->addItem(QString::fromStdString(i._name));
        }
}

addContractWindow::~addContractWindow() {
}

auto addContractWindow::on_closeBtn_clicked() -> void {
    this->close();
}

auto addContractWindow::on_addBtn_clicked() -> void {
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
    // Get category.
    for (int i = 0; i < _db->_categories.size(); i++) {
        Category* category = &_db->_categories[i];
        if (category->_name == this->categoryBox->currentText().toUtf8().constData()) {
            // Make contract.
            Contract contract;
            contract._name = this->nameBox->text().toStdString();
            contract._desc = this->descBox->text().toStdString();
            contract._notify_from_months = this->notifyMonthsVal->value();
            contract._notify_from_days = this->notifyDaysVal->value();
            contract_setExpiry(contract, this->expiryDate->date());

            // Add contract.
            category_addContract(*category, contract);
            break;
        }
    }
    ((MainWindow*)(this->parent()))->updateDB();
    db_makeList(*(this->_db));
    this->close();
}
