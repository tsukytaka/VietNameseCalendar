#ifndef QLUNARDATE_H
#define QLUNARDATE_H

#include <QObject>

class QLunarDate : public QObject
{
    Q_OBJECT
public:
    explicit QLunarDate(QObject *parent = 0);
    QLunarDate(const QLunarDate &lunarDate);
    QLunarDate(int year, int month, int day);
    QLunarDate &operator = (const QLunarDate &lunarDate);
    ~QLunarDate();

    int year() const;
    int month() const;
    int day() const;
    void setDate(int year, int month, int day);

private:
    int d;
    int m;
    int y;

signals:

public slots:
};

#endif // QLUNARDATE_H
