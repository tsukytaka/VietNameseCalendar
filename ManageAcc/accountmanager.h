#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QObject>
#include "account.h"
#include "googleaccount.h"

class AccountManager : public QObject
{
    Q_OBJECT
public:
    explicit AccountManager(QObject *parent = 0);

    void addAccount(Account::TYPE_ACC type);
    void deleteAccount(QString name);

signals:

public slots:

private:
    QList<Account*> listAccount;
};

#endif // ACCOUNTMANAGER_H
