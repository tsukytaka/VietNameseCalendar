QT += core
QT += gui

CONFIG += c++11

TARGET = ResourceManager
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ResourceMng.cpp

HEADERS += \
    ResourceMng.h \
    test.h
