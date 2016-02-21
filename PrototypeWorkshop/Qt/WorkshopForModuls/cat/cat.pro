#-------------------------------------------------
#
# Project created by QtCreator 2016-02-21T21:23:52
#
#-------------------------------------------------

QT       -= gui

TARGET = cat
TEMPLATE = lib

DEFINES += CAT_LIBRARY

SOURCES += cat.cpp

HEADERS += cat.h\
        cat_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
