#ifndef EVENTSSCREENVM_H
#define EVENTSSCREENVM_H

#include <QObject>

class EventsScreenVM : public QObject
{
    Q_OBJECT
public:
    explicit EventsScreenVM(QObject *parent = 0);

signals:

public slots:
};

#endif // EVENTSSCREENVM_H