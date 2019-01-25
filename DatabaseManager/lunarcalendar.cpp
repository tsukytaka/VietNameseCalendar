#include "lunarcalendar.h"
#include "lunarevent.h"

LunarCalendar::LunarCalendar()
{

}

ErrorCode LunarCalendar::importCSVFile(QString pathFile)
{
    Q_UNUSED(pathFile);
    ErrorCode ret = Success;
    //read csv file
    QFile file(pathFile);
    if (!file.open(QIODevice::ReadOnly)) {
        ret = FileInvalid;
        goto finished;
    }

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        //parsing line
        QList<QByteArray> strings = line.split(',');
        if (strings.count() != 3) {
            continue;
        }
        LunarEvent event;
        event.setTitle(strings.first());
        qDebug() << "event.getTitle() : " << event.getTitle();
        QList<QByteArray> dateStrsStart = strings[1].split('-');
        if (dateStrsStart.count() >= 3)
        {
            qint32 leap = 0;
            if (dateStrsStart[1].contains('+')) {
                leap ++;
                dateStrsStart[1].replace('+', ' ');
            }
            QLunarDate lunarDate(dateStrsStart[0].toInt(), dateStrsStart[1].toInt(), dateStrsStart[2].toInt(), leap);
            event.setStartLunarDate(lunarDate);

            if (dateStrsStart.count() == 5)
            {
                QLunarDate lunarDate(dateStrsStart[0].toInt(), dateStrsStart[1].toInt(), dateStrsStart[2].toInt());
                event.setStartLunarDate(lunarDate);
                QTime startTime(dateStrsStart[3].toInt(), dateStrsStart[4].toInt());
                event.setStartTime(startTime);
            }
            qDebug() << "lunarStartDate : " << lunarDate.year() << "-" << lunarDate.month() << "-" << lunarDate.day();
        }
        else
        {
            continue;
        }

        QList<QByteArray> dateStrsEnd = strings[2].split('-');
        if (dateStrsEnd.count() >= 3)
        {
            qint32 leap = 0;
            if (dateStrsEnd[1].contains('+')) {
                leap ++;
                dateStrsEnd[1].replace('+', ' ');
            }
            QLunarDate lunarDate(dateStrsEnd[0].toInt(), dateStrsEnd[1].toInt(), dateStrsEnd[2].toInt(), leap);
            event.setStartLunarDate(lunarDate);

            if (dateStrsEnd.count() == 5)
            {
                QLunarDate lunarDate(dateStrsEnd[0].toInt(), dateStrsEnd[1].toInt(), dateStrsEnd[2].toInt());
                event.setEndLunarDate(lunarDate);
                QTime endTime(dateStrsEnd[3].toInt(), dateStrsEnd[4].toInt());
                event.setEndTime(endTime);
            }
        }
        else
        {
            continue;
        }

        //Add list event to calendar
        event.setEventId(event.getTitle());
        addEvent(new Event(event));
    }

finished:
    return ret;
}

ErrorCode LunarCalendar::exportCSVFile(QString pathFile)
{
    Q_UNUSED(pathFile);
    ErrorCode ret = Success;


    return ret;
}
