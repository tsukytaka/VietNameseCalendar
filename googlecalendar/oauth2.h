#ifndef OAUTH2_H
#define OAUTH2_H

#include "afxstd.h"
#include "httpserver/httplistener.h"
#include "errorcode.h"

#define LISTENER_GROUP_NAME "HTTP_LISTENER"
#define GOOGLE_GROUP_NAME "GOOGLE"

#define GOOGLE_CALENDAR_SCOPE "https://www.googleapis.com/auth/calendar"
#define GOOGLE_CLIENT_SECRET_PATH_FILE ":/otherfile/client_secret_multi_platform.json"

#define CLIENT_ID "client_id"
#define PROJECT_ID "project_id"
#define AUTH_URI "auth_uri"
#define TOKEN_URI "token_uri"
#define AUTH_PROVIDER_URL "auth_provider_x509_cert_url"
#define CLIENT_SECRET "client_secret"
#define REDIRECT_URIS "redirect_uris"

#define REFRESH_TOKEN "refresh_token"
#define ACCESS_TOKEN "access_token"
#define TOKEN_TYPE "token_type"

#define TIME_OUT_WAIT_LOGIN 1800000


class OAuth2 : public QObject
{
    Q_OBJECT

public:
    OAuth2(QSettings* settings, QObject* parent = NULL);
    QString accessToken();
    bool isAuthorized();
    ErrorCode startLogin(QString m_strScope);
    ErrorCode getAccessToken();
    void logout();

signals:
    void loginDone(ErrorCode err);
    void finishedGetAuthCode();

private slots:
//    void receivedResponseMessage(QNetworkReply *replyMessage);
    void OnReceivedAuthCode(QString authCode);

private:
    QString m_strAccessToken;
    QString m_refreshToken;
    QString m_authCode;
    QString m_tokenType;

    QString m_strEndPointAuth;
    QString m_strEndPointToken;
    QString m_strClientID;
    QString m_strClientSecret;
    QString m_strRedirectURI;

    HttpListener *httpListener;
    QNetworkAccessManager m_networkAccessManager;
    QSettings* settings;
};

#endif // OAUTH2_H
