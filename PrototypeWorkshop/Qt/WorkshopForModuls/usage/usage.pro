#-------------------------------------------------
#
# Project created by QtCreator 2016-02-21T14:30:30
#
#-------------------------------------------------

QT       -= gui

TEMPLATE = lib

DEFINES += USAGE_LIBRARY

SOURCES += usage.cpp

HEADERS += usage.h\
        usage_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
