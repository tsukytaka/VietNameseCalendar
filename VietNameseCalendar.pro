QT += qml quick quickcontrols2 xml xmlpatterns

CONFIG += c++11

SOURCES += main.cpp \
    CalendarClient/CalendarClient_CalDAV_ReceiveResonse.cpp \
    CalendarClient/CalendarClient_CalDAV_SendRequest.cpp \
    CalendarClient/CalendarClient_CalDAV_StateMachine.cpp \
    CalendarClient/CalendarClient_CalDAV_Utils.cpp \
    CalendarClient/CalendarClient_CalDAV.cpp \
    CalendarClient/CalendarClient_ICS_ReceiveResonse.cpp \
    CalendarClient/CalendarClient_ICS_SendRequest.cpp \
    CalendarClient/CalendarClient_ICS_StateMachine.cpp \
    CalendarClient/CalendarClient_ICS.cpp \
    CalendarClient/CalendarClient.cpp \
    CalendarClient/CalendarEvent.cpp \
    CalendarClient/CalendarManager.cpp \
    CalendarClient/DateUtils.cpp \
    CalendarClient/SimpleCrypt.cpp \
    lunartools.cpp \
    qlunardate.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    CalendarClient/CalendarClient_CalDAV.h \
    CalendarClient/CalendarClient_ICS.h \
    CalendarClient/CalendarClient.h \
    CalendarClient/CalendarEvent.h \
    CalendarClient/CalendarManager.h \
    CalendarClient/DateUtils.h \
    CalendarClient/SimpleCrypt.h \
    lunartools.h \
    qlunardate.h
