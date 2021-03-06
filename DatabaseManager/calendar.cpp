#include "calendar.h"

Calendar::Calendar()
{

}

Calendar::~Calendar()
{

}

ErrorCode Calendar::addEvent(Event* event)
{
    ErrorCode ret = Success;
    if (m_events.find(event->getEventId()) == m_events.end())
    {
        m_events.insert(event->getEventId(), event);
    }
    else
    {
        ret = Existed;
    }
    return ret;
}

ErrorCode Calendar::deleteEvent(Event* event)
{
    ErrorCode ret = Success;
    if (m_events.find(event->getEventId()) != m_events.end())
    {
        m_events.remove(event->getEventId());
    }
    else
    {
        ret = Empty;
    }
    return ret;
}

ErrorCode Calendar::getEvent(QString id, Event *&outputEvent)
{
    ErrorCode ret = Success;
    QMap<QString, Event*>::const_iterator i = m_events.find(id);
    if (i != m_events.end())
    {
        outputEvent = i.value();
    }
    else
    {
        ret = Empty;
    }
    return ret;
}

ErrorCode Calendar::getNumberEvent(qint32 &numberEvent)
{
    ErrorCode ret = Success;
    numberEvent = m_events.count();
    return ret;
}

ErrorCode Calendar::importCSVFile(QString pathFile)
{
    Q_UNUSED(pathFile);
    ErrorCode ret = Success;
    return ret;
}

ErrorCode Calendar::exportCSVFile(QString pathFile)
{
    Q_UNUSED(pathFile);
    ErrorCode ret = Success;
    return ret;
}
