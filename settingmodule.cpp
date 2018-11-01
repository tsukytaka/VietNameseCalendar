#include "settingmodule.h"

SettingModule* SettingModule::instance = NULL;

SettingModule::SettingModule(QObject *parent) : QObject(parent)
{
    //Init config file
#ifdef Q_OS_WIN
    configFilePath = "./VietNameseCalendar.ini";
#else
    configFilePath = "";
#endif

    settingObject = new QSettings(configFilePath, QSettings::IniFormat);
}

SettingModule::~SettingModule() {
    delete settingObject;
}

SettingModule* SettingModule::getInstance() {
    if (instance == NULL) {
        instance = new SettingModule();
    }
    return instance;
}

QSettings* SettingModule::getSettingObject() {
    return settingObject;
}
