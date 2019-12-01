QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ContractNotifier
TEMPLATE = app
CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp

HEADERS += \
        src/mainwindow.h \
		src/lib/contract.h \
		src/lib/db.h \
		src/lib/export.h \
		src/lib/import.h \
		src/lib/notify.h

FORMS += \
        src/mainwindow.ui
