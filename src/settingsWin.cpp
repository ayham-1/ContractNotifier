#include "settingsWin.h"
#include "mainwindow.h"

settingsWindow::settingsWindow(DB *db,QWidget *parent)
    : QMainWindow(parent), _db(db) {
        setupUi(this);
        this->emailBox->setText(QString::fromStdString(db->_notifier_email));
        if (db->_notify_by_email)
            this->notifyByEmail->setCheckState(Qt::Checked);
        else 
            this->notifyByEmail->setCheckState(Qt::Unchecked);
        if (db->_notify_by_notify)
            this->notifyByNotify->setCheckState(Qt::Checked);
        else 
            this->notifyByNotify->setCheckState(Qt::Unchecked);
}

settingsWindow::~settingsWindow() {
}

auto settingsWindow::on_closeBtn_clicked() -> void {
    this->close();
}
auto settingsWindow::on_helpBtn_clicked() -> void {
    // TODO: Make help
}
auto settingsWindow::on_applyBtn_clicked() -> void {
    // Save the data.
    std::string email = this->emailBox->text().toUtf8().constData();
    _db->_notifier_email = email;

    if (this->notifyByEmail->checkState() == Qt::Checked)
        _db->_notify_by_email = true;
    else _db->_notify_by_email = false;
    if (this->notifyByNotify->checkState() == Qt::Checked)
        _db->_notify_by_notify = true;
    else _db->_notify_by_notify = false;
    ((MainWindow*)(this->parent()))->updateDB();
    this->close();
}
