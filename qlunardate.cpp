#include "qlunardate.h"

QLunarDate::QLunarDate(QObject *parent) : QObject(parent)
{
    y = 0;
    m = 0;
    d = 0;
}

QLunarDate::QLunarDate(const QLunarDate &lunarDate){
    this->y = lunarDate.year();
    this->m = lunarDate.month();
    this->d = lunarDate.day();
}

QLunarDate::~QLunarDate() {

}

QLunarDate &QLunarDate::operator =(const QLunarDate &lunarDate){
    this->y = lunarDate.year();
    this->m = lunarDate.month();
    this->d = lunarDate.day();
    return (*this);
}

QLunarDate::QLunarDate(int year, int month, int day){
    this->y = year;
    this->m = month;
    this->d = day;
}

int QLunarDate::year() const{
    return y;
}

void QLunarDate::setYear(int year) {
    y = year;
    emit yearChanged();
}

int QLunarDate::month() const{
    return m;
}

void QLunarDate::setMonth(int month) {
    m = month;
    emit monthChanged();
}

int QLunarDate::day() const{
    return d;
}

void QLunarDate::setDay(int day) {
    d = day;
    emit dayChanged();
}

void QLunarDate::setDate(int year, int month, int day){
    y = year;
    m = month;
    d = day;
}
