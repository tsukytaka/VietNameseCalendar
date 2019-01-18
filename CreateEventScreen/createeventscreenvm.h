#ifndef CREATEEVENTSCREENVM_H
#define CREATEEVENTSCREENVM_H

#include <QObject>
#include <QTimeZone>

class CreateEventScreenVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString placeHolderTextTitle READ placeHolderTextTitle WRITE setPlaceHolderTextTitle NOTIFY placeHolderTextTitleChanged)
    Q_PROPERTY(QString eventTitle READ placeHolderTextTitle WRITE setEventTitle NOTIFY eventTitleChanged)
    Q_PROPERTY(QString connectDateText READ connectDateText WRITE setConnectDateText NOTIFY connectDateTextChanged)
    Q_PROPERTY(bool isAllDay READ isAllDay WRITE setIsAllDay NOTIFY isAllDayChanged)
    Q_PROPERTY(QString textAllDay READ textAllDay WRITE setTextAllDay NOTIFY textAllDayChanged)


public:
    explicit CreateEventScreenVM(QObject *parent = 0);

    inline QString placeHolderTextTitle() { return m_placeHolderTextTitle; }
    inline void setPlaceHolderTextTitle(QString txt) { m_placeHolderTextTitle = txt; }
    inline QString eventTitle() { return m_eventTitle; }
    inline void setEventTitle(QString txt) { m_eventTitle = txt; }
    inline QString connectDateText() { return m_connectDateText; }
    inline void setConnectDateText(QString txt) { m_connectDateText = txt; }
    inline QString textAllDay() { return m_textAllDay; }
    inline void setTextAllDay(QString txt) { m_textAllDay = txt; }
    inline bool isAllDay() { return m_isAllDay; }
    inline void setIsAllDay(bool value) { m_isAllDay = value; emit isAllDayChanged(); }

    void updateText();
    void updateIcon();

    Q_INVOKABLE void CreateEvent();

signals:
    void placeHolderTextTitleChanged();
    void eventTitleChanged();
    void connectDateTextChanged();
    void textAllDayChanged();
    void isAllDayChanged();

public slots:


private:
    QString m_placeHolderTextTitle;
    QString m_eventTitle;
    QString m_connectDateText;
    QDateTime m_startDateTime;
    QDateTime m_endDateTime;
    QTimeZone m_timeZoneStart;
    QTimeZone m_timeZoneEnd;
    bool m_isAllDay;
    QString m_textAllDay;

};

#endif // CREATEEVENTSCREENVM_H
