#ifndef GOOGLECALENDARTOOL_H
#define GOOGLECALENDARTOOL_H

#include <QObject>
#include "afxstd.h"
#include "DatabaseManager/calendar.h"
#include "errorcode.h"

class GoogleCalendarTool : public QObject
{
public:
    static GoogleCalendarTool* getInstance();
    ErrorCode getCalendars(QString access_token, QList<Calendar> &listCalendar);

private:
    GoogleCalendarTool(QObject* parent = NULL);

private slots:
    void receivedResponseMessage(QNetworkReply *replyMessage);

private:
    static GoogleCalendarTool* instance;
    QNetworkAccessManager m_networkAccessManager;

};

#endif // GOOGLECALENDARTOOL_H
