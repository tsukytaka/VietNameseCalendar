#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QDebug>

#include "lunartools.h"
#include "qlunardate.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QLocale::setDefault(QLocale(QLocale::Vietnamese, QLocale::Vietnam));
    QQuickStyle::setStyle("Material");

    qRegisterMetaType<QLunarDate*>();
//    qmlRegisterType<QLunarDate>("VCalendar", 1, 0, "QLunarDate");
    qmlRegisterSingletonType<LunarTools>("VCalendar", 1, 0, "LunarTools", LunarTools::qobject_lunartools_provider);

//    /*
//     * Test
//    */

//    qint32 yy,mm,dd;
//    Lunar::convertSolar2Lunar(QDate::currentDate(), 7, dd, mm, yy);

//    qInfo() << yy << "/" << mm << "/" << dd;



    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
