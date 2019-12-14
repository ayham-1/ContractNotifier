#include "exportWin.h"

exportWindow::exportWindow(DB *db,QWidget *parent)
    : QMainWindow(parent), _db(db) {
        setupUi(this);
}

exportWindow::~exportWindow() {
}

auto exportWindow::on_closeBtn_clicked() -> void {
    this->close();
}
auto exportWindow::on_exportBtn_clicked() -> void {
    export_db_as_db(*(this->_db), this->locationBox->text().toUtf8().constData());
    this->close();
}
auto exportWindow::on_browseBtn_clicked() -> void {
    QString dirname = QFileDialog::getSaveFileName(this,
            "Export", "", "*.db");
    this->locationBox->setText(dirname);
}
