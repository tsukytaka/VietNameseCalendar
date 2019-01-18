#ifndef GOOGLECALENDAR_H
#define GOOGLECALENDAR_H

#include "afxstd.h"
#include "solarcalendar.h"

class GoogleCalendar : public SolarCalendar
{
public:
    GoogleCalendar();

private:
    QString kind;
    QString etag;
    QString summary;
    QString accessRole;
};

#endif // GOOGLECALENDAR_H
