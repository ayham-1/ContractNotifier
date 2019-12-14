#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
        setupUi(this);

        auto exitAction = new QAction(tr("Exit"), this);
        auto trayIconMenu = new QMenu(this);
        trayIconMenu->addAction(exitAction);

        auto sysTrayIcon = new QSystemTrayIcon(this);
        sysTrayIcon->setContextMenu(trayIconMenu);
        sysTrayIcon->setIcon(QIcon("icon.png"));
        sysTrayIcon->show();
        connect(exitAction, &QAction::triggered, [this]() {
                closing = true;
                close();
                });
        connect(sysTrayIcon, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason) {
                if(reason == QSystemTrayIcon::Trigger) {
                if(isVisible()){
                hide();
                }
                else{
                show();
                activateWindow();}}});

    Category category;
    category._name = "All";
    category._desc = "Default Category";
    _db._categories.push_back(category);
}

MainWindow::~MainWindow() {
    export_db_as_db(_db, "db.db");
}

auto MainWindow::closeEvent(QCloseEvent *event) -> void {
        if(closing) {
            event->accept();
        }
        else {
            this->hide();
            event->ignore();
        }
}

auto MainWindow::on_closeBtn_clicked() -> void {
    hide();
}

auto MainWindow::on_settingsBtn_clicked() -> void {
    settingsWindow *win = new settingsWindow(&_db, this);
    win->show();
}

auto MainWindow::on_actionExport_triggered() -> void {
    exportWindow *win = new exportWindow(&_db, this);
    win->show();
}

auto MainWindow::on_actionImport_triggered() -> void {
    importWindow *win = new importWindow(&_db, this);
    win->show();
}

auto MainWindow::on_actionAdd_Contract_triggered() -> void {
    addContractWindow *win = new addContractWindow(&_db, this);
    win->show();
    export_db_as_db(_db, "db.db");
}

auto MainWindow::on_actionAdd_Category_triggered() -> void {
    addCategoryWindow *win = new addCategoryWindow(&_db, this);
    win->show();
    export_db_as_db(_db, "db.db");
}

