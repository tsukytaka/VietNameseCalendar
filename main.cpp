#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

#include "afxstd.h"
#include "lunartools.h"
#include "qlunardate.h"
#include "settingmodule.h"
#include "ManageAcc/accountmanager.h"
#include "globalvariable.h"
#include "DatabaseManager/databasemanager.h"
#include "CreateEventScreen/createeventscreenvm.h"
#include "imgprovider.h"
#include "DatabaseManager/lunarcalendar.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QLocale::setDefault(QLocale(QLocale::Vietnamese, QLocale::Vietnam));
    QQuickStyle::setStyle("Material");

    qRegisterMetaType<QLunarDate*>();
    qmlRegisterSingletonType<LunarTools>("VCalendar", 1, 0, "LunarTools", LunarTools::qobject_lunartools_provider);
    qmlRegisterType<CreateEventScreenVM>("VCalendar", 1, 0, "CreateEventScreenVM");

    GlobalVariable::getInstance()->setDataDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    QDir dir(GlobalVariable::getInstance()->getDataDir());
    if (!dir.exists())
    {
        dir.mkdir(GlobalVariable::getInstance()->getDataDir());
    }
    qInfo() << "dataDir = " << GlobalVariable::getInstance()->getDataDir();
    QString pathConfigFile = GlobalVariable::getInstance()->getDataDir() + QDir::separator() + QCoreApplication::applicationName().append(".cfg");
    GlobalVariable::getInstance()->setAppSetting( new QSettings(pathConfigFile, QSettings::IniFormat, &app));

//    DatabaseManager::getInstance();


//    /*
//     * Test import from csv file for lunar calendar
//     */
//    LunarCalendar lunarCal;
//    ErrorCode ret = lunarCal.importCSVFile("../../otherfile/lunarCal.csv");
//    if (ret == FileInvalid) {
//        qWarning() << "file error or not exist";
//    }
//    qint32 numberEvent;
//    ret = lunarCal.getNumberEvent(numberEvent);
//    if (ret != Success) {
//        qWarning() << "get number event error";
//    }
//    qDebug() << "number event = " << numberEvent;



//    defaultAcc.addCalendar(lunarCal);

//    /*
//     * Test OAuth2
//     */
//    OAuth2* m_pOauth2 = new OAuth2(appSettings);
//    m_pOauth2->startLogin("https://www.googleapis.com/auth/calendar");

//    /*
//     * Test convert lunar date
//    */
//    QLunarDate lunarDate(LunarTools::convertSolar2Lunar(QDate::currentDate(), TIME_ZONE));
//    qInfo() << lunarDate.year() << "/" << lunarDate.month() << "/" << lunarDate.day();

//    /*
//     * Test step
//     */
//    qint64 currentJdDate = QDate::currentDate().toJulianDay();
//    qInfo() << "currentJdDate = " << currentJdDate;

//    qint64 k = qint64((currentJdDate/* - JAN_01_1990_NUMBER_DAY_JD*/) / AVG_NUMBER_DAY_IN_MONTH);
//    qInfo() << "k = " << k;

//    qreal T = k/(AVG_NUMBER_LUNAR_MONTH_IN_YEAR*100);
//    qInfo() << "T = " << T;
//    qreal T2 = T * T;
//    qInfo() << "T2 = " << T2;
//    qreal T3 = T2 * T;
//    qInfo() << "T3 = " << T3;
//    qint64 jdDayMonthStart = qint64(/*JAN_01_1990_NUMBER_DAY_JD + */AVG_NUMBER_DAY_IN_MONTH*k + 0.0001178*T2 - 0.000000155*T3);
//    qInfo() << "jdDayMonthStart = " << jdDayMonthStart;

//    QDate date(2019, 2, 5);
//    QLunarDate* lunarDate = LunarTools::convertSolar2Lunar(date, TIME_ZONE);
//    qInfo() << "lunarDate: " << lunarDate->leap() << "-" << lunarDate->day() << "-" << lunarDate->month() << "-" << lunarDate->year();

//    QDate destinativeDate = LunarTools::convertLunar2Solar(*lunarDate, TIME_ZONE);
//    qInfo() << "solarDate: " << destinativeDate.day() << "-" << destinativeDate.month() << "-" << destinativeDate.year();


//    LunarTools::convertLunar2Solar(
//    /*
//     * Test GoogleAcc
//     *
//     */
//    GoogleAccount googleAcc;
//    googleAcc.Login();
//    googleAcc.Synchronize();



    QQmlApplicationEngine engine;

    ImgProvider *imgProvider = ImgProvider::GetInstance();
    engine.addImageProvider(QString("ImgProvider"), imgProvider);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
