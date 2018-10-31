#include "settingmodule.h"

SettingModule* SettingModule::instance = NULL;

SettingModule::SettingModule(QObject *parent) : QObject(parent)
{

}

SettingModule* SettingModule::getInstance() {
    if (instance == NULL) {
        instance = new SettingModule();
    }
    return instance;
}
