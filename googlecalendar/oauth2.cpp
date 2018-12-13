#include "oauth2.h"
#include <QDebug>
#include <QSettings>
#include <QUrl>
#include <QDesktopServices>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QEventLoop>


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

//    m_networkAccessManager = new QNetworkAccessManager(this);
//    connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(receivedResponseMessage(QNetworkReply*)), Qt::DirectConnection);

}

//void OAuth2::receivedResponseMessage(QNetworkReply* replyMessage)
//{
//    QString content = (QString) replyMessage->readAll();
//    QJsonParseError error;
//    QJsonDocument jDoc = QJsonDocument::fromJson(content.toUtf8(), &error);
//    if (jDoc.isNull() || jDoc.isEmpty()) {
//        qCritical() << "Error: Parse message, " << error.errorString();
//        return;
//    }
//    QJsonObject jObj = jDoc.object();
//    m_strAccessToken = jObj.value(ACCESS_TOKEN).toString();
//    m_refreshToken = jObj.value(REFRESH_TOKEN).toString();
//    m_tokenType = jObj.value(TOKEN_TYPE).toString();

//    qDebug() << "access_token = " << m_strAccessToken;

//    emit loginDone();
//}

void OAuth2::OnReceivedAuthCode(QString authCode)
{
    m_authCode = authCode;
    delete httpListener;
    emit finishedGetAuthCode();
}

QString OAuth2::accessToken()
{
    return m_strAccessToken;
}

bool OAuth2::isAuthorized()
{
    return !m_strAccessToken.isEmpty();
}

ErrorCode OAuth2::startLogin(QString m_strScope)
{
    ErrorCode ret = Success;
    if(m_strClientID.isEmpty() || m_strRedirectURI.isEmpty())
    {
        ret = ApplicationNotReady;
        goto finished;
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

        QEventLoop eventLoop;
        QTimer timer;
        timer.setSingleShot(true);
        connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
        connect(this, SIGNAL(finishedGetAuthCode()), &eventLoop, SLOT(quit()));
        timer.start(TIME_OUT_WAIT_LOGIN);
        eventLoop.exec();

        if (!timer.isActive()) {
            timer.stop();
            ret = TimeOut;
            goto finished;
        }
    }

    if (m_refreshToken.isEmpty())
    {
        ret = getAccessToken();
        if (ret != Success) {
            goto finished;
        }
    }

    if (m_strAccessToken.isEmpty() /*or access_token expires*/)
    {
        //refresh access_token by refresh_token
    }

finished:
    emit loginDone(ret);
    return ret;

}

void OAuth2::logout()
{
    QString logoutUrl = "https://accounts.google.com/logout";
    QString requestStr = logoutUrl + "/access_token=" + m_strAccessToken;
    QNetworkRequest request;
    request.setUrl(requestStr);
    m_networkAccessManager.get(request);
}

ErrorCode OAuth2::getAccessToken()
{
    ErrorCode ret = Success;
    QJsonObject jObj;
    QJsonValue valueObj;
    //request POST message to get access token
    QString strData = QString("grant_type=authorization_code&code=%1&redirect_uri=%2&client_id=%3&client_secret=%4").arg(m_authCode).arg(m_strRedirectURI).arg(m_strClientID).arg(m_strClientSecret);

    QNetworkRequest request;
    request.setUrl(m_strEndPointToken);
    QNetworkReply* replyMessage = m_networkAccessManager.post(request, strData.toUtf8());

    QEventLoop eventLoop;
    connect(replyMessage, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();


    QString content = (QString) replyMessage->readAll();
    QJsonParseError error;
    QJsonDocument jDoc = QJsonDocument::fromJson(content.toUtf8(), &error);
    if (jDoc.isNull() || jDoc.isEmpty()) {
        qCritical() << "Error: Parse message, " << error.errorString();
        ret = JsonIncorrectFormat;
        goto finish_getAccessToken;
    }
    jObj = jDoc.object();
    if((valueObj = jObj.value(ACCESS_TOKEN)) != QJsonValue::Undefined) {
        m_strAccessToken = valueObj.toString();
    }
    else
    {
        ret = ValueInvalidate;
        goto finish_getAccessToken;
    }

    if((valueObj = jObj.value(REFRESH_TOKEN)) != QJsonValue::Undefined) {
        m_refreshToken = valueObj.toString();
    }
    if((valueObj = jObj.value(TOKEN_TYPE)) != QJsonValue::Undefined) {
        m_tokenType = valueObj.toString();
    }

    qDebug() << "access_token = " << m_strAccessToken;

finish_getAccessToken:
    return ret;

}



