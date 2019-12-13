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

}

MainWindow::~MainWindow() {

}

void MainWindow::closeEvent(QCloseEvent *event)
{
        if(closing)
        {
            event->accept();
        }
        else
        {
            this->hide();
            event->ignore();
        }
}

void MainWindow::onCloseBtn_clicked() {
}
