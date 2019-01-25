#ifndef LUNAREVENT_H
#define LUNAREVENT_H
#include "event.h"
#include "qlunardate.h"

class LunarEvent : public Event
{
public:
    LunarEvent();

    inline void setStartLunarDate(const QLunarDate lunarDate) {m_startLunarDate = lunarDate; }
    inline QLunarDate getStartLunarDate() const {return m_startLunarDate; }

    inline void setEndLunarDate(const QLunarDate lunarDate) {m_endLunarDate = lunarDate; }
    inline QLunarDate getEndLunarDate() const {return m_endLunarDate; }

    ErrorCode updateDateFromLunarDate();

private:
    QLunarDate m_startLunarDate;
    QLunarDate m_endLunarDate;
};

#endif // LUNAREVENT_H
