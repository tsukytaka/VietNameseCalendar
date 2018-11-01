#ifndef SETTINGMODULE_H
#define SETTINGMODULE_H

#include <QObject>
#include <QSettings>

#define WEB_SECTION "WEB-SECTION"
#define PORT_KEY    "Port"
#define PORT_DEFAULT "9111"

class SettingModule : public QObject
{
    Q_OBJECT
public:
    static SettingModule* getInstance();
    QSettings *getSettingObject();
    ~SettingModule();

signals:

public slots:

private:
    explicit SettingModule(QObject *parent = 0);
    static SettingModule* instance;
    QSettings *settingObject;
    QString configFilePath;
};

#endif // SETTINGMODULE_H
