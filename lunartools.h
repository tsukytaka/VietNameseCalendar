#ifndef LUNAR_TOOLS_H
#define LUNAR_TOOLS_H
#include "afxstd.h"
#include <QObject>
#include <QDate>
#include <QJSValue>
#include <QQmlEngine>
#include "qlunardate.h"

class LunarTools : public QObject
{
    Q_OBJECT
public:

    static LunarTools* getInstance();
    static QObject *qobject_lunartools_provider(QQmlEngine *engine, QJSEngine *scriptEngine);
    Q_INVOKABLE static qint64 getMonthOfLunarByJd(qint64 jd);
    Q_INVOKABLE static qint64 getNewMoonDay(qint64 monthOfLunar, qint32 timeZone);
    Q_INVOKABLE static qint64 getSunLongitude(qint64 jdn, qint32 timeZone);
    Q_INVOKABLE static qint64 getLunarMonth11(qint32 year, qint32 timeZone);
    Q_INVOKABLE static qint32 getLeapMonthOffset(qint32 a11, qint32 timeZone);
    Q_INVOKABLE static QLunarDate *convertSolar2Lunar(QDate date, qint32 timeZone);
    Q_INVOKABLE static QDate convertLunar2Solar(QLunarDate lunarDate, qint32 timeZone);

private:
    explicit LunarTools(QObject *parent = nullptr);
    static LunarTools *instance;

signals:

public slots:
};

#endif // LUNAR_H
