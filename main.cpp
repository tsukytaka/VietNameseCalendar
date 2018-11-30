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
#include "ManageAcc/accountmanager.h"

QSettings* appSettings;
QString dataDir;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QLocale::setDefault(QLocale(QLocale::Vietnamese, QLocale::Vietnam));
    QQuickStyle::setStyle("Material");

    qRegisterMetaType<QLunarDate*>();
    qmlRegisterSingletonType<LunarTools>("VCalendar", 1, 0, "LunarTools", LunarTools::qobject_lunartools_provider);

    dataDir =  QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QDir dir(dataDir);
    if (!dir.exists()){
        dir.mkdir(dataDir);
    }
    qInfo() << "dataDir = " << dataDir;
    QString pathConfigFile = dataDir + QDir::separator() + QCoreApplication::applicationName().append('.cfg');
    appSettings = new QSettings(pathConfigFile, QSettings::IniFormat, &app);

//    AccountManager accMng;
//    accMng.addAccount(Account::TYPE_ACC::GoogleType);

//    /*
//     * Test OAuth2
//     */
//    OAuth2* m_pOauth2 = new OAuth2(appSettings);
//    m_pOauth2->startLogin("https://www.googleapis.com/auth/calendar");

//    /*
//     * Test convert lunar date
//    */
//    qint32 yy,mm,dd;
//    Lunar::convertSolar2Lunar(QDate::currentDate(), 7, dd, mm, yy);
//    qInfo() << yy << "/" << mm << "/" << dd;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
