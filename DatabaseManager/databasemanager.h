#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QtSql/QSqlDatabase>


#define DB_NAME "status_saver"
#define ACC_TABLE "TblAccount"
#define GOOGLE_ACC_TABLE "TblGoogleAccount"

class DatabaseManager
{
public:
    DatabaseManager *getInstance();

private:
    DatabaseManager();
    DatabaseManager(QString pathDB);
    void prepareDatabase(QString pathDB);

private:
    static DatabaseManager *instance;
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
