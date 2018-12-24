#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include "afxstd.h"
#include "event.h"
#include "errorcode.h"


class Calendar
{
public:
    Calendar();
    void addEvent(Event event);


private:
    QString calendarId;
    QColor bgColor;
    QColor fgColor;
    QTimeZone timeZone;
    QList<Event> events;
};

#endif // CALENDAR_H
