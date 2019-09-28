#ifndef LANGMANAGER_H
#define LANGMANAGER_H

#include "langmng_global.h"
#include "common_string.h"
#include <QString>

class LANGMANAGERSHARED_EXPORT LangMng
{

public:
    static LangMng *GetInstance();
    QString getStr(quint32 id);
    void setCurrentLang(quint32 lang);

private:
    static LangMng *_instance;
    uint32_t _currentLang;
    LangMng();
    ~LangMng();

    QString getStringSpecifyLang(quint32 id, quint32 langId);
    quint32 getCurrentLang();

    CommonStringMaster *_commonString;

    quint32 _langParam;
};

#endif // LANGMANAGER_H
