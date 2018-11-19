#include "oauth2.h"
#include <QDebug>
#include <QSettings>
#include <QUrl>
#include <QDesktopServices>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>


OAuth2::OAuth2(QSettings *settings, QObject *parent): QObject(parent)
{
    m_strEndPointAuth = "";
    m_strEndPointToken = "";
    m_strClientID = "";
    m_strClientSecret = "";
    m_strRedirectURI = "";

    /*
     * read google credential oauth2
     */
    QFile f(GOOGLE_CLIENT_SECRET_PATH_FILE);
    if (f.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&f);
        QString content = in.readAll();
        qDebug() << "content = " << content;
        QJsonParseError error;
        QJsonDocument jDoc = QJsonDocument::fromJson(content.toUtf8(), &error);
        if (jDoc.isNull() || jDoc.isEmpty()) {
            qCritical() << "Error: Parse message, " << error.errorString();
            return;
        }
        QJsonObject rootObj = jDoc.object();
        QJsonObject installedObj = (*rootObj.begin()).toObject();

        m_strClientID = installedObj.value(CLIENT_ID).toString();
        m_strClientSecret = installedObj.value(CLIENT_SECRET).toString();
        m_strEndPointAuth = installedObj.value(AUTH_URI).toString();
        m_strEndPointToken = installedObj.value(TOKEN_URI).toString();
        m_strRedirectURI = installedObj.value(REDIRECT_URIS).toString();
    }

    settings->beginGroup(GOOGLE_GROUP_NAME);
    this->settings = settings;

    m_networkAccessManager = new QNetworkAccessManager(this);
    connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(receivedResponseMessage(QNetworkReply*)));

}

void OAuth2::receivedResponseMessage(QNetworkReply* replyMessage)
{
    QString content = (QString) replyMessage->readAll();
    QJsonParseError error;
    QJsonDocument jDoc = QJsonDocument::fromJson(content.toUtf8(), &error);
    if (jDoc.isNull() || jDoc.isEmpty()) {
        qCritical() << "Error: Parse message, " << error.errorString();
        return;
    }
    QJsonObject jObj = jDoc.object();
    m_strAccessToken = jObj.value(ACCESS_TOKEN).toString();
    m_refreshToken = jObj.value(REFRESH_TOKEN).toString();
    m_tokenType = jObj.value(TOKEN_TYPE).toString();

    qDebug() << "access_token = " << m_strAccessToken;

    emit loginDone();
}

void OAuth2::OnReceivedAuthCode(QString authCode)
{
    m_authCode = authCode;
    getAccessToken();
    delete httpListener;
}

QString OAuth2::accessToken()
{
    return m_strAccessToken;
}

bool OAuth2::isAuthorized()
{
    return !m_strAccessToken.isEmpty();
}

void OAuth2::startLogin(QString m_strScope)
{
    if(m_strClientID.isEmpty() || m_strRedirectURI.isEmpty())
    {
        return;
    }

    if(m_authCode.isEmpty())
    {
        /*
         * Start httplistener to be received authentical code
         */
        QSettings* listenerSettings = new QSettings(settings);
        listenerSettings->beginGroup(LISTENER_GROUP_NAME);
        HttpRequestHandler *httpRequestHanler =  new HttpRequestHandler(this);
        QObject::connect(httpRequestHanler, SIGNAL(receivedAuthCode(QString)), SLOT(OnReceivedAuthCode(QString)));
        httpListener = new HttpListener(listenerSettings, httpRequestHanler, this);

        QString str = QString("%1?client_id=%2&redirect_uri=%3&response_type=%4&scope=%5").arg(m_strEndPointAuth).arg(m_strClientID).
                arg(m_strRedirectURI).arg("code").arg(m_strScope);
        QDesktopServices::openUrl(QUrl(str));
    }
    else if (m_refreshToken.isEmpty())
    {
        getAccessToken();
    }
    else if (m_strAccessToken.isEmpty() /*or access_token expires*/)
    {
        //refresh access_token by refresh_token
    }
    else
    {
        emit loginDone();
    }
}

void OAuth2::logout()
{
    QString logoutUrl = "https://accounts.google.com/logout";
    QString requestStr = logoutUrl + "/access_token=" + m_strAccessToken;
    QNetworkRequest request;
    request.setUrl(requestStr);
    m_networkAccessManager->get(request);
}

void OAuth2::getAccessToken()
{
    //request POST message to get access token
    QString strData = QString("grant_type=authorization_code&code=%1&redirect_uri=%2&client_id=%3&client_secret=%4").arg(m_authCode).arg(m_strRedirectURI).arg(m_strClientID).arg(m_strClientSecret);

    QNetworkRequest request;
    request.setUrl(m_strEndPointToken);
    m_networkAccessManager->post(request, strData.toUtf8());
}



