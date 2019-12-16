#include "settingsWin.h"
#include "mainwindow.h"

infoWindow::infoWindow(DB *db, Contract *contract,std::string category, QWidget *parent)
    : QMainWindow(parent), _contract(contract), _db(db), _category(category) {
        setupUi(this);
        this->nameBox->setText(QString::fromStdString(contract->_name));
        this->descBox->setText(QString::fromStdString(contract->_desc));
        this->notifyMonthsVal->setValue(contract->_notify_from_months);
        this->notifyDaysVal->setValue(contract->_notify_from_days);
        this->expiryDate->setDate(contract_getExpiry(*contract));
        if (contract->_expired)
            this->isExpired->setCheckState(Qt::Checked);
        else 
            this->isExpired->setCheckState(Qt::Unchecked);

        for (auto i : _db->_categories)
            this->categoryBox->addItem(QString::fromStdString(i._name));

        this->categoryBox->setCurrentText(QString::fromStdString(category));
}

infoWindow::~infoWindow() {
}

auto infoWindow::on_closeBtn_clicked() -> void {
    this->close();
}

auto infoWindow::on_applyBtn_clicked() -> void {
    this->_contract->_name = this->nameBox->text().toUtf8().constData();
    this->_contract->_desc = this->descBox->text().toUtf8().constData();
    contract_setExpiry(*this->_contract, this->expiryDate->date());
    this->_contract->_notify_from_months = this->notifyMonthsVal->value();
    this->_contract->_notify_from_days = this->notifyDaysVal->value();

    // Get original category.
    Category *categorySrc = nullptr;
    if (_category == "Expired") categorySrc = &_db->_deactivatedCategory;
    else
        for (int i = 0; i < _db->_categories.size(); i++)
            if (_category  == _db->_categories[i]._name) {
                // Found the category.
                categorySrc = &_db->_categories[i];
                break;
            }
    // Get destination category.
    auto category_name = this->categoryBox->currentText().toUtf8().constData();
    Category *categoryDest = nullptr;
    if (_category == "Expired") categorySrc = &_db->_deactivatedCategory;
    else
        for (int i = 0; i < _db->_categories.size(); i++)
            if (category_name == _db->_categories[i]._name) {
                // Found the category.
                categoryDest = &_db->_categories[i];
                break;
            }

    category_moveContract(*categorySrc, *categoryDest, *_contract);

    ((MainWindow*)(this->parent()))->updateDB();
    this->close();
}
