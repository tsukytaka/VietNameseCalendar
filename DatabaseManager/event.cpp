#include "event.h"

Event::Event()
{

}

Event::~Event()
{

}

Event::Event(const Event& src)
{
    m_eventId = src.getEventId();
    m_startDate = src.getStartDate();
    m_endDate = src.getEndDate();
    m_startTime = src.getStartTime();
    m_endTime = src.getEndTime();
    m_title = src.getTitle();
    m_content = src.getContent();
}
