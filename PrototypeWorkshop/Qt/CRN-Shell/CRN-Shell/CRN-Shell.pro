#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T09:59:40
#
#-------------------------------------------------

QT       +=  gui network

QT       -= gui

TARGET = CRN-Shell
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

#DEFINES += QT_NO_DEBUG_OUTPUT


SOURCES += main.cpp \
    subshell_crn.cpp \
    subshell_ci.cpp \
    subshell_cip.cpp

unix:!macx: LIBS += -L$$PWD/../build-CI-Desktop_Qt_5_4_1_GCC_64bit-Release/ -lCI

INCLUDEPATH += $$PWD/../CI
DEPENDPATH += $$PWD/../CI

unix:!macx: LIBS += -L$$PWD/../build-CRN-Desktop_Qt_5_4_1_GCC_64bit-Release/ -lCRN

INCLUDEPATH += $$PWD/../CRN
DEPENDPATH += $$PWD/../CRN

unix:!macx: LIBS += -L$$PWD/../build-CIP-Desktop_Qt_5_4_1_GCC_64bit-Release/ -lCIP

INCLUDEPATH += $$PWD/../CIP
DEPENDPATH += $$PWD/../CIP

HEADERS += \
    subshell_crn.h \
    subshell_ci.h \
    subshell_cip.h
