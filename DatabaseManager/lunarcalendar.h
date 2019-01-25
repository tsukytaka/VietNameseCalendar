#ifndef LUNARCALENDAR_H
#define LUNARCALENDAR_H

#include <QObject>
#include "calendar.h"

class LunarCalendar : public Calendar
{
public:
    LunarCalendar();

    ErrorCode importCSVFile(QString pathFile) override;
    ErrorCode exportCSVFile(QString pathFile) override;
};

#endif // LUNARCALENDAR_H
