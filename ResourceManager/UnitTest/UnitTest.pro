QT += core
QT += gui

CONFIG += c++11

TARGET = UnitTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

############################################
# Add ResourceManager library to project
############################################
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Build/release/ -lResourceManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Build/debug/ -lResourceManager
else:unix: LIBS += -L$$PWD/../Build/ -lResourceManager
INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
