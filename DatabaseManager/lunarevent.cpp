#include "lunarevent.h"

LunarEvent::LunarEvent()
{

}

ErrorCode LunarEvent::updateDateFromLunarDate()
{
    ErrorCode ret = Success;
    setDate(m_lunarDate.toSolarDate());
    return ret;
}
