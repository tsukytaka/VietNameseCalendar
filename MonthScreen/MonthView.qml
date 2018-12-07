import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1
import QtQuick.Controls.Material 2.0
import VCalendar 1.0

Calendar {
    id: calendar
    width: parent.width
    height: parent.height * 0.5
    frameVisible: true
    selectedDate: new Date()
    focus: true
    style: calstyle
    navigationBarVisible: false

    onVisibleMonthChanged: {
//            calendarManager.date = new Date(calendar.visibleYear, calendar.visibleMonth, 1)
    }
    onVisibleYearChanged: {
//            calendarManager.date = new Date(calendar.visibleYear, calendar.visibleMonth, 1)
    }

    Component {
        id: calstyle
        CalendarStyle {
            dayDelegate: Item {
                id: thisItem
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: styleData.selected ? 0 : 2
                    border.width: 2
    //                    border.color: styleData.date !== undefined && styleData.selected ? selectedDateColor : "transparent"

    //                    color: {
    //                        var color
    //                        if (styleData.valid) {
    //                            color = styleData.visibleMonth ? backgroundColorVisible : backgroundColorInvisible
    //                        }
    //                        color;
    //                    }


                    Text {
                        id: dayDelegateText
                        text: styleData.date.getDate()
                        anchors.centerIn: parent
                        font.pixelSize: 18
    //                        color: {
    //                            var color = invalidDatecolor;
    //                            if (styleData.valid) {
    //                                color = styleData.visibleMonth ? textColor : differentMonthDateTextColor;
    //                            }
    //                            color;
    //                        }
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
    //                        color: {
    //                            var color = invalidDatecolor;
    //                            if (styleData.valid) {
    //                                color = styleData.visibleMonth ? textColor : differentMonthDateTextColor;
    //                            }
    //                            color;
    //                        }
                    }
                }

            }

            navigationBar: Rectangle {
                id: navigation
                height: 64
                color: Material.color(Material.Orange , Material.Shade200)



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




