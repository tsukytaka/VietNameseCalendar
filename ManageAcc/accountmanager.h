#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "account.h"
#include "googleaccount.h"

class AccountManager
{

public:
    AccountManager* getInstance();
    void addAccount(Account::TYPE_ACC type);
    void deleteAccount(QString name);

signals:

public slots:

private:
    AccountManager();

private:
    static AccountManager *instance;
    QList<Account*> listAccount;
};

#endif // ACCOUNTMANAGER_H
