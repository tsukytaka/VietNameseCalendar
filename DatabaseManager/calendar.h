#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include "event.h"


class Calendar
{
public:
    Calendar();


private:
    QString calendarId;
    QList<Event> events;
};

#endif // CALENDAR_H
