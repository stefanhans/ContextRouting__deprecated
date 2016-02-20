#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T11:36:42
#
#-------------------------------------------------

QT       += core gui network

TARGET = CRN
TEMPLATE = lib

DEFINES += CRN_LIBRARY

SOURCES += crn.cpp \
    tcp_ping.cpp

HEADERS += crn.h\
        crn_global.h \
    tcp_ping.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
