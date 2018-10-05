import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.1
import QtGraphicalEffects 1.0
import VCalendar 1.0


ApplicationWindow {
    visible: true
    width: 1024
    height: 480
    title: qsTr("Calendar")

    Material.theme: Material.Dark

    Component {
        id: calstyle
        CalendarStyle {
            dayDelegate: Item {
                id: thisItem
                readonly property color sameMonthDateTextColor: "#444"
                readonly property color selectedDateColor: "#403778d0"
                readonly property color selectedDateTextColor: "white"
                readonly property color differentMonthDateTextColor: "#bbb"
                readonly property color invalidDatecolor: "#dddddd"

//                Rectangle {
//                    anchors.fill: parent
//                    border.color: "transparent"
//                    color: styleData.date !== undefined && styleData.selected ? selectedDateColor : "transparent"
//                    anchors.margins: styleData.selected ? -1 : 0
//                }


                Text {
                    id: dayDelegateText
                    text: styleData.date.getDate()
                    anchors {
                        top: parent.top
                        bottom: parent.bottom
                        left: parent.left
                        margins: 4
                    }
                    width: parent.width / 3
                    font.bold: true
                    color: {
                        var color = invalidDatecolor;
                        if (styleData.valid) {
                            // Date is within the valid range.
                            color = styleData.visibleMonth ? sameMonthDateTextColor : differentMonthDateTextColor;
                            if (styleData.selected) {
                                color = selectedDateTextColor;
                            }
                        }
                        color;
                    }
                }

//                Grid  {
//                    id: thisGrid
//                    anchors {
//                        top: parent.top
//                        bottom: parent.bottom
//                        left: dayDelegateText.right
//                        right: parent.right
//                    }

//                    anchors.margins: 4
//                    columns: 2
//                    rows: 4
//                    spacing: 4
//                    readonly property real itemWidth: (thisGrid.width - (thisGrid.spacing*thisGrid.columns))/thisGrid.columns
//                    readonly property real itemHeight: (thisGrid.height - (thisGrid.spacing*thisGrid.rows))/thisGrid.rows

//                    function redrawCalendarFlags() {
//                        var evtList = calendarManager.eventsForDate(styleData.date)
//                        thisListModel.clear()
//                        for (var ci = 0; ci < calendarManager.listOfCalendars.length; ci++) {
//                            for (var ei = 0; ei < evtList.length; ei++) {
//                                if ( (false === evtList[ei].isCanceled) && (calendarManager.getListItemAt(ci).displayName == evtList[ei].calendarName ) ) {
//                                    thisListModel.append({"calendarName":calendarManager.getListItemAt(ci).displayName, "calendarColor":calendarManager.getListItemAt(ci).color})
//                                    break;
//                                }
//                            }
//                        }
//                    }

//                    Connections {
//                        target: calendarManager
//                        onEventsUpdated: {
//                            thisGrid.redrawCalendarFlags()
//                        }
//                        onListOfCalendarsChanged: {
//                            thisGrid.redrawCalendarFlags()
//                        }
//                    }

//                    ListModel {
//                        id: thisListModel
//                    }

//                    Repeater {
//                        id: rep_DayCalendars
//                        delegate: Item {
//                            width: thisGrid.itemWidth
//                            height: thisGrid.itemHeight
//                            Image {
//                                id: thisImage
//                                anchors.fill: parent
//                                visible: false
//                                source: "qrc:///resources/images/icon_flag.svg"
//                            }
//                            ColorOverlay {
//                                anchors.fill: parent
//                                source: thisImage
//                                color: calendarColor
//                            }
//                        }
//                        model: thisListModel
//                    }
//                }
            }
        }
    }

    Calendar {
        id: calendar
        anchors.fill: parent
        anchors.margins: 20
        frameVisible: true
        weekNumbersVisible: true
        selectedDate: new Date()
        focus: true
        style: calstyle
        onVisibleMonthChanged: {
            calendarManager.date = new Date(calendar.visibleYear, calendar.visibleMonth, 1)
        }
        onVisibleYearChanged: {
            calendarManager.date = new Date(calendar.visibleYear, calendar.visibleMonth, 1)
        }
    }
}
