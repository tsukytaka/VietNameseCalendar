#include "amlich.h"
#include <QtMath>
#include <QDebug>

AmLich::AmLich(QObject *parent) : QObject(parent)
{

}

//static qint64 AmLich::dateToJd(QDate date) {
//    unsigned long a,y,m,jd;
//    a = 14 - date.
//}

//static QDate AmLich::jdToDate(qint64 jdn);'

qint64 AmLich::getNewMoonDay(qint64 monthOfAmLich, int timeZone) {
    qreal T, T2, T3, dr, Jd1, M, Mpr, F, C1, deltat, JdNew;
    T = monthOfAmLich/1236.85; // Time in Julian centuries from 1900 January 0.5
    T2 = T * T;
    T3 = T2 * T;
    dr = 3.14159/180;
    Jd1 = 2415020.75933 + 29.53058868*monthOfAmLich + 0.0001178*T2 - 0.000000155*T3;
    Jd1 = Jd1 + 0.00033*qSin((166.56 + 132.87*T - 0.009173*T2)*dr); // Mean new moon
    M = 359.2242 + 29.10535608*monthOfAmLich - 0.0000333*T2 - 0.00000347*T3; // Sun's mean anomaly
    Mpr = 306.0253 + 385.81691806*monthOfAmLich + 0.0107306*T2 + 0.00001236*T3; // Moon's mean anomaly
    F = 21.2964 + 390.67050646*monthOfAmLich - 0.0016528*T2 - 0.00000239*T3; // Moon's argument of latitude
    C1=(0.1734 - 0.000393*T)*qSin(M*dr) + 0.0021*qSin(2*dr*M);
    C1 = C1 - 0.4068*qSin(Mpr*dr) + 0.0161*qSin(dr*2*Mpr);
    C1 = C1 - 0.0004*qSin(dr*3*Mpr);
    C1 = C1 + 0.0104*qSin(dr*2*F) - 0.0051*qSin(dr*(M+Mpr));
    C1 = C1 - 0.0074*qSin(dr*(M-Mpr)) + 0.0004*qSin(dr*(2*F+M));
    C1 = C1 - 0.0004*qSin(dr*(2*F-M)) - 0.0006*qSin(dr*(2*F+Mpr));
    C1 = C1 + 0.0010*qSin(dr*(2*F-Mpr)) + 0.0005*qSin(dr*(2*Mpr+M));
    if (T < -11) {
        deltat= 0.001 + 0.000839*T + 0.0002261*T2 - 0.00000845*T3 - 0.000000081*T*T3;
    } else {
        deltat= -0.000278 + 0.000265*T + 0.000262*T2;
    };
    JdNew = Jd1 + C1 - deltat;
    qInfo() << JdNew;
    qint64  jd = (qint64)(JdNew + 0.5 + timeZone/24);
    qInfo() << jd;
    return jd;
}

qint64 AmLich::getMonthOfAmLichByJd(qint64 jd) {
    return (qint64)((jd-2415021)/29.530588853);
}
