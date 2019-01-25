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
    virtual ~Calendar();

    inline QString calendarId() const {return m_calendarId; }
    inline void setCalendarId(QString calendarId) {m_calendarId = calendarId; }
    inline QString calendarName() const {return m_calendarName; }
    inline void setCalendarName(QString calendarName) {m_calendarName = calendarName; }
    inline QColor bgColor() const {return m_bgColor; }
    inline void setBgColor(QColor color) {m_bgColor = color; }
    inline QColor fgColor() const {return m_fgColor; }
    inline void setFgColor(QColor color) {m_fgColor = color; }
    inline QTimeZone timeZone() const {return m_timeZone; }
    inline void setTimeZone(QTimeZone timeZone) {m_timeZone = timeZone; }

    ErrorCode addEvent(Event* event);
    ErrorCode deleteEvent(Event* event);
    ErrorCode getEvent(QString id, Event *&outputEvent);
    ErrorCode getNumberEvent(qint32 &numberEvent);

    virtual ErrorCode importCSVFile(QString pathFile);
    virtual ErrorCode exportCSVFile(QString pathFile);

private:
    QString m_calendarId;
    QString m_calendarName;
    QColor m_bgColor;
    QColor m_fgColor;
    QTimeZone m_timeZone;
    QMap<QString, Event*> m_events;
};

#endif // CALENDAR_H
