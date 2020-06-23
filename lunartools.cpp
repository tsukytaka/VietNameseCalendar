#include "lunartools.h"
#include <QtMath>
#include <QDebug>

LunarTools* LunarTools::instance = nullptr;

LunarTools::LunarTools(QObject *parent) : QObject(parent)
{

}

LunarTools* LunarTools::getInstance() {
    if (!instance) {
        instance = new LunarTools();
    }
    return instance;
}

// First, define the singleton type provider function (callback).
QObject *LunarTools::qobject_lunartools_provider(QQmlEngine *engine, QJSEngine *scriptEngine){
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    LunarTools *ins = getInstance();
    return ins;
}

qint64 LunarTools::getMonthOfLunarByJd(qint64 jd) {
    return qint64((jd-NEWMOON_IN_JAN_01_1990_JD)/AVG_NUMBER_DAY_IN_MONTH);
}

qint64 LunarTools::getNewMoonDay(qint64 monthOfLunar, qint32 timeZone) {
    qreal T, T2, T3, dr, Jd1, M, Mpr, F, C1, deltat, JdNew;
    T = monthOfLunar/(AVG_NUMBER_LUNAR_MONTH_IN_YEAR*100); // Time in Julian centuries from 1900 January 0.5
    T2 = T * T;
    T3 = T2 * T;
    dr = PI/180;
    Jd1 = START_IN_JAN_01_1990_JD + AVG_NUMBER_DAY_IN_MONTH*monthOfLunar + 0.0001178*T2 - 0.000000155*T3;
    Jd1 = Jd1 + 0.00033*qSin((166.56 + 132.87*T - 0.009173*T2)*dr); // Mean new moon
    M = 359.2242 + 29.10535608*monthOfLunar - 0.0000333*T2 - 0.00000347*T3; // Sun's mean anomaly
    Mpr = 306.0253 + 385.81691806*monthOfLunar + 0.0107306*T2 + 0.00001236*T3; // Moon's mean anomaly
    F = 21.2964 + 390.67050646*monthOfLunar - 0.0016528*T2 - 0.00000239*T3; // Moon's argument of latitude
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
    qint64  jd = qint64(JdNew + 0.5 + timeZone/24.0);
    return jd;
}



qint64 LunarTools::getSunLongitude(qint64 jdn, qint32 timeZone){
    qreal T, T2, dr, M, L0, DL, L;
    T = (jdn - 2451545.5 - timeZone/24.0) / 36525; // Time in Julian centuries from 2000-01-01 12:00:00 GMT
    T2 = T*T;
    dr = PI/180; // degree to radian
    M = 357.52910 + 35999.05030*T - 0.0001559*T2 - 0.00000048*T*T2; // mean anomaly, degree
    L0 = 280.46645 + 36000.76983*T + 0.0003032*T2; // mean longitude, degree
    DL = (1.914600 - 0.004817*T - 0.000014*T2)*qSin(dr*M);
    DL = DL + (0.019993 - 0.000101*T)*qSin(dr*2*M) + 0.000290*qSin(dr*3*M);
    L = L0 + DL; // true longitude, degree
    L = L*dr;
    L = L - PI*2*(qint32(L/(PI*2))); // Normalize to (0, 2*PI)
    return qint64(L / PI * 6);
}

qint64 LunarTools::getLunarMonth11(qint32 yy, qint32 timeZone){
    qreal k, off, sunLong;
    qint64 nm;
    QDate date(yy, 12, 31);
    off = date.toJulianDay() - 2415021;
    k = qint32(off / 29.530588853);
    nm = getNewMoonDay(qint64(k), timeZone);
    sunLong = getSunLongitude(qint64(nm), timeZone); // sun longitude at local midnight
    if (sunLong >= 9) {
        nm = getNewMoonDay(qint64(k)-1, timeZone);
    }
    return nm;
}

