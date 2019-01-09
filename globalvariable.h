#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <QObject>
#include "afxstd.h"

class GlobalVariable
{
public:
    static GlobalVariable *getInstance();

    inline QSettings* getAppSetting() {return m_appSettings; }
    inline void setAppSetting(QSettings* appSetting) {m_appSettings = appSetting; }
    inline QString getDataDir() {return m_dataDir; }
    inline void setDataDir(QString dataDir) {m_dataDir = dataDir; }

private:
    GlobalVariable();
    ~GlobalVariable();

private:
    static GlobalVariable *instance;

    QSettings* m_appSettings;
    QString m_dataDir;
};

#endif // GLOBALVARIABLE_H
