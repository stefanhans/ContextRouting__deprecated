#-------------------------------------------------
#
# Project created by QtCreator 2016-03-17T20:11:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

unix:!macx: LIBS += -L$$PWD/../build-CIP-Desktop_Qt_5_5_1_GCC_64bit-Release/ -lCIP

INCLUDEPATH += $$PWD/../CIP
DEPENDPATH += $$PWD/../CIP
