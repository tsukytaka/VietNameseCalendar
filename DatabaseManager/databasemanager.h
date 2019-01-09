#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QtSql/QSqlDatabase>


#define DB_NAME "status_saver"
#define ACC_TABLE "TblAccount"
#define INFO_GOOGLE_ACC_TABLE "TblGoogleAccount"
#define CALENDAR_TABLE "TblCalendar"
#define LUNAR_CALENDAR_TABLE "TblLunarCalendar"
#define GOOGLE_CALENDAR_TABLE "TblGoogleCalendar"
#define EVENT_TABLE "TblEvent"
#define LUNAR_EVENT_TABLE "TblLunarEvent"
#define GOOGLE_EVENT_TABLE "TblGoogleEvent"

class DatabaseManager
{
public:
    static DatabaseManager *getInstance();

private:
    DatabaseManager();
    DatabaseManager(QString pathDB);
    void prepareDatabase(QString pathDB);

private:
    static DatabaseManager *instance;
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
