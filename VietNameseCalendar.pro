QT += qml quick quickcontrols2 xml xmlpatterns websockets network sql

CONFIG += c++11

SOURCES += main.cpp \
    lunartools.cpp \
    qlunardate.cpp \
    ScheduleScreen/schedulescreenvm.cpp \
    EventsScreen/eventsscreenvm.cpp \
    weblistenerserver.cpp \
    settingmodule.cpp \
    httpserver/httpconnectionhandler.cpp \
    httpserver/httpconnectionhandlerpool.cpp \
    httpserver/httprequesthandler.cpp \
    httpserver/httprequest.cpp \
    httpserver/httpresponse.cpp \
    httpserver/httplistener.cpp \
    googlecalendar/oauth2.cpp \
    ManageAcc/accountmanager.cpp \
    ManageAcc/account.cpp \
    ManageAcc/googleaccount.cpp \
    DatabaseManager/databasemanager.cpp \
    SystemMenu/systemmenuvm.cpp \
    MonthScreen/monthviewvm.cpp \
    googlecalendar/googlecalendartool.cpp \
    DatabaseManager/calendar.cpp \
    DatabaseManager/event.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    lunartools.h \
    qlunardate.h \
    afxstd.h \
    ScheduleScreen/schedulescreenvm.h \
    EventsScreen/eventsscreenvm.h \
    weblistenerserver.h \
    settingmodule.h \
    httpserver/httpconnectionhandler.h \
    httpserver/httpconnectionhandlerpool.h \
    httpserver/httprequesthandler.h \
    httpserver/httprequest.h \
    httpserver/httpresponse.h \
    httpserver/httplistener.h \
    googlecalendar/oauth2.h \
    ManageAcc/accountmanager.h \
    ManageAcc/account.h \
    ManageAcc/googleaccount.h \
    DatabaseManager/databasemanager.h \
    SystemMenu/systemmenuvm.h \
    MonthScreen/monthviewvm.h \
    googlecalendar/googlecalendartool.h \
    DatabaseManager/calendar.h \
    DatabaseManager/event.h \
    errorcode.h

DISTFILES += \
    config/VietNameseCalendar.cfg
