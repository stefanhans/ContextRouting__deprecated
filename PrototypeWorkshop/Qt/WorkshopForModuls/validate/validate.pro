QT       += core network

QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

HEADERS +=

unix:!macx: LIBS += -L$$PWD/../build-usage-Desktop_Qt_5_5_1_GCC_64bit-Release/ -lusage

INCLUDEPATH += $$PWD/../Lib/usage
DEPENDPATH += $$PWD/../Lib/usage


