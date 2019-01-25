#include "lunarevent.h"

LunarEvent::LunarEvent()
{

}

ErrorCode LunarEvent::updateDateFromLunarDate()
{
    ErrorCode ret = Success;
    setStartDate(m_startLunarDate.toSolarDate());
    setEndDate(m_endLunarDate.toSolarDate());
    return ret;
}
