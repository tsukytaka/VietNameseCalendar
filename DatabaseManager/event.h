#ifndef EVENT_H
#define EVENT_H

#include <QObject>

class Event
{
public:
    Event();
    Event(QString id);

private:
    QString eventId;

};

#endif // EVENT_H
