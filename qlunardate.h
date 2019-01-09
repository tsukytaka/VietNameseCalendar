#ifndef QLUNARDATE_H
#define QLUNARDATE_H

#include <QObject>
#include <QMetaType>

class QLunarDate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 year READ year WRITE setYear NOTIFY yearChanged)
    Q_PROPERTY(qint32 month READ month WRITE setMonth NOTIFY monthChanged)
    Q_PROPERTY(qint32 day READ day WRITE setDay NOTIFY dayChanged)

public:
    explicit QLunarDate(QObject *parent = nullptr);
    QLunarDate(const QLunarDate &lunarDate);
    QLunarDate(qint32 year, qint32 month, qint32 day, qint32 leap);
    QLunarDate(const QDate &date);
    QLunarDate &operator = (const QLunarDate &lunarDate);
    ~QLunarDate();

    inline qint32 year() const {return m_y; }
    inline void setYear(qint32 year) { m_y = year; emit yearChanged(); }
    inline qint32 month() const {return m_m; }
    inline void setMonth(qint32 month) { m_m = month; emit monthChanged(); }
    inline qint32 day() const {return m_d; }
    inline void setDay(qint32 day) { m_d = day; emit dayChanged(); }
    inline qint32 leap() const {return m_leap; }
    inline void setLeap(int leap) {m_leap = leap; emit leapChanged(); }


    void setDate(int year, int month, int day);
    QDate toSolarDate();

private:
    qint32 m_d;
    qint32 m_m;
    qint32 m_y;
    qint32 m_leap;

signals:
    void yearChanged();
    void monthChanged();
    void dayChanged();
    void leapChanged();


public slots:
};

Q_DECLARE_METATYPE(QLunarDate*)

#endif // QLUNARDATE_H
