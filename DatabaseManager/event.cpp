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
    m_date = src.getDate();
    m_startTime = src.getStartTime();
    m_endTime = src.getEndTime();
    m_title = src.getTitle();
    m_content = src.getContent();
}
