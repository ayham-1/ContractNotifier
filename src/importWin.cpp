#include "importWin.h"
#include "mainwindow.h"

importWindow::importWindow(DB *db,QWidget *parent)
    : QMainWindow(parent), _db(db) {
        setupUi(this);
}

importWindow::~importWindow() {
}

auto importWindow::on_closeBtn_clicked() -> void {
    this->close();
}
auto importWindow::on_importBtn_clicked() -> void {
    import_db_as_db(*(this->_db), this->locationBox->text().toUtf8().constData());
    this->close();
}
auto importWindow::on_browseBtn_clicked() -> void {
    QString dirname = QFileDialog::getOpenFileName(this,
            "Import", "", "*.db");
    this->locationBox->setText(dirname);
    ((MainWindow*)(this->parent()))->listDB();
    this->close();
}
