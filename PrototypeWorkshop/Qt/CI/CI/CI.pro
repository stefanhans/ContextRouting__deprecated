#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T10:01:51
#
#-------------------------------------------------

QT       += core gui network

TARGET = CI
TEMPLATE = lib

DEFINES += CI_LIBRARY

SOURCES += ci.cpp

HEADERS += ci.h\
        ci_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
