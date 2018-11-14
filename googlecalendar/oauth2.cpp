#include "oauth2.h"
#include <QDebug>
#include <QSettings>
#include <QUrl>
#include <QDesktopServices>

OAuth2::OAuth2(QSettings *settings, QObject *parent): QObject(parent)
{
    m_strEndPointAuth = "https://accounts.google.com/o/oauth2/auth";
    m_strScope = "https://www.googleapis.com/auth/calendar";
    m_strClientID = "760581500921-17vl6s2lsu2mi2qnscn1tqrbhsmvc5ga.apps.googleusercontent.com";
    m_strRedirectURI = "https://localhost:8080/authenticate";
    m_strResponseType = "code";

    this->settings = settings;
}

void OAuth2::accessTokenObtained()
{
//    m_strAccessToken = m_pLoginDialog->accessToken();
//    settings.setValue("access_token", m_strAccessToken);
//    m_pLoginDialog->setLoginUrl("");
    emit loginDone();

}


QString OAuth2::loginUrl()
{
    QString str = QString("%1?client_id=%2&redirect_uri=%3&response_type=%4&scope=%5").arg(m_strEndPointAuth).arg(m_strClientID).
            arg(m_strRedirectURI).arg(m_strResponseType).arg(m_strScope);
    qDebug() << "Login URL" << str;
    return str;
}

QString OAuth2::accessToken()
{
    return m_strAccessToken;
}

bool OAuth2::isAuthorized()
{
    return m_strAccessToken != "";
}

void OAuth2::startLogin(bool bForce)
{
    qDebug() << "OAuth2::startLogin";
    QString str = settings->value("access_token", "").toString();

    qDebug() << "OAuth2::startLogin, token from Settings" << str;

    if(m_strClientID == "YOUR_CLIENT_ID_HERE" || m_strRedirectURI == "YOUR_REDIRECT_URI_HERE")
    {
//        QMessageBox::warning(m_pParent, "Warning",
//                             "To work with application you need to register your own application in <b>Google</b>.\n"
//                             "Learn more from <a href='http://code.google.com/p/qt-google-calendar/wiki/HowToRegisterYourApplicationInGoogle'>here</a>");
        return;
    }


    if(str.isEmpty() || bForce)
    {
        QDesktopServices::openUrl(QUrl(loginUrl()));
    }
    else
    {
        m_strAccessToken = str;
        emit loginDone();
    }
}

