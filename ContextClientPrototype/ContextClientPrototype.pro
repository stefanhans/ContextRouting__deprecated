#-------------------------------------------------
#
# Project created by QtCreator 2015-06-29T08:37:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ContextClientPrototype_B
TEMPLATE = app

LIBS += -luuid


SOURCES += main.cpp\
        mainwindow.cpp \
    abstractwidget.cpp \
    abstractreader.cpp \
    codingwidget.cpp \
    codingreader.cpp \
    dictionarytree.cpp \
    abstractcodingelement.cpp \
    dictionarywidget.cpp \
    dictionaryreader.cpp \
    offerwidget.cpp \
    abstractwriter.cpp \
    offerreader.cpp \
    offerwriter.cpp \
    dictionarycodingelement.cpp \
    requestreader.cpp \
    requestwriter.cpp \
    requestwidget.cpp

HEADERS  += mainwindow.h \
    abstractwidget.h \
    abstractreader.h \
    codingwidget.h \
    codingreader.h \
    dictionarytree.h \
    abstractcodingelement.h \
    dictionarywidget.h \
    dictionaryreader.h \
    offerwidget.h \
    abstractwriter.h \
    offerreader.h \
    offerwriter.h \
    dictionarycodingelement.h \
    requestreader.h \
    requestwriter.h \
    requestwidget.h
