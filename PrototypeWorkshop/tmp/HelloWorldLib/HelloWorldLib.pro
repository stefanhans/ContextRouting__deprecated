#-------------------------------------------------
#
# Project created by QtCreator 2016-02-19T13:17:19
#
#-------------------------------------------------

QT       -= gui

TARGET = HelloWorldLib
TEMPLATE = lib

DEFINES += HELLOWORLDLIB_LIBRARY

SOURCES += helloworldlib.cpp

HEADERS += helloworldlib.h\
        helloworldlib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
