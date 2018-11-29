#include "account.h"

Account::Account(QObject *parent) : QObject(parent)
{
    m_type = GoogleType;
    m_name = "";
    m_color = QColor(0,0,0);
}
