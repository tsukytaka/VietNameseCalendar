#include "accountmanager.h"

AccountManager *AccountManager::instance = NULL;

AccountManager::AccountManager()
{

}

AccountManager* AccountManager::getInstance()
{
    if (!instance)
    {
        instance = new AccountManager();
    }
    return instance;
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
