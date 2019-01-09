#ifndef LUNAREVENT_H
#define LUNAREVENT_H
#include "event.h"
#include "qlunardate.h"

class LunarEvent : public Event
{
public:
    LunarEvent();

    inline void setLunarDate(const QLunarDate lunarDate) {m_lunarDate = lunarDate; }
    inline QLunarDate getLunarDate() const {return m_lunarDate; }

    ErrorCode updateDateFromLunarDate();

private:
    QLunarDate m_lunarDate;
};

#endif // LUNAREVENT_H
