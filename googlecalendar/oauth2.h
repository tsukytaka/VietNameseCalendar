#ifndef OAUTH2_H
#define OAUTH2_H

#include <QString>
#include <QObject>
#include <QSettings>

class OAuth2 : public QObject
{
    Q_OBJECT

public:
    OAuth2(QSettings* settings, QObject* parent = NULL);
    QString accessToken();
    bool isAuthorized();
    void startLogin(bool bForce);

    QString loginUrl();

signals:
    void loginDone();

private slots:
    void accessTokenObtained();

private:
    QString m_strAccessToken;

    QString m_strEndPointAuth;
    QString m_strScope;
    QString m_strClientID;
    QString m_strRedirectURI;
    QString m_strResponseType;

    QSettings* settings;
};

#endif // OAUTH2_H
