QT += core
QT -= gui

CONFIG += c++11

TARGET = UnitTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

############################################
# Add LangManager library to project
############################################
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Build/release/ -lLangManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Build/debug/ -lLangManager
else:unix: LIBS += -L$$PWD/../Build/ -lLangManager
INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
