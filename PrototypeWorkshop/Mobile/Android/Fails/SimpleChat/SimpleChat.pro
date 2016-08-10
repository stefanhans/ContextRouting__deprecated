#-------------------------------------------------
#
# Project created by QtCreator 2016-08-10T15:01:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleChat
TEMPLATE = app


SOURCES += main.cpp \
    MainWindow.cpp

HEADERS  += \
    MainWindow.h

FORMS    += \
    chatWindow.ui

CONFIG += mobility
MOBILITY = 

