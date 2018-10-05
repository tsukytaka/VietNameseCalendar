/*********************************************//*!@addtogroup file Files*//*@{*/
/*!
 *******************************************************************************
* File identification:      $Id: CalendarClient.cpp 18 2017-01-26 17:33:06Z cypax $
* Revision of last commit:  $Rev: 18 $
* Author of last commit:    $Author: cypax $
* Date of last commit:      $Date: 2017-01-26 18:33:06 +0100 (Do, 26 Jan 2017) $
 *******************************************************************************
 *
 * @author        Cypax (cypax.net)
 *
 * @brief         Implementation file of class CalendarClient.
 */
/************************************************************************//*@}*/

/******************************************************************************/
/* Library includes                                                           */
/******************************************************************************/
#include <QDebug>
#include <QColor>

/******************************************************************************/
/* Own includes                                                               */
/******************************************************************************/
#include "CalendarClient.h"
#include "CalendarEvent.h"
#include "DateUtils.h"

/******************************************************************************/
/* Namespace                                                                 */
/******************************************************************************/

/******************************************************************************/
/* Constants (#define)                                                        */
/***************************************//*!@addtogroup define Constants*//*@{*/

#define DEBUG_CALENDARCLIENT 0
#if DEBUG_CALENDARCLIENT
#define QDEBUG qDebug()
#else
#define QDEBUG if (0) qDebug()
#endif

/***** End of: define Constants *****************************************//*@}*/

/******************************************************************************/
/* Constructors                                                               */
/**********************************//*!@addtogroup constrc Constructors *//*@{*/

CalendarClient::CalendarClient(QObject* parent) : QObject(parent)
{
  m_pReply = NULL;
  m_DataStream = NULL;
  m_HostURL = "";
  m_DisplayName = "";

  m_RequestTimeoutMS = 2000;
  m_RequestTimeoutTimer.setSingleShot(true);

  // timer is set to single shot so we don't need to abort it, in case the synchronization has failed
  m_SynchronizationTimer.setSingleShot(true);
  m_SynchronizationTimer.setInterval(60000);

  // create random color
  m_Color = QColor(qrand() & 0xFF, qrand() & 0xFF, qrand() & 0xFF).name();

}

/***** End of: constrc Constructors *************************************//*@}*/

/******************************************************************************/
/* Deconstructor                                                              */
/******************************//*!@addtogroup deconstrc Deconstructors *//*@{*/

CalendarClient::~CalendarClient()
{
  m_EventList.clear();
  m_SynchronizationTimer.stop();
}

/***** End of: deconstrc Constructors ***********************************//*@}*/

/******************************************************************************/
/* Public functions                                                           */
/*****************************//*!@addtogroup pubfunct Public functions *//*@{*/

