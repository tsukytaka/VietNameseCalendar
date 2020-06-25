import QtQuick 2.0
import QtQuick.Controls 2.1
import Qt.labs.calendar 1.0
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.0

Dialog {
    property var date : new Date()
    id: dateDialog
    width: 260; height: 240

    ListView {
        id: listview
        spacing: 50
        clip: true
        anchors.fill: parent
        snapMode: ListView.SnapOneItem
        orientation: ListView.Horizontal
//        highlightRangeMode: ListView.StrictlyEnforceRange

        model: CalendarModel {
            from: new Date(2020, 0, 1)
            to: new Date(2020, 11, 31)
        }

        delegate: GridLayout {
            columns: 1

            Label {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                text: grid.title
            }

            DayOfWeekRow {
                locale: Qt.locale("en_US")
                Layout.fillWidth: true
                delegate: Text {
                    text: model.shortName
                    color: Material.foreground
                }
            }

            MonthGrid {
                id: grid
                month: model.month
                year: 2020
                locale: Qt.locale("en_US")
                Layout.fillWidth: true
                Layout.fillHeight: true

                delegate: Rectangle {
                    color: model.date.toLocaleString(Qt.locale("en_US"),"dd.MM.yyyy") === dateDialog.date.toLocaleString(Qt.locale("en_US"),"dd.MM.yyyy") ? Material.primary : "transparent"
                    width:24
                    height: 24
                    Text {
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        opacity: model.month === grid.month ? 1 : 0.1
                        text: model.day
                        color: Material.foreground
                    }

                }

                onClicked: {
                    dateDialog.date = date
                }
            }
        }

        ScrollIndicator.horizontal: ScrollIndicator { }
    }

}
