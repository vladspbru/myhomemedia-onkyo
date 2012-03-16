#-------------------------------------------------
#
# Project created by QtCreator 2012-02-16T15:02:34
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = onkyocli
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../lib

SOURCES += main.cpp \
    ../lib/deviceinfo.cpp \
    ../lib/devicediscoverysimple.cpp \
    ../lib/iscpmessage.cpp \
    ../lib/onkyoclient.cpp \
    cliprinter.cpp \
    options.cpp

HEADERS += \
    ../lib/deviceinfo.h \
    ../lib/devicediscoverysimple.h \
    ../lib/iscpmessage.h \
    ../lib/onkyoclient.h \
    cliprinter.h \
    options.h

