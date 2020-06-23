import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1
import QtQuick.Controls.Material 2.0
import VCalendar 1.0

Calendar {
    id: calendar
    anchors.fill: parent
//    frameVisible: true
    focus: true
    style: calstyle
    navigationBarVisible: true

    MonthViewVM {
        id: monthViewVM
    }

    onVisibleMonthChanged: {
//            calendarManager.date = new Date(calendar.visibleYear, calendar.visibleMonth, 1)
    }
    onVisibleYearChanged: {
//            calendarManager.date = new Date(calendar.visibleYear, calendar.visibleMonth, 1)
    }

    onClicked: {
        console.log("test click")
    }

    onPressed: {
        console.log("test press")
    }

    Component.onCompleted: {
        console.log("Material.primary = " + Material.primary)
        console.log("Material.background = " + Material.background)
    }

    Component {
        id: calstyle

        CalendarStyle {
            background: Rectangle {
                color: Material.background
            }

            navigationBar: Rectangle {
                id: navigation
                height: 32
                color: Material.background
                Text {
                    color: Material.foreground
                    text: styleData.title
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
            }

            dayOfWeekDelegate: Rectangle {
                color: Material.background
                height: 48
                Label {
                    text: control.locale.dayName(styleData.dayOfWeek, control.dayOfWeekFormat)
                    anchors.centerIn: parent
                    font.pixelSize: 18
                    color: Material.foreground
                }
            }

            dayDelegate: Item {
                Rectangle {
                    anchors.fill: parent
                    color: Material.background

                    Rectangle {
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        width: styleData.visibleMonth ? 24 : 16
                        height: styleData.visibleMonth ? 24 : 16
                        radius: width*0.5
                        color: styleData.visibleMonth ? Material.primary : Material.background

                        Text {
                            id: dayDelegateText
                            text: styleData.date.getDate()
                            anchors.centerIn: parent
                            font.pixelSize: styleData.visibleMonth ? 18 : 12
                            color: {
                                return  Material.foreground
                            }
                        }
                    }

                    ListView {

                    }

                    Text {
                        text: {
                            var dateStr = "";
                            var lunarDate = LunarTools.convertSolar2Lunar(styleData.date, 7)

                            if (lunarDate.day === 1) {
                                dateStr = lunarDate.day + "/" + lunarDate.month
                            }
                            dateStr = lunarDate.day
                            return dateStr
                        }
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 5
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        font.pixelSize: 12
                        color: Material.foreground
                    }
                }

            }



        }
    }
}