QList<QObject*> CalendarClient::eventsForDate(const QDate& date)
{
  QList<QObject*> events;

  QDateTime startOfQuestionedDate(date);
  QDateTime endOfQuestionedDate(date, QTime(23,59,59));

  foreach(CalendarEvent evt, m_EventList)
  {

    // skip if event starts in future
    if (evt.getStartDateTime() > endOfQuestionedDate)
    {
      continue;
    }

    if (evt.getRRULE() == "")
    {
      // is a single event

      // skip if event has ended
      if (evt.getEndDateTime() < startOfQuestionedDate)
      {
        continue;
      }

      events.append(handleSingleEvent(evt, startOfQuestionedDate, endOfQuestionedDate));
    }
    else
    {
      // is a repeated event

      // retrieve an array of rules
      QStringList rruleList = evt.getRRULE().trimmed().split(";", QString::SkipEmptyParts);

      QString strFREQ = "";
      QString strINTERVAL = "";
      QString strCOUNT = "";
      QString strUNTIL = "";
      QString strWKST = "";
      QString strBYDAY = "";
      QString strBYMONTHDAY = "";
      QString strBYMONTH = "";
      QString strBYYEAR = "";
      QString strBYWEEKNO = "";
      QString strBYSETPOS = "";

      // divide into rule name and rule parameter(s)
      foreach(QString ruleString, rruleList)
      {
        QStringList rruleElements = ruleString.trimmed().split("=", QString::SkipEmptyParts);
        // result must have 2 elements
        if (rruleElements.length() != 2)
        {
          QDEBUG << m_DisplayName << ": " << "ERROR: invalid rule element count" << rruleElements.length() << "in rule" << ruleString;
          continue;
        }
        if (rruleElements.at(0).toUpper() == "FREQ")
        {
          strFREQ = rruleElements.at(1);
        }
        else if (rruleElements.at(0).toUpper() == "INTERVAL")
        {
          strINTERVAL = rruleElements.at(1);
        }
        else if (rruleElements.at(0).toUpper() == "COUNT")
        {
          strCOUNT = rruleElements.at(1);
        }
        else if (rruleElements.at(0).toUpper() == "UNTIL")
        {
          strUNTIL = rruleElements.at(1);
        }
        else if (rruleElements.at(0).toUpper() == "WKST")
        {
          strWKST = rruleElements.at(1);
        }
        else if (rruleElements.at(0).toUpper() == "BYDAY")
        {
          strBYDAY = rruleElements.at(1);
        }
        else if (rruleElements.at(0).toUpper() == "BYMONTHDAY")
        {
          strBYMONTHDAY = rruleElements.at(1);
        }
        else if (rruleElements.at(0).toUpper() == "BYMONTH")
        {
          strBYMONTH = rruleElements.at(1);
        }
        else if (rruleElements.at(0).toUpper() == "BYYEAR")
        {
          strBYYEAR = rruleElements.at(1);
        }
        else if (rruleElements.at(0).toUpper() == "BYWEEKNO")
        {
          strBYWEEKNO = rruleElements.at(1);
        }
        else if (rruleElements.at(0).toUpper() == "BYSETPOS")
        {
          strBYSETPOS = rruleElements.at(1);
        }
        else
        {
          QDEBUG << m_DisplayName << ": " << "WARNING: unsupported rrule element" << rruleElements.at(0);
        }
      }


      // frequency must be set, all other rules are optional
      if (strFREQ.isEmpty())
      {
        QDEBUG << m_DisplayName << ": " << "ERROR: FREQ rule not set in RRULE" << evt.getRRULE();
        continue;
      }

      // retrieve INTERVAL as integer if set
      int iInterval = 1;
      if (!strINTERVAL.isEmpty())
      {
        bool convResult = false;
        int convValue = strINTERVAL.toInt(&convResult, 10);
        if (convResult)
        {
          iInterval = convValue;
        }
        else
        {
          QDEBUG << m_DisplayName << ": " << "ERROR: invalid INTERVAL value in" << evt.getRRULE();
          continue;
        }
      }

      // retrieve COUNT as integer if available
      int iCount = -1;
      if (!strCOUNT.isEmpty())
      {
        bool convResult = false;
        int convValue = strCOUNT.toInt(&convResult, 10);
        if (convResult)
        {
          iCount = convValue;
        }
        else
        {
          QDEBUG << m_DisplayName << ": " << "ERROR: invalid COUNT value in" << evt.getRRULE();
          continue;
        }
      }

      // retrieve UNTIL as QDateTime if available
      QDateTime dtUntil = QDateTime(); // creates an invalid QDateTime
      if (!strUNTIL.isEmpty())
      {
        dtUntil = QDateTime::fromString(strUNTIL, Qt::ISODate);
        if (!dtUntil.isValid())
        {
          dtUntil = QDateTime::fromString(strUNTIL, "yyyyMMddTHHmmssZ");
        }
        if (!dtUntil.isValid())
        {
          dtUntil = QDateTime::fromString(strUNTIL, "yyyyMMddTHHmmss");
        }
        if (!dtUntil.isValid())
        {
          dtUntil = QDateTime::fromString(strUNTIL, "yyyyMMddHHmmss");
        }
        if (!dtUntil.isValid())
        {
          QDEBUG << m_DisplayName << ": " << "ERROR: could not interpret UNTIL date in" << evt.getRRULE();
          continue;
        }
      }

      QDateTime testDateTime = evt.getStartDateTime();

      if (strFREQ == "WEEKLY")
      {
        //QDEBUG << m_DisplayName << ": " << evt.name() << " repeats weekly" << evt.getRRULE();

        if (strBYDAY.isEmpty())
        {
          // repeats every nth week since start date

          int occurrences = 0;
          while (testDateTime <= endOfQuestionedDate)
          {

            // check if event is not excluded by EXDATEs
            bool bOccurrenceIsCanceled = isDateExcluded(evt.getExdates(), testDateTime.date());
            if (!bOccurrenceIsCanceled)
            {
              occurrences++;
            }

            // check if date matches questioned date range
            if ( (testDateTime >= startOfQuestionedDate) && (testDateTime <= endOfQuestionedDate) )
            {
              //QDEBUG << m_DisplayName << ": " << "found match on" << testDateTime.toString("yyyy-MM-dd HH:mm:ss");

              CalendarEvent* event = new CalendarEvent(this);
              event->copyFrom(evt);
              event->setIsCanceled(bOccurrenceIsCanceled);
              //event->setStartDateTime(testDateTime);

              //QDEBUG << m_DisplayName << ": " << "appended" << event->name();
              events.append(event);
            }

            // abort if COUNT rule applies
            if (!strCOUNT.isEmpty())
            {
              if (occurrences >= iCount)
              {
                QDEBUG << m_DisplayName << ": " << "weekly, count reached" << occurrences;
                break;
              }
            }

            // abort if UNTIL rule applies
            if (!strUNTIL.isEmpty())
            {
              if (testDateTime > dtUntil)
              {
                QDEBUG << m_DisplayName << ": " << "weekly, until reached";
                break;
              }
            }

            testDateTime = testDateTime.addDays(7 * iInterval);
          }
        }
        else
        {
          // repeats every nth week since start date at given weekdays

          // get a list of weekdays
          QStringList listOfWeekdays = strBYDAY.toUpper().trimmed().split(",", QString::SkipEmptyParts);

          foreach (QString weekday, listOfWeekdays)
          {
            testDateTime = evt.getStartDateTime();

            int iWeekday = DateUtils::getWeekdayIndexFromString(weekday);

            if (0 == iWeekday)
            {
              QDEBUG << m_DisplayName << ": " << "ERROR: BYDAY" << weekday << "in rrule" << evt.getRRULE() << "is invalid";
              continue;
            }

            // if the testDate doesn't start on the questioned weekday, jump forward to the next weekday occurrence
            if (testDateTime.date().dayOfWeek() != iWeekday)
            {
              int weekdayDiff = iWeekday - testDateTime.date().dayOfWeek();
              if (weekdayDiff < 0) { weekdayDiff+= 7; }
              testDateTime = testDateTime.addDays(weekdayDiff);
            }

            int occurrences = 0;


            while (testDateTime <= endOfQuestionedDate)
            {

              // check if event is not excluded by EXDATEs
              bool bOccurrenceIsCanceled = isDateExcluded(evt.getExdates(), testDateTime.date());
              if (!bOccurrenceIsCanceled)
              {
                occurrences++;
              }

              // check if date matches questioned date range
              if ( (testDateTime >= startOfQuestionedDate) && (testDateTime <= endOfQuestionedDate) )
              {
                //QDEBUG << m_DisplayName << ": " << "found match on" << testDateTime.toString("yyyy-MM-dd HH:mm:ss") << weekday;

                CalendarEvent* event = new CalendarEvent(this);
                event->copyFrom(evt);
                //event->setStartDateTime(testDateTime);
                event->setIsCanceled(bOccurrenceIsCanceled);

                //QDEBUG << m_DisplayName << ": " << "appended" << event->name();
                events.append(event);
              }

              // abort if COUNT rule applies
              if (!strCOUNT.isEmpty())
              {
                if (occurrences >= iCount)
                {
                  QDEBUG << m_DisplayName << ": " << "monthly, count reached" << occurrences;
                  break;
                }
              }

              // abort if UNTIL rule applies
              if (!strUNTIL.isEmpty())
              {
                if (testDateTime > dtUntil)
                {
                  QDEBUG << m_DisplayName << ": " << "monthly, until reached";
                  break;
                }
              }

              testDateTime = testDateTime.addDays(7 * iInterval);
            }

          }

        }
      }
      else if (strFREQ == "MONTHLY")
      {


        if (strBYDAY.isEmpty())
        {
          // repeats every nth month since start date

          int occurrences = 0;
          while (testDateTime <= endOfQuestionedDate)
          {

            // check if event is not excluded by EXDATEs
            bool bOccurrenceIsCanceled = isDateExcluded(evt.getExdates(), testDateTime.date());
            if (!bOccurrenceIsCanceled)
            {
              occurrences++;
            }

            // check if date matches questioned date range
            if ( (testDateTime >= startOfQuestionedDate) && (testDateTime <= endOfQuestionedDate) )
            {
              //QDEBUG << m_DisplayName << ": " << "found match on" << testDateTime.toString("yyyy-MM-dd HH:mm:ss");

              CalendarEvent* event = new CalendarEvent(this);
              event->copyFrom(evt);
              //event->setStartDateTime(testDateTime);
              event->setIsCanceled(bOccurrenceIsCanceled);

              QDEBUG << m_DisplayName << ": " << "appended" << event->name();
              events.append(event);
            }

            // abort if COUNT rule applies
            if (!strCOUNT.isEmpty())
            {
              if (occurrences >= iCount)
              {
                //QDEBUG << m_DisplayName << ": " << "monthly, count reached" << occurrences;
                break;
              }
            }

            // abort if UNTIL rule applies
            if (!strUNTIL.isEmpty())
            {
              if (testDateTime > dtUntil)
              {
                QDEBUG << m_DisplayName << ": " << "monthly, until reached";
                break;
              }
            }

            testDateTime = testDateTime.addDays(7 * iInterval);
          }

        }
        else // when strBYDAY is not empty
        {


          // repeats every nth month since start date at given weekdays

          // get a list of weekdays
          QStringList listOfWeekdays = strBYDAY.toUpper().trimmed().split(",", QString::SkipEmptyParts);

          foreach (QString weekday, listOfWeekdays)
          {
            testDateTime = evt.getStartDateTime();

            int iWeekday = DateUtils::getWeekdayIndexFromString(weekday);
            if (0 == iWeekday)
            {
              QDEBUG << m_DisplayName << ": " << "ERROR: unsupported weekday" << weekday << "in RRULE" << evt.getRRULE();
              break;
            }

            int iWeekdaySelector = DateUtils::getWeekdaySelectorFromString(weekday);
            if (DATEUTILS_INVALID_DAY == iWeekdaySelector)
            {
              QDEBUG << m_DisplayName << ": " << "ERROR: unsupported weekday selector" << weekday << "in RRULE" << evt.getRRULE();
              break;
            }

            if (0 == iWeekdaySelector)
            {
              // weekday selector is not set -> every occurrence of the questioned weekday in an month applies

              // if the event doesn't start on the questioned weekday, jump forward to the next weekday occurrence
              if (testDateTime.date().dayOfWeek() != iWeekday)
              {
                int weekdayDiff = iWeekday - testDateTime.date().dayOfWeek();
                if (weekdayDiff < 0) { weekdayDiff+= 7; }
                testDateTime = testDateTime.addDays(weekdayDiff);
              }

              int occurrences = 0;


              /* Programming scheme:
               * while (testDate <= endOfQuestionedDate)
               * 1. occurrences += 1
               * 2. if (testDateTime in questioned period), then append the event to the event list
               * 3. add one week to testDateTime
               * 4. if 3. causes to leave the current month, then
               *   4.1 seek back to the 1st day of the current month
               *   4.2 add iInterval times months
               *   4.3 if this date is not the strBYDAY-weekday, then seek forward to the first strBYDAY-weekday
               * 5. continue with 1.
              */

              while (testDateTime <= endOfQuestionedDate)
              {

                // check if event is not excluded by EXDATEs
                bool bOccurrenceIsCanceled = isDateExcluded(evt.getExdates(), testDateTime.date());
                if (!bOccurrenceIsCanceled)
                {
                  // 1:
                  occurrences++;
                }

                // 2: if (testDateTime in questioned period), then append the event to the event list
                if ( (testDateTime >= startOfQuestionedDate) && (testDateTime <= endOfQuestionedDate) )
                {
                  //QDEBUG << m_DisplayName << ": " << "found match on" << testDateTime.toString("yyyy-MM-dd HH:mm:ss") << weekday;

                  CalendarEvent* event = new CalendarEvent(this);
                  event->copyFrom(evt);
                  //event->setStartDateTime(testDateTime);
                  event->setIsCanceled(bOccurrenceIsCanceled);

                  //QDEBUG << m_DisplayName << ": " << "appended" << event->name();
                  events.append(event);
                }

                // abort if COUNT rule applies
                if (!strCOUNT.isEmpty())
                {
                  if (occurrences >= iCount)
                  {
                    QDEBUG << m_DisplayName << ": " << "monthly, count reached" << occurrences;
                    break;
                  }
                }

                // abort if UNTIL rule applies
                if (!strUNTIL.isEmpty())
                {
                  if (testDateTime > dtUntil)
                  {
                    QDEBUG << m_DisplayName << ": " << "monthly, until reached";
                    break;
                  }
                }


                int thisMonth = testDateTime.date().month();
                int thisYear = testDateTime.date().year();

                // 3: add one week to testDateTime
                testDateTime.setDate(testDateTime.date().addDays(7));

                // 4: if 3. causes to leave the current month, then
                if (thisMonth != testDateTime.date().month())
                {
                  // 4.1: seek back to the 1st day of the current month
                  testDateTime.setDate(QDate(thisYear, thisMonth, 1));

                  // 4.2: add iInterval times months
                  testDateTime = testDateTime.addMonths(iInterval);

                  // 4.3: if this date is not the strBYDAY-weekday, then seek forward to the first strBYDAY-weekday
                  if (testDateTime.date().dayOfWeek() != iWeekday)
                  {
                    int weekdayDiff = iWeekday - testDateTime.date().dayOfWeek();
                    if (weekdayDiff < 0) { weekdayDiff+= 7; }
                    testDateTime = testDateTime.addDays(weekdayDiff);
                  }

                }

              } // END: while (testDateTime <= endOfQuestionedDate)

            }
            else
            {
              // weekday selector is set -> only specific weekdays in a month do apply

              int occurrences = 0;

              while (testDateTime <= endOfQuestionedDate)
              {
                QDate weekDayDate = DateUtils::getWeekdayOfMonth(iWeekday, iWeekdaySelector, testDateTime.date());
                if (weekDayDate.isValid())
                {
                  // check if event is not excluded by EXDATEs
                  bool bOccurrenceIsCanceled = isDateExcluded(evt.getExdates(), testDateTime.date());
                  if (!bOccurrenceIsCanceled)
                  {
                    occurrences++;
                  }

                  testDateTime.setDate(weekDayDate);

                  // check if date matches questioned date range
                  if ( (testDateTime >= startOfQuestionedDate) && (testDateTime <= endOfQuestionedDate) )
                  {
                    //QDEBUG << m_DisplayName << ": " << "found match" << occurrences << "on" << testDateTime.toString("yyyy-MM-dd HH:mm:ss") << weekday;

                    CalendarEvent* event = new CalendarEvent(this);
                    event->copyFrom(evt);
                    //event->setStartDateTime(testDateTime);
                    event->setIsCanceled(bOccurrenceIsCanceled);

                    //QDEBUG << m_DisplayName << ": " << "appended" << event->name();
                    events.append(event);
                  }

                }
                // abort if testDateTime exceeds end of questioned date
                else if (testDateTime > endOfQuestionedDate)
                {
                  //QDEBUG << m_DisplayName << ": " << "end of questioned range reached" << testDateTime.toString("yyyy-MM-dd HH:mm:ss");
                  break;
                }

                // abort if COUNT rule applies
                if (!strCOUNT.isEmpty())
                {
                  if (occurrences >= iCount)
                  {
                    //QDEBUG << m_DisplayName << ": " << "monthly, count reached" << occurrences;
                    break;
                  }
                }

                // abort if UNTIL rule applies
                if (!strUNTIL.isEmpty())
                {
                  if (testDateTime > dtUntil)
                  {
                    QDEBUG << m_DisplayName << ": " << "monthly, until reached" << testDateTime.toString("yyyy-MM-dd HH:mm:ss");
                    break;
                  }
                }

                testDateTime = testDateTime.addMonths(iInterval);
                testDateTime.setDate(QDate(testDateTime.date().year(), testDateTime.date().month(), 1));
                // if the event doesn't start on the questioned weekday, jump forward to the next weekday occurrence
                if (testDateTime.date().dayOfWeek() != iWeekday)
                {
                  int weekdayDiff = iWeekday - testDateTime.date().dayOfWeek();
                  if (weekdayDiff < 0) { weekdayDiff+= 7; }
                  testDateTime = testDateTime.addDays(weekdayDiff);
                }

              }

            }


          } // END: foreach weekday


        }

      }
      else if (strFREQ == "YEARLY")
      {
        int occurrences = 1; // start date counts as first occurrence

        while (testDateTime <= endOfQuestionedDate)
        {
          // check if event is not excluded by EXDATEs
          bool bOccurrenceIsCanceled = isDateExcluded(evt.getExdates(), testDateTime.date());
          if (!bOccurrenceIsCanceled)
          {
            occurrences++;
          }

          // check if date matches questioned date range
          if ( (testDateTime >= startOfQuestionedDate) && (testDateTime <= endOfQuestionedDate) )
          {
            //QDEBUG << m_DisplayName << ": " << "found yearly match" << occurrences << "on" << testDateTime.toString("yyyy-MM-dd HH:mm:ss");

            CalendarEvent* event = new CalendarEvent(this);
            event->copyFrom(evt);
            //event->setStartDateTime(testDateTime);
            event->setIsCanceled(bOccurrenceIsCanceled);

            //QDEBUG << m_DisplayName << ": " << "appended" << event->name();
            events.append(event);
          }

          testDateTime = testDateTime.addYears(iInterval);

          // abort if testDateTime exceeds end of questioned date
          if (testDateTime > endOfQuestionedDate)
          {
            //QDEBUG << m_DisplayName << ": " << "end of questioned range reached" << testDateTime.toString("yyyy-MM-dd HH:mm:ss");
            break;
          }

          // abort if COUNT rule applies
          if (!strCOUNT.isEmpty())
          {
            if (occurrences >= iCount)
            {
              //QDEBUG << m_DisplayName << ": " << "yearly, count reached" << occurrences;
              break;
            }
          }

          // abort if UNTIL rule applies
          if (!strUNTIL.isEmpty())
          {
            if (testDateTime > dtUntil)
            {
              //QDEBUG << m_DisplayName << ": " << "yearly, until reached" << testDateTime.toString("yyyy-MM-dd HH:mm:ss");
              break;
            }
          }


        }

        continue;
      }
      else {
        QDEBUG << m_DisplayName << ": " << "WARNING: unsupported event frequency" << strFREQ;
      }



    } // END: else (is repeated event)

  }

  return events;
}

