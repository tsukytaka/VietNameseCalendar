#ifndef QLUNARDATE_H
#define QLUNARDATE_H

#include <QObject>
#include <QMetaType>

class QLunarDate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int year READ year WRITE setYear NOTIFY yearChanged)
    Q_PROPERTY(int month READ month WRITE setMonth NOTIFY monthChanged)
    Q_PROPERTY(int day READ day WRITE setDay NOTIFY dayChanged)

public:
    explicit QLunarDate(QObject *parent = 0);
    QLunarDate(const QLunarDate &lunarDate);
    QLunarDate(int year, int month, int day);
    QLunarDate &operator = (const QLunarDate &lunarDate);
    ~QLunarDate();

    int year() const;
    void setYear(int year);
    int month() const;
    void setMonth(int month);
    int day() const;
    void setDay(int day);

    void setDate(int year, int month, int day);

private:
    int d;
    int m;
    int y;

signals:
    void yearChanged();
    void monthChanged();
    void dayChanged();


public slots:
};

Q_DECLARE_METATYPE(QLunarDate*)

#endif // QLUNARDATE_H
