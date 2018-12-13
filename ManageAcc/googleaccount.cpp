#include "googleaccount.h"
#include "googlecalendar/googlecalendartool.h"

extern QSettings* appSettings;

GoogleAccount::GoogleAccount(QObject *parent) : Account(parent)
{
    m_pOauth2 = new OAuth2(appSettings);
}

GoogleAccount::~GoogleAccount()
{
}

void GoogleAccount::Login()
{
    m_pOauth2->startLogin(GOOGLE_CALENDAR_SCOPE);
}

void GoogleAccount::Logout()
{
    m_pOauth2->logout();
}

void GoogleAccount::Synchronize()
{
    QList<Calendar> listCalendar;
    GoogleCalendarTool::getInstance()->getCalendars(m_pOauth2->accessToken(), listCalendar);
//    qDebug() << "Number calendar = " << listCalendar.count();
//    for (int i = 0; i < listCalendar.count(); i++) {
//        qDebug() << listCalendar[i].calendarId;
//    }
}
