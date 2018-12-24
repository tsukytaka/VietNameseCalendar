#ifndef GOOGLECALENDAR_H
#define GOOGLECALENDAR_H

#include "afxstd.h"
#include "calendar.h"

class GoogleCalendar : public Calendar
{
public:
    GoogleCalendar();

private:
    QString kind;
    QString etag;
    QString summary;
    bool selected;
    QString accessRole;
};

#endif // GOOGLECALENDAR_H
