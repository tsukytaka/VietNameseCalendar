#ifndef GOOGLECALENDARTOOL_H
#define GOOGLECALENDARTOOL_H

#include <QObject>
#include "DatabaseManager/calendar.h"
#include <QNetworkAccessManager>

class GoogleCalendarTool : public QObject
{
public:
    GoogleCalendarTool* getInstance();
//    QList<Calendar> getCalendars(QString acces_token);

private:
    GoogleCalendarTool(QObject* parent = NULL);

private slots:
    void receivedResponseMessage(QNetworkReply *replyMessage);

private:
    static GoogleCalendarTool* instance;
    QNetworkAccessManager *m_networkAccessManager;

};

#endif // GOOGLECALENDARTOOL_H
