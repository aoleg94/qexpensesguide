#-------------------------------------------------
#
# Project created by QtCreator 2015-11-28T00:29:12
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qexpensesguide
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addoperationdialog.cpp

HEADERS  += mainwindow.h \
    addoperationdialog.h

FORMS    += mainwindow.ui \
    addoperationdialog.ui

CONFIG += mobility
MOBILITY = 

