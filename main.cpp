#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QDebug>

#include "CalendarClient/CalendarManager.h"
#include "CalendarClient/CalendarClient_CalDAV.h"
#include "CalendarClient/CalendarClient_ICS.h"
#include "CalendarClient/CalendarClient.h"

#include "lunartools.h"
#include "qlunardate.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QLocale::setDefault(QLocale(QLocale::Vietnamese, QLocale::Vietnam));
    QQuickStyle::setStyle("Material");

    CalendarManager calendarManager(QString(app.applicationDirPath()+"/CalendarManager.ini"));
    LunarTools lunarTools;

    qmlRegisterUncreatableType<QLunarDate>("VCalendar", 1, 0, "QLunarDate", "QLunarDate is uncreatable");
    qmlRegisterUncreatableType<LunarTools>("VCalendar", 1, 0, "LunarTools", "LunarTools is uncreatable");
    qmlRegisterUncreatableType<CalendarClient>("VCalendar", 1, 0, "CalendarClient", "CalendarClient is uncreatable");
    qmlRegisterUncreatableType<CalendarClient_CalDAV>("VCalendar", 1, 0, "CalendarClient_CalDAV", "CalendarClient_CalDAV is uncreatable");
    qmlRegisterUncreatableType<CalendarClient_ICS>("VCalendar", 1, 0, "CalendarClient_ICS", "CalendarClient_ICS is uncreatable");
    qmlRegisterUncreatableType<CalendarManager>("VCalendar", 1, 0, "CalendarManager", "CalendarManager is uncreatable");

//    /*
//     * Test
//    */

//    qint32 yy,mm,dd;
//    Lunar::convertSolar2Lunar(QDate::currentDate(), 7, dd, mm, yy);

//    qInfo() << yy << "/" << mm << "/" << dd;



    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("calendarManager", &calendarManager);
    engine.rootContext()->setContextProperty("lunarTools", &lunarTools);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
