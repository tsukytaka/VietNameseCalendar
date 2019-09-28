#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T09:11:45
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = LangManager
TEMPLATE = lib

DEFINES += LANGMANAGER_LIBRARY
DEFINES += USING_SCREEN_OPERATOR
DEFINES += _USING_STDINT

SOURCES += \
    langmng.cpp \
    common_string.cpp

HEADERS +=\
    langmng.h \
    langmng_global.h \
    common_string.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
