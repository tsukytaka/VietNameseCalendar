#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QObject>

class ScheduleItem : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleItem(QObject *parent = 0);

signals:

public slots:
};

#endif // SCHEDULEITEM_H