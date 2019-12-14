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

    _db._deactivatedCategory._name = "Expired";
    _db._deactivatedCategory._desc = "Permanent Category";

    this->listDB();
}

MainWindow::~MainWindow() {
    export_db_as_db(_db, "db.db");
}

auto MainWindow::listDB() -> void {
    this->treeView->clear();
    auto t = new QTreeWidgetItem(QStringList() << "DB");
    for (auto category : _db._categories) {
        auto cattop = new QTreeWidgetItem(QStringList() << category._name.c_str());
        for (auto contract : category._contracts) {
            auto item = new QTreeWidgetItem(QStringList() << contract._name.c_str());
            cattop->addChild(item);
        }
        t->addChild(cattop);
    }
    auto deactive = new QTreeWidgetItem(QStringList() << "Expired");
    t->addChild(deactive);
    this->treeView->addTopLevelItem(t);
    this->treeView->expandItem(t);
};

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

auto MainWindow::on_infoBtn_clicked() -> void {
    if (this->_selectedContract) {
        infoWindow *win = new infoWindow(&_db, _selectedContract, _selectedCategoryName, this);
        win->show();
    }
    else if (this->_selectedCategory) {
        categoryInfoWindow *win = new categoryInfoWindow(_selectedCategory, this);
        win->show();
    }
}

auto MainWindow::on_treeView_itemClicked() -> void {
    // Reset state.
    this->_selectedContract = nullptr;
    this->_selectedCategory = nullptr;
    this->infoBtn->setEnabled(false);
    this->deleteBtn->setEnabled(false);   

    // Get item selected
    auto item = this->treeView->currentItem()->text(0);

    // Check if item name is a contract name.
    for (int i = 0; i < _db._categories.size(); i++) {
        Category *category = &_db._categories[i];
        if (item != QString::fromStdString(category->_name)) {
            // Iterate over contracts.
            for (int j = 0; j < category->_contracts.size(); j++) {
                Contract *contract = &category->_contracts[i];
                if (item == QString::fromStdString(contract->_name)) {
                    // It's a contract.
                    this->_selectedContract = contract;
                    this->_selectedCategoryName = category->_name;
                    this->infoBtn->setEnabled(true);
                    this->deleteBtn->setEnabled(true);
                }
            }
        }
        else {
            // It's a category.
            this->_selectedCategory = category;
            this->infoBtn->setEnabled(true);
            this->deleteBtn->setEnabled(true);       
        }
    }
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

