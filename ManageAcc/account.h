#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include "afxstd.h"
#include "DatabaseManager/calendar.h"

class Account : public QObject
{
    Q_OBJECT

public:
    explicit Account(QObject *parent = 0);
    inline virtual ~Account() {}

    enum TYPE_ACC{
        VnmcType,
        GoogleType,
    };

    inline TYPE_ACC getType(){return m_type;}
    inline void setType(TYPE_ACC type){m_type = type;}
    inline QString getName(){return m_name;}
    inline void setName(QString name){m_name = name;}
//    inline QColor getColor(){return m_color;}
//    inline void setColor(QColor color){m_color = color;}

    void addCalendar(Calendar cal);
    QList<Calendar> getCalendarList();

    inline virtual void Login(){}
    inline virtual void Logout(){}
    inline virtual void Synchronize(){}

signals:

public slots:

private:
    TYPE_ACC m_type;
    QString m_name;
    QList<Calendar> m_calendars;
//    QColor m_color;

};

#endif // ACCOUNT_H
