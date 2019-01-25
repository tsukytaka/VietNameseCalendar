import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1
import QtQuick.Controls.Material 2.0
import VCalendar 1.0

Calendar {
    id: calendar
    width: parent.width
    height: parent.height
    frameVisible: true
    focus: true
    style: calstyle
    navigationBarVisible: false

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

    }

    Component {
        id: calstyle

        CalendarStyle {
            background: Rectangle {
                color: Material.background
            }

            dayDelegate: Item {
                id: thisItem
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 1
                    border.width: 2
                    color: Material.background

                    Rectangle {
                        id: selectedAreaDate
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        width: 32
                        height: 32
                        radius: width*0.5
                        color: styleData.today ? Material.primary : parent.color

                        Text {
                            id: dayDelegateText
                            text: styleData.date.getDate()
                            anchors.centerIn: parent
                            font.pixelSize: 18
                            color: {
                                return styleData.visibleMonth ? Material.foreground : Material.color(Material.foreground, Material.Shade100)
                            }
                        }
                    }

                    ListView {
                        id: listEvent

                    }

                    Text {
                        id: lunarDayDelegateText
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
                        color: {
                            return styleData.visibleMonth ? Material.foreground : Material.color(Material.foreground, Material.Shade100)
                        }
                    }
                }

            }

            navigationBar: Rectangle {
                id: navigation
                height: 64
                color: Material.background
                Text {
                    id: monthDelegateText
                    text: styleData.title
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
            }

        }
    }

}




