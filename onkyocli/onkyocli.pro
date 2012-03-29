#-------------------------------------------------
#
# Project created by QtCreator 2012-02-16T15:02:34
#
#-------------------------------------------------
QT += core
QT += network
QT -= gui

TEMPLATE = app
TARGET = onkyocli
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp \
    cliprinter.cpp \
    options.cpp

HEADERS += \
    cliprinter.h \
    options.h

INCLUDEPATH += ../lib
include(../lib/lib.pri)
