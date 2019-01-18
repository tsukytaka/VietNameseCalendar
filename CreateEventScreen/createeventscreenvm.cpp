#include "createeventscreenvm.h"

CreateEventScreenVM::CreateEventScreenVM(QObject *parent) : QObject(parent)
{
    m_isAllDay = true;
    updateText();

}

void CreateEventScreenVM::updateText()
{
    m_placeHolderTextTitle = "Add title";
    m_connectDateText = "To";
    m_textAllDay = "All day";

}

void CreateEventScreenVM::updateIcon()
{

}

void CreateEventScreenVM::CreateEvent()
{

}
