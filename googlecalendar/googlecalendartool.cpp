#include "googlecalendartool.h"

#define GOOGLE_CALENDAR_URI "https://www.googleapis.com/calendar/v3"
#define TIME_OUT_REQUEST 30000

#define ITEMS_TAG "items"

GoogleCalendarTool* GoogleCalendarTool::instance = nullptr;

GoogleCalendarTool::GoogleCalendarTool(QObject *parent) : QObject(parent)
{
}

GoogleCalendarTool* GoogleCalendarTool::getInstance()
{
    if (!instance) {
        instance = new GoogleCalendarTool();
    }
    return instance;
}

ErrorCode GoogleCalendarTool::getCalendars(QString access_token, QList<Calendar> &listCalendar)
{
    Q_UNUSED(listCalendar);
    ErrorCode ret = Success;
    QString content;
    QJsonParseError error;
    QJsonDocument jDoc;
    QJsonObject rootObj, itemObj;
    QJsonArray itemsObj;

    QString requestStr = QString(GOOGLE_CALENDAR_URI) + "/users/me/calendarList" + "?access_token=" + access_token;
    QNetworkRequest request;
    request.setUrl(requestStr);
//    request.setRawHeader(QString("Authorization").toLatin1(), (QString("Bearer") + access_token).toLatin1());
    QNetworkReply* replyMsg = m_networkAccessManager.get(request);

    QEventLoop eventLoop;
    QTimer timer;
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    connect(replyMsg, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    timer.start(TIME_OUT_REQUEST);
    eventLoop.exec();

    if (!timer.isActive()) {
        timer.stop();
        ret = TimeOut;
        goto finished;
    }

    content = QString::fromUtf8(replyMsg->readAll());
    qDebug() << "content = " << content;

    jDoc = QJsonDocument::fromJson(content.toUtf8(), &error);
    if (jDoc.isNull() || jDoc.isEmpty()) {
        qCritical() << "Error: Parse message, " << error.errorString();
        ret = JsonIncorrectFormat;
        goto finished;
    }
    rootObj = jDoc.object();
    itemsObj = rootObj.value(ITEMS_TAG).toArray();
    for (int i = 0; i < itemsObj.count(); i++)
    {
        itemObj = itemsObj.at(i).toObject();
    }

finished:
    return ret;
}
