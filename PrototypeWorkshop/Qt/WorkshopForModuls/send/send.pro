QT  += core network
QT  -= gui

TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle

SOURCES += main.cpp

unix:!macx: LIBS += -L$$PWD/../build-usage-Desktop_Qt_5_5_1_GCC_64bit-Release/ -lusage

INCLUDEPATH += $$PWD/../Lib/usage
DEPENDPATH += $$PWD/../Lib/usage