QList<QObject*> CalendarClient::allEvents(void)
{
  QList<QObject*> events;

  foreach(CalendarEvent evt, m_EventList)
  {
    CalendarEvent* event = new CalendarEvent(this);
    event->copyFrom(evt);
    events.append(event);
  }

  return events;
}



int CalendarClient::getRequestTimeoutMS(void) const
{
  return m_RequestTimeoutMS;
}

void CalendarClient::setRequestTimeoutMS(const int requestTimeoutMS)
{
  if (requestTimeoutMS > 0)
  {
    m_RequestTimeoutMS = requestTimeoutMS;
    emit requestTimeoutMSChanged(m_RequestTimeoutMS);
  }
}


/***** End of: pubfunct Public functions ********************************//*@}*/

/******************************************************************************/
/* Protected functions                                                        */
/*************************//*!@addtogroup protfunct Protected functions *//*@{*/

QList<QObject*> CalendarClient::handleSingleEvent(CalendarEvent& evt, const QDateTime& startOfQuestionedDate, const QDateTime& endOfQuestionedDate)
{
  QList<QObject*> events;

  // events must not end at 00:00:00
  if (0 == evt.getEndDateTime().time().msecsSinceStartOfDay())
  {
    // removing one second from endDateTime
    QDateTime newEndDateTime = evt.getEndDateTime().addSecs(-1);
    evt.setEndDateTime(newEndDateTime);
  }

  // check if event occurs in questioned range
  if (    ( (evt.getStartDateTime() >= startOfQuestionedDate) && (evt.getStartDateTime() <= endOfQuestionedDate) ) // event starts in questioned range
       || ( (evt.getEndDateTime()   >= startOfQuestionedDate) && (evt.getEndDateTime()   <= endOfQuestionedDate) ) // event ends in questioned range
       || ( (evt.getStartDateTime() <= startOfQuestionedDate) && (evt.getEndDateTime()   >= endOfQuestionedDate) ) // event overlaps questioned range
     )
  {
    CalendarEvent* event = new CalendarEvent(this);
    event->copyFrom(evt);

    //QDEBUG << m_DisplayName << ": " << "appended" << event->name();
    events.append(event);
  }

  return events;
}


