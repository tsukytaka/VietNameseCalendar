#include "accountmanager.h"

AccountManager::AccountManager(QObject *parent) : QObject(parent)
{

}

void AccountManager::addAccount(Account::TYPE_ACC type)
{
    if (type == Account::TYPE_ACC::GoogleType)
    {
        GoogleAccount* googleAcc = new GoogleAccount();
        listAccount.append(googleAcc);
        googleAcc->Login();
    }
    else if (type == Account::TYPE_ACC::VnmcType)
    {

    }
    else
    {

    }
}

void AccountManager::deleteAccount(QString name)
{

}
