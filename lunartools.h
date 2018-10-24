#ifndef LUNAR_TOOLS_H
#define LUNAR_TOOLS_H

#define PI 3.141592653589793
#define TIME_ZONE 7

#include <QObject>
#include <QDate>
#include "qlunardate.h"

class LunarTools : public QObject
{
    Q_OBJECT
public:
    explicit LunarTools(QObject *parent = 0);

    Q_INVOKABLE static qint64 getMonthOfLunarByJd(qint64 jd);
    Q_INVOKABLE static qint64 getNewMoonDay(qint64 monthOfLunar, qint32 timeZone);
    Q_INVOKABLE static qint32 getSunLongitude(qint64 jdn, qint32 timeZone);
    Q_INVOKABLE static qint32 getLunarMonth11(qint32 year, qint32 timeZone);
    Q_INVOKABLE static qint32 getLeapMonthOffset(qint32 a11, qint32 timeZone);
    Q_INVOKABLE static QLunarDate convertSolar2Lunar(QDate date, qint32 timeZone);
    Q_INVOKABLE static QDate convertLunar2Solar(qint32 lunarDay, qint32 lunarMonth, qint32 lunarYear, qint32 lunarLeap, qint32 timeZone);

signals:

public slots:
};

#endif // LUNAR_H
