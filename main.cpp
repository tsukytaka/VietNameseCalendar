#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

#include "lunartools.h"
#include "qlunardate.h"
#include "settingmodule.h"
//#include "weblistenerserver.h"
#include "httpserver/httplistener.h"

#define LISTENER_GROUP_NAME "listener"

HttpListener *httpListener;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QLocale::setDefault(QLocale(QLocale::Vietnamese, QLocale::Vietnam));
    QQuickStyle::setStyle("Material");

    qRegisterMetaType<QLunarDate*>();
//    qmlRegisterType<QLunarDate>("VCalendar", 1, 0, "QLunarDate");
    qmlRegisterSingletonType<LunarTools>("VCalendar", 1, 0, "LunarTools", LunarTools::qobject_lunartools_provider);

//    static WebListenerServer receiverOAuth(SettingModule::getInstance()->getSettingObject()->value(PORT_KEY, PORT_DEFAULT).toInt());

//    QSettings *appSetting = new QSettings()
//    HttpListener


     QString path =  QStandardPaths::writableLocation(QStandardPaths::DataLocation);
     QDir dir(path);
     if (!dir.exists()){
       dir.mkdir(path);
     }

     qInfo() << "path = " << path;
     QString pathConfigFile = path + '/' + QCoreApplication::applicationName() + '.cfg';
     QSettings* listenerSettings = new QSettings(pathConfigFile, QSettings::IniFormat, &app);
     listenerSettings->sync();
     listenerSettings->beginGroup(LISTENER_GROUP_NAME);

     httpListener = new HttpListener(listenerSettings, new HttpRequestHandler(&app), &app);

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
