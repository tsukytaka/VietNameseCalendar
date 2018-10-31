#ifndef SETTINGMODULE_H
#define SETTINGMODULE_H

#include <QObject>
#include <QSettings>

#define WEB_SECTION "WEB-SECTION"

class SettingModule : public QObject
{
    Q_OBJECT
public:
    static SettingModule* getInstance();

signals:

public slots:

private:
    explicit SettingModule(QObject *parent = 0);
    static SettingModule* instance;
    QSettings appSetting;
};

#endif // SETTINGMODULE_H
