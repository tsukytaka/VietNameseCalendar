#ifndef GOOGLEACCOUNT_H
#define GOOGLEACCOUNT_H

#include "account.h"
#include "googlecalendar/oauth2.h"

class GoogleAccount : public Account
{
    Q_OBJECT
public:
    explicit GoogleAccount(QObject *parent = 0);
    ~GoogleAccount() override;

    void Login() override;
    void Logout() override;
    void Synchronize() override;

signals:

public slots:

private:
    OAuth2* m_pOauth2;
};

#endif // GOOGLEACCOUNT_H