QString CalendarClient::encodeBase64(QString string)
{
  QByteArray ba;
  ba.append(string);
  return ba.toBase64();
}

QString CalendarClient::ascii2utf8(QString str)
{
 return QString::fromUtf8(str.toLocal8Bit().data());
}

void CalendarClient::parseCALENDAR(QString href)
{
  QString line = m_DataStream->readLine();

  while(false == line.isNull())
  {
    if(false != line.contains("BEGIN:VEVENT"))
    {
        parseVEVENT(href);
    }
    line = m_DataStream->readLine();
  }
}

void CalendarClient::parseVEVENT(QString href)
{
  CalendarEvent event(this);
  event.setColor(m_Color);
  event.setCalendarName(m_DisplayName);
  event.setCalendarPointer(this);
  event.setHREF(href);
  QString line;
  QDateTime utcTime;
  while (!(line = m_DataStream->readLine()).contains(QByteArray("END:VEVENT")))
  {
    //QDEBUG << m_DisplayName << ": " << line;

    const int deliminatorPosition = line.indexOf(QLatin1Char(':'));
    const QString key   = line.mid(0, deliminatorPosition);
    QString value = (line.mid(deliminatorPosition + 1, -1).replace("\\n", "\n")); //.toLatin1();
    QString testEncodingString = ascii2utf8(value);
    if (false == testEncodingString.contains("�"))
    {
      value = testEncodingString;
    }

    if (key.startsWith(QLatin1String("DTSTART")))
    {
      utcTime = QDateTime::fromString(value, "yyyyMMdd'T'hhmmss'Z'");
      if (!utcTime.isValid())
        utcTime = QDateTime::fromString(value, "yyyyMMdd'T'hhmmss");
      if (!utcTime.isValid())
        utcTime = QDateTime::fromString(value, "yyyyMMddhhmmss");
      if (!utcTime.isValid())
        utcTime = QDateTime::fromString(value, "yyyyMMdd");
      if (!utcTime.isValid())
        QDEBUG << m_DisplayName << ": " << "could not parse" << line;

      event.setStartDateTime(utcTime.toLocalTime());
    }
    else if (key.startsWith(QLatin1String("DTEND")))
    {
      utcTime = QDateTime::fromString(value, "yyyyMMdd'T'hhmmss'Z'");
      if (!utcTime.isValid())
        utcTime = QDateTime::fromString(value, "yyyyMMdd'T'hhmmss");
      if (!utcTime.isValid())
        utcTime = QDateTime::fromString(value, "yyyyMMddhhmmss");
      if (!utcTime.isValid())
        utcTime = QDateTime::fromString(value, "yyyyMMdd");
      if (!utcTime.isValid())
        QDEBUG << m_DisplayName << ": " << "could not parse" << line;

      event.setEndDateTime(utcTime.toLocalTime());
    }
    else if (key == QLatin1String("RRULE"))
    {
      event.setRRULE(value);
    }
    else if (key == QLatin1String("EXDATE"))
    {
      event.setExdates(value);
    }
    else if (key == QLatin1String("SUMMARY"))
    {
      event.setName(value);
    }
    else if (key == QLatin1String("LOCATION"))
    {
      event.setLocation(value);
    }
    else if (key == QLatin1String("UID"))
    {
      event.setUID(value);
    }
    else if (key == QLatin1String("CATEGORIES"))
    {
      event.setCategories(value);
    }
    else if (key == QLatin1String("DESCRIPTION"))
    {
      event.setDescription(value);
    }
  }
  if (event.name() != "")
  {
    m_EventList.append(event);
  }
}


