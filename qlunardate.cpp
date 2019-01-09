#include "qlunardate.h"
#include "lunartools.h"

QLunarDate::QLunarDate(QObject *parent) : QObject(parent)
{
    m_y = 0;
    m_m = 0;
    m_d = 0;
    m_leap = 0;
}

QLunarDate::QLunarDate(const QLunarDate &lunarDate){
    m_y = lunarDate.year();
    m_m = lunarDate.month();
    m_d = lunarDate.day();
    m_leap = lunarDate.leap();
}

QLunarDate::~QLunarDate() {

}

QLunarDate &QLunarDate::operator =(const QLunarDate &lunarDate){
    m_y = lunarDate.year();
    m_m = lunarDate.month();
    m_d = lunarDate.day();
    m_leap = lunarDate.leap();
    return (*this);
}

QLunarDate::QLunarDate(qint32 year, qint32 month, qint32 day, qint32 leap){
    m_y = year;
    m_m = month;
    m_d = day;
    m_leap = leap;
}

QLunarDate::QLunarDate(const QDate &date)
{
    QLunarDate* lunarDate = LunarTools::convertSolar2Lunar(date, TIME_ZONE);
    m_y = lunarDate->year();
    m_m = lunarDate->month();
    m_d = lunarDate->day();
    m_leap = lunarDate->leap();
}

void QLunarDate::setDate(int year, int month, int day){
    m_y = year;
    m_m = month;
    m_d = day;
}

QDate QLunarDate::toSolarDate()
{
    return LunarTools::convertLunar2Solar(*this, TIME_ZONE);
}
