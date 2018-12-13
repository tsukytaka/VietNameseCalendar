#include "googlecalendartool.h"
#include <QNetworkRequest>
#define GOOGLE_CALENDAR_URI "https://www.googleapis.com/calendar/v3"


GoogleCalendarTool* GoogleCalendarTool::instance = NULL;

GoogleCalendarTool::GoogleCalendarTool(QObject *parent) : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager();
    connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(receivedResponseMessage(QNetworkReply*)), Qt::DirectConnection);
}

GoogleCalendarTool* GoogleCalendarTool::getInstance()
{
    if (!instance) {
        instance = new GoogleCalendarTool();
    }
    return instance;
}

void GoogleCalendarTool::receivedResponseMessage(QNetworkReply *replyMessage)
{

}


//QList<Calendar> GoogleCalendarTool::getCalendars(QString access_token)
//{
//    QString requestStr = QString(GOOGLE_CALENDAR_URI) + "/users/me/calendarList" + "/access_token=" + access_token;
//    QNetworkRequest request;
//    request.setUrl(requestStr);
//    m_networkAccessManager->get(request);
//    return NULL;
//}
