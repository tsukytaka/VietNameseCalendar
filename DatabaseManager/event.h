#ifndef EVENT_H
#define EVENT_H
#include "afxstd.h"
#include <QObject>

class Event
{
public:
    enum EVENT_TYPE{
        LUNAR,
        GOOGLE,
    };

public:
    Event();
    virtual ~Event();
    Event(QString id);
    Event(const Event& src);

    inline void setEventId(const QString id) {m_eventId = id; }
    inline QString getEventId() const {return m_eventId; }

    inline void setType (const EVENT_TYPE type) {m_type = type; }
    inline EVENT_TYPE getType() const {return m_type; }

    inline void setDate(const QDate date) {m_date = date; }
    inline QDate getDate() const {return m_date; }

    inline void setStartTime(const QTime startTime) {m_startTime = startTime; }
    inline QTime getStartTime() const {return m_startTime; }

    inline void setEndTime(const QTime endTime) {m_endTime = endTime; }
    inline QTime getEndTime() const {return m_endTime; }

    inline void setTitle(const QString title) {m_title = title; }
    inline QString getTitle() const {return m_title; }

    inline void setContent(const QString content) {m_content = content; }
    inline QString getContent() const {return m_content; }

private:
    QString m_eventId;
    EVENT_TYPE m_type;
    QDate m_date;
    QTime m_startTime;
    QTime m_endTime;
    QString m_title;
    QString m_content;

};

#endif // EVENT_H
