#include "databasemanager.h"
#include <QDir>
#include <QFile>
#include <QtSql/QSqlQuery>

extern QString dataDir;

DatabaseManager* DatabaseManager::instance = NULL;

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
        QString pathDB = dataDir + QDir::separator() + "VietnameseCalendar.sqlite";
        instance = new DatabaseManager(pathDB);
    }
    return instance;
}

void DatabaseManager :: prepareDatabase(QString pathDB){
    QFile fileSql(pathDB);
    if (!fileSql.exists()) {
        db.open();
//        db.database().transaction();
        QSqlQuery query;
        query.exec(QString("create table %1 (Name nvarchar(100) primary key, Type tinyint, Color nvarchar(12)").arg(ACC_TABLE));
        query.exec(QString("create table %1 (Name nvarchar(100) primary key, AuthCode nvarchar(100), RefreshToken nvarchar(100), Access_Token nvarchar(100)").arg(GOOGLE_ACC_TABLE));
//        db.database().commit();
    }
}
