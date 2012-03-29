TEMPLATE = lib
TARGET = onkyo_client
CONFIG += qt plugin
QT += declarative network

DESTDIR = plugins/vx/home/qmlcomponents
TARGET = $$qtLibraryTarget($$TARGET)
uri = vx.home.qmlcomponents

# Input
SOURCES += \
    onkyo_client_plugin.cpp \
    onkyoremoteitem.cpp \ 
    onkyoparameteritem.cpp

HEADERS += \
    onkyo_client_plugin.h \
    onkyoremoteitem.h \ 
    onkyoparameteritem.h

INCLUDEPATH += ../lib
include(../lib/lib.pri)

OTHER_FILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    maemo5 | !isEmpty(MEEGO_VERSION_MAJOR) {
        installPath = /usr/lib/qt4/imports/$$replace(uri, \\., /)
    } else {
        installPath = $$[QT_INSTALL_IMPORTS]/$$replace(uri, \\., /)
    }
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