bool CalendarClient::isDateExcluded(const QString strExdates, const QDate& questionedDate) const
{
  QStringList strlstExdates = strExdates.split(",", QString::SkipEmptyParts);
  bool bRet = false;

  if (strlstExdates.isEmpty())
  {
    return false;
  }

  foreach(const QString& strExdate, strlstExdates)
  {
    QDateTime excludeDate;
    excludeDate = QDateTime::fromString(strExdate, "yyyyMMdd'T'hhmmss'Z'");
    if (!excludeDate.isValid())
      excludeDate = QDateTime::fromString(strExdate, "yyyyMMdd'T'hhmmss");
    if (!excludeDate.isValid())
      excludeDate = QDateTime::fromString(strExdate, "yyyyMMddhhmmss");
    if (!excludeDate.isValid())
      excludeDate = QDateTime::fromString(strExdate, "yyyyMMdd");
    if (!excludeDate.isValid())
    {
      QDEBUG << m_DisplayName << ": " << "could not parse EXDATE" << strExdate;
    }
    else
    {
      excludeDate.setDate(excludeDate.toLocalTime().date());
      if (excludeDate.date() == questionedDate)
      {
        // event occurence is excluded
        //QDEBUG << m_DisplayName << ": " << "event is excluded by EXDATE" << strExdate;
        bRet = true;
        break;
      }
    }
  }

  return bRet;
}


