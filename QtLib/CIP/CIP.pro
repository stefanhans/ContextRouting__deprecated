#-------------------------------------------------
#
# Project created by QtCreator 2016-03-16T19:52:42
#
#-------------------------------------------------

QT       -= gui

QT += network

TARGET = CIP
TEMPLATE = lib

DEFINES += CIP_LIBRARY

SOURCES += cip.cpp

HEADERS += cip.h\
        cip_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
