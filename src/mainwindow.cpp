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
                this->_checker->setClosing(true);
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

        // Try to load from db.db file
        std::ifstream f("db.db");
        if (f.good())
            import_db_as_db(_db, "db.db");
        else {
            Category category;
            category._name = "All";
            category._desc = "Default Category";
            _db._categories.push_back(category);

            _db._deactivatedCategory._name = "Expired";
            _db._deactivatedCategory._desc = "Permanent Category"; 
        }
        this->_checker = new DBChecker(&_db);
        f.close();
        this->updateDB();

        // Spawn checking thread.
        this->_checkingThread = new std::thread(&DBChecker::checkDBthread, this->_checker);
        connect(this->_checker, SIGNAL(checkDBepoch()), this, SLOT(updateDB()));

        this->treeView->setSelectionMode(QAbstractItemView::SingleSelection);

        db_makeList(this->_db);
}

MainWindow::~MainWindow() {
    db_cleanList(this->_db);
    this->_checker->setClosing(true);
    export_db_as_db(_db, "db.db");
    exit(0);
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
    for (auto item : _db._deactivatedCategory._contracts)
        deactive->addChild(new QTreeWidgetItem(QStringList() << item._name.c_str()));
    t->addChild(deactive);
    this->treeView->addTopLevelItem(t);
    this->treeView->expandItem(t);
};

auto MainWindow::on_searchBox_textChanged(const QString &text) -> void {
    auto str = text.toStdString();
    if (str == "") {
        this->listDB();
    }
    else {
        db_search_sort(this->_db, str);
        // Print contract list to screen.
        this->treeView->clear();
        auto t = new QTreeWidgetItem(QStringList() << "Search Results");
        for (auto contract : *(this->_db._contractList)) {
            auto item = new QTreeWidgetItem(QStringList() << contract->_name.c_str());
            t->addChild(item);
        }
        this->treeView->addTopLevelItem(t);
        this->treeView->expandItem(t);
    }
}

auto MainWindow::on_clearBtn_clicked() -> void {
    this->searchBox->clear();
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
auto MainWindow::on_actionExit_triggered() -> void {
    this->close();
}

auto MainWindow::on_closeBtn_clicked() -> void {
    hide();
    this->updateDB();
}

auto MainWindow::on_settingsBtn_clicked() -> void {
    settingsWindow *win = new settingsWindow(&_db, this);
    win->show();
}

auto MainWindow::on_actionSettings_triggered() -> void {
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

auto MainWindow::on_deleteBtn_clicked() -> void {
    // Get item selected
    auto item = this->treeView->currentItem()->text(0).toStdString();

    // Check if it is the expired category.
    if (item == "Expired") {
       QMessageBox msgBox;
       msgBox.setText("Can't delete the expired category.");
       msgBox.exec();
    }

    // Check if it is a category.
    for (int i = 0; i < _db._categories.size(); i++)
        if (item == _db._categories[i]._name)
            db_removeCategory(_db, _db._categories[i]);

    // Check if it is in expired category.
    for (int i = 0; i < _db._deactivatedCategory._contracts.size(); i++)
        if (item == _db._deactivatedCategory._contracts[i]._name) {
            category_removeContract(_db._deactivatedCategory, _db._deactivatedCategory._contracts[i]);
            break;
        }

    // Check which category it is.
    for (int i = 0; i < _db._categories.size(); i++)
        for (int j = 0; j < _db._categories[i]._contracts.size(); j++)
            if (item == _db._categories[i]._contracts[j]._name) {
                category_removeContract(_db._categories[i], _db._categories[i]._contracts[j]);
                break;
            }

    this->updateDB();
    db_makeList(this->_db);
}

auto MainWindow::on_treeView_itemClicked(QTreeWidgetItem* _item, int col) -> void {
    // Reset state.
    this->_selectedContract = nullptr;
    this->_selectedCategory = nullptr;
    this->_selectedCategoryName = "";
    this->infoBtn->setEnabled(false);
    this->deleteBtn->setEnabled(false);   

    // Get item selected
    auto item = _item->text(0).toStdString();

    // Check if the item is from expired category.
    for (int i = 0; i < _db._deactivatedCategory._contracts.size(); i++) {
        Contract *contract = &_db._deactivatedCategory._contracts[i]; 
        if (contract->_name == item) {
            // It's a contract.
            this->_selectedContract = contract;
            this->_selectedCategoryName = "Deactivated";
            this->infoBtn->setEnabled(true);
            this->deleteBtn->setEnabled(true);
        }
    }
    // Check if item name is a contract name.
    for (int i = 0; i < _db._categories.size(); i++) {
        Category *category = &_db._categories[i];
        if (item != category->_name) {
            // Iterate over contracts.
            for (int j = 0; j < category->_contracts.size(); j++) {
                Contract *contract = &category->_contracts[i];
                if (item == contract->_name) {
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
}

auto MainWindow::on_actionAdd_Category_triggered() -> void {
    addCategoryWindow *win = new addCategoryWindow(&_db, this);
    win->show();
}

auto MainWindow::on_actionInfo_triggered() -> void {
    appInfoWindow *win = new appInfoWindow(this);
    win->show();
}

auto MainWindow::updateDB() -> void {
    std::thread *iter = new std::thread(&DBChecker::checkDBiter, this->_checker);
    this->listDB();
    export_db_as_db(_db, "db.db");
}
