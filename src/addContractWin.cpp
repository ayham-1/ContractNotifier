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
    // Get category.
    for (int i = 0; i < _db->_categories.size(); i++) {
        Category* category = &_db->_categories[i];
        if (category->_name == this->categoryBox->currentText().toUtf8().constData()) {
            // Make contract.
            Contract contract;
            contract._name = this->nameBox->text().toUtf8().constData();
            contract._desc = this->descBox->text().toUtf8().constData();
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
