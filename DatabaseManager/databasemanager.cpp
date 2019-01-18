#include "databasemanager.h"
#include <QDir>
#include <QFile>
#include <QtSql/QSqlQuery>
#include "globalvariable.h"

//extern QString dataDir;

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

DatabaseManager::DatabaseManager(QString pathDB)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathDB);
    prepareDatabase(pathDB);
}

DatabaseManager* DatabaseManager::getInstance()
{
    if (!instance) {
        QString pathDB = GlobalVariable::getInstance()->getDataDir() + QDir::separator() + "VietnameseCalendar.sqlite";
        instance = new DatabaseManager(pathDB);
    }
    return instance;
}

void DatabaseManager::prepareDatabase(QString pathDB)
{
    QFile fileSql(pathDB);
    if (!fileSql.exists()) {
        db.open();
        QSqlQuery query;
        query.exec(QString("create table %1 (Name NVARCHAR(100) primary key, Type TINYINT, Color NVARCHAR(12)").arg(ACC_TABLE));
        query.exec(QString("create table %1 (Name NVARCHAR(100) primary key, AuthCode NVARCHAR(100), RefreshToken NVARCHAR(100), Access_Token NVARCHAR(100)").arg(INFO_GOOGLE_ACC_TABLE));
        query.exec(QString("create table %1 (Id NVARCHAR(100) primary key, Name NVARCHAR(100), BgColor NVARCHAR(12), FgColor NVARCHAR(12), TimeZone TINYINT, NameAcc NVARCHAR(100)").arg(CALENDAR_TABLE));
//        query.exec(QString("create table %1 (Id NVARCHAR(100) primary key").arg(LUNAR_CALENDAR_TABLE));
        query.exec(QString("create table %1 (Id NVARCHAR(100) primary key, Kind NVARCHAR(100), Etag NVARCHAR(100), Summary NVARCHAR(100), AccessRole NVARCHAR(100)").arg(GOOGLE_CALENDAR_TABLE));
        query.exec(QString("create table %1 (Id NVARCHAR(100) primary key, Type TINYINT, Datetime DATETIME, IdCalendar NVARCHAR(100)").arg(EVENT_TABLE));
        query.exec(QString("create table %1 (Id NVARCHAR(100) primary key, LunarDatetime DATETIME").arg(LUNAR_EVENT_TABLE));
    }
}