qint32 LunarTools::getLeapMonthOffset(qint32 a11, qint32 timeZone){
    qint64 last, arc;
    qint64 k, i;
    k = qint64((a11 - 2415021.076998695) / 29.530588853 + 0.5);
    last = 0;
    i = 1; // We start with the month following lunar month 11
    arc = getSunLongitude(getNewMoonDay(k+i, timeZone), timeZone);
    do {
        last = arc;
        i++;
        arc = getSunLongitude(getNewMoonDay(k+i, timeZone), timeZone);
    } while (arc != last && i < 14);
    return qint32(i-1);
}

QLunarDate* LunarTools::convertSolar2Lunar(QDate date, qint32 timeZone)
{
    qint32 lunarYear, lunarMonth, lunarDay, lunarLeap;
    qint32 yy;
    yy = date.year();
//    mm = date.month();
//    dd = date.day();
    qint64 k, dayNumber, monthStart, a11, b11;
    dayNumber = date.toJulianDay();
//    qInfo() << "dayNumber = " << dayNumber;
    k = qint32((dayNumber - NEWMOON_IN_JAN_01_1990_JD) / AVG_NUMBER_DAY_IN_MONTH);
//    qInfo() << "k = " << k;
    monthStart = getNewMoonDay(k+1, timeZone);

//    qInfo() << "monthStart k+1 = " << monthStart;

    if (monthStart > dayNumber) {
        monthStart = getNewMoonDay(k, timeZone);
    }

//    qInfo() << "monthStart k = " << monthStart;

    a11 = getLunarMonth11(yy, timeZone);
    b11 = a11;
    if (a11 >= monthStart) {
        lunarYear = yy;
        a11 = getLunarMonth11(yy-1, timeZone);
    } else {
        lunarYear = yy+1;
        b11 = getLunarMonth11(yy+1, timeZone);
    }

//    if (date.day() == 5) {
//        qInfo() << "a11 = " << a11;
//        qInfo() << "b11 = " << b11;
//    }

    lunarDay = qint32(dayNumber-monthStart+1);
    qint32 diff = qint32((monthStart - a11)/29);
    lunarLeap = 0;
    lunarMonth = diff + 11;
    if (b11 - a11 > 365) {
        qint32 leapMonthDiff = getLeapMonthOffset(qint32(a11), timeZone);
        if (diff >= leapMonthDiff) {
            lunarMonth = diff + 10;
            if (diff == leapMonthDiff) {
                lunarLeap = 1;
            }
        }
    }

    if (lunarMonth > 12) {
        lunarMonth = lunarMonth - 12;
    }

    if (lunarMonth >= 11 && diff < 4) {
        lunarYear -= 1;
    }

    QLunarDate* lunarDate = new QLunarDate(lunarYear, lunarMonth, lunarDay, lunarLeap);

    return lunarDate;
}

QDate LunarTools::convertLunar2Solar(QLunarDate lunarDate, qint32 timeZone){
    qint64 k, off, leapOff, leapMonth, monthStart;
    qint64 a11, b11;
    if (lunarDate.month() < 11) {
        a11 = getLunarMonth11(lunarDate.year()-1, timeZone);
        b11 = getLunarMonth11(lunarDate.year(), timeZone);
    } else {
        a11 = getLunarMonth11(lunarDate.year(), timeZone);
        b11 = getLunarMonth11(lunarDate.year()+1, timeZone);
    }
    off = lunarDate.month() - 11;
    if (off < 0) {
        off += 12;
    }
    if (b11 - a11 > 365) {
        leapOff = getLeapMonthOffset(qint32(a11), timeZone);
        leapMonth = leapOff - 2;
        if (leapMonth < 0) {
            leapMonth += 12;
        }
        if (lunarDate.leap() != 0 && lunarDate.month() - leapMonth != 0) {
            return QDate(0, 0, 0);
        } else if (lunarDate.leap() != 0 || off >= leapOff) {
            off += 1;
        }
    }
    k = qint32(0.5 + (a11 - 2415021.076998695) / 29.530588853);
    monthStart = getNewMoonDay(k+off, timeZone);
    return QDate::fromJulianDay(monthStart+lunarDate.day()-1);
}
