#ifndef AMLICH_H
#define AMLICH_H

#include <QObject>

class AmLich : public QObject
{
    Q_OBJECT
public:
    explicit AmLich(QObject *parent = 0);

    static qint64 getNewMoonDay(qint64 monthOfAmLich, int timeZone);
    static qint64 getMonthOfAmLichByJd(qint64 jd);

//    static qint64 dateToJd(QDate date);
//    static QDate jdToDate(qint64 jdn);

signals:

public slots:
};

#endif // AMLICH_H
