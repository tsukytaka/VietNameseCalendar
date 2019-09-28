#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T10:35:28
#
#-------------------------------------------------

QT       += gui

TARGET = ResourceManager
TEMPLATE = lib

DEFINES += RESOURCEMANAGER_LIBRARY

SOURCES += resourcemanager.cpp

HEADERS += resourcemanager.h\
        resourcemanager_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