/***** End of: protfunct Protected functions ****************************//*@}*/

/******************************************************************************/
/* Private functions                                                          */
/*************************//*!@addtogroup privfunct Private functions   *//*@{*/
/***** End of: privfunct Private functions ******************************//*@}*/

/******************************************************************************/
/* Public slots                                                               */
/*************************//*!@addtogroup pubslots Public slots         *//*@{*/

CalendarClient::E_CalendarState CalendarClient::getSyncState(void)
{
  return m_State;
}

QString CalendarClient::getColor(void) const
{
  return m_Color;
}

void CalendarClient::setColor(const QString& color)
{
  if (color != m_Color)
  {
    m_Color = color;
    for (int i = 0; i < m_EventList.count(); i++)
    {
      CalendarEvent* pEvent = &(m_EventList[i]);
      pEvent->setColor(m_Color);
    }
    emit colorChanged(m_Color);
  }
}


CalendarClient::E_CalendarType CalendarClient::getCalendarType(void)
{
  return m_CalendarType;
}

bool CalendarClient::setHostURL(const QUrl hostURL)
{
  bool bRet = false;

  if (false != hostURL.isValid())
  {
    m_HostURL = hostURL;
    bRet = true;
    emit hostURLChanged(m_HostURL.toString());
  }

  return bRet;
}

QString CalendarClient::getHostURL(void) const
{
  return m_HostURL.toString();
}


QString CalendarClient::getDisplayName(void) const
{
  return m_DisplayName;
}

void CalendarClient::setDisplayName(QString name)
{
  m_DisplayName = name;
  emit displayNameChanged(m_DisplayName);
}

/***** End of: pubslots Public slots ************************************//*@}*/

/******************************************************************************/
/* Protected slots                                                            */
/*********************//*!@addtogroup protslots Protected slots         *//*@{*/
/***** End of: protslots Protected slots ********************************//*@}*/

/******************************************************************************/
/* Private slots                                                              */
/*************************//*!@addtogroup privslots Private slots       *//*@{*/
/***** End of:privslots Private slots ***********************************//*@}*/

/**** Last line of source code                                             ****/
