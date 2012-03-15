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

INCLUDEPATH += ../onkyo_client

SOURCES += main.cpp \
    ../onkyo_client/iscpmessage.cpp \
    ../onkyo_client/devicediscovery.cpp \
    ../onkyo_client/deviceinfo.cpp \
    ../onkyo_client/onkyoclient.cpp \
    cliprinter.cpp \
    options.cpp

HEADERS += \
    ../onkyo_client/iscpmessage.h \
    ../onkyo_client/devicediscovery.h \
    ../onkyo_client/deviceinfo.h \
    ../onkyo_client/onkyoclient.h \
    cliprinter.h \
    options.h

