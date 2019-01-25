#ifndef SOLARCALENDAR_H
#define SOLARCALENDAR_H

#include <QObject>
#include "calendar.h"

class SolarCalendar : public Calendar
{
public:
    SolarCalendar();

    ErrorCode importCSVFile(QString pathFile) override;
    ErrorCode exportCSVFile(QString pathFile) override;
};

#endif // SOLARCALENDAR_H
