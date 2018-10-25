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
    width: 640
    height: 1136
    title: qsTr("Calendar")

    Material.theme: Material.Dark

    Component {
        id: calstyle
        CalendarStyle {
            dayDelegate: Item {
                id: thisItem
                readonly property color selectedDateColor: "#80DEEA"
                readonly property color differentMonthDateTextColor: "#bbb"
                readonly property color invalidDatecolor: "#dddddd"
                readonly property color textColor: "#80DEEA"
                readonly property color backgroundColorInvisible: "#EEEEEE"
                readonly property color backgroundColorVisible: "transparent"

                Rectangle {
                    anchors.fill: parent
                    border.width: 3
                    border.color: styleData.date !== undefined && styleData.selected ? selectedDateColor : "transparent"                    
                    color: {
                        var color
                        if (styleData.valid) {
                            color = styleData.visibleMonth ? backgroundColorVisible : backgroundColorInvisible
                        }
                        color;

                    }
                    anchors.margins: styleData.selected ? -1 : 0

                    Text {
                        id: dayDelegateText
                        text: styleData.date.getDate()
                        anchors.centerIn: parent
                        font.pixelSize: 18
                        color: {
                            var color = invalidDatecolor;
                            if (styleData.valid) {
                                color = styleData.visibleMonth ? textColor : differentMonthDateTextColor;
                            }
                            color;
                        }
                    }

                    Text {
                        id: lunarDayDelegateText
                        text: {
                            var lunarDate = LunarTools.convertSolar2Lunar(styleData.date, 7)
                            if (lunarDate.day === 1) {
                                return lunarDate.day + "/" + lunarDate.month
                            }
                            return lunarDate.day
                        }
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 5
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        font.pixelSize: 12
                        color: {
                            var color = invalidDatecolor;
                            if (styleData.valid) {
                                color = styleData.visibleMonth ? textColor : differentMonthDateTextColor;
                            }
                            color;
                        }
                    }
                }

            }

            navigationBar: Rectangle {
                id: navigation
                height: 64
                color: "#FFCC80"
                Text {
                    id: monthDelegateText
                    text: styleData.title
                    anchors.centerIn: parent
                    font.pixelSize: 18
                }
            }
        }
    }

    Calendar {
        id: calendar
        width: parent.width
        height: parent.height * 0.5
        frameVisible: true
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

    Loader {
        id: viewArea
        width: parent.width
        height: parent.height * 0.5
    }
}
