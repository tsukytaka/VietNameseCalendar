QT += qml quick quickcontrols2 xml xmlpatterns websockets

CONFIG += c++11

SOURCES += main.cpp \
    lunartools.cpp \
    qlunardate.cpp \
    ScheduleScreen/schedulescreenvm.cpp \
    scheduleitem.cpp \
    EventsScreen/eventsscreenvm.cpp \
    event.cpp \
    weblistenerserver.cpp \
    settingmodule.cpp \
    httpserver/httpconnectionhandler.cpp \
    httpserver/httpconnectionhandlerpool.cpp \
    httpserver/httprequesthandler.cpp \
    httpserver/httprequest.cpp \
    httpserver/httpresponse.cpp \
    httpserver/httplistener.cpp

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
    scheduleitem.h \
    EventsScreen/eventsscreenvm.h \
    event.h \
    weblistenerserver.h \
    settingmodule.h \
    httpserver/httpconnectionhandler.h \
    httpserver/httpconnectionhandlerpool.h \
    httpserver/httprequesthandler.h \
    httpserver/httprequest.h \
    httpserver/httpresponse.h \
    httpserver/httplistener.h

DISTFILES += \
    config/VietNameseCalendar.cfg
