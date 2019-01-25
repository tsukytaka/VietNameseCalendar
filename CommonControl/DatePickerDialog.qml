import QtQuick 2.0
import QtQuick.Controls 2.1
import Qt.labs.calendar 1.0
import QtQuick.Layouts 1.12

Dialog {
    id: dateDialog
    width: 240; height: 240

    ListView {
        id: listview
        spacing: 50
        clip: true
        anchors.fill: parent
        snapMode: ListView.SnapOneItem
        orientation: ListView.Horizontal
//          highlightRangeMode: ListView.StrictlyEnforceRange

        model: CalendarModel {
            from: new Date(2019, 0, 1)
            to: new Date(2019, 11, 31)
        }

        delegate: GridLayout {
            columns: 1

            DayOfWeekRow {
                locale: Qt.locale("en_US")
//                  Layout.column: 0
                Layout.fillWidth: true
            }

            MonthGrid {
                id: grid
                month: model.month
                year: 2019
                locale: Qt.locale("en_US")

                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        ScrollIndicator.horizontal: ScrollIndicator { }
    }

}
