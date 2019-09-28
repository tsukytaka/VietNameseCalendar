#include "langmng.h"

LangMng* LangMng::_instance = nullptr;

LangMng::LangMng()
{
    _langParam = COMMON_LANGAGE_TYPE_VIE;
    _currentLang = _langParam;
    _commonString = new CommonStringMaster(static_cast<COMMON_LANGAGE_TYPE>(_langParam));
}

LangMng::~LangMng()
{
    if(_commonString)
        delete _commonString;
}

LangMng* LangMng::GetInstance()
{
    if (!_instance) {
        _instance = new LangMng();
    }
    return _instance;
}

QString LangMng::getStr(quint32 id)
{
    QString str = "";
    str = getStringSpecifyLang(id, getCurrentLang());
    return str;
}

QString LangMng::getStringSpecifyLang(quint32 id, quint32 langId)
{
    QString str = "";
    if (_currentLang != langId)
    {
        _currentLang = langId;
    }
    _commonString->getString(id, str);
    return str;
}

quint32 LangMng::getCurrentLang()
{
    return _langParam;
}

void LangMng::setCurrentLang(quint32 lang)
{
    _langParam = lang;
}
