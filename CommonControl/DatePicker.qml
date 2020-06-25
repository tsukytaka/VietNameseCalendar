import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0

TextField {
    id: datePicker
    text: datePickerDlg.selectedDate.toLocaleDateString(Locale.ShortFormat)
    MouseArea {
        anchors.fill: parent
        onClicked: {
            datePickerDlg.open()
        }
    }

    DatePickerDialog {
        id: datePickerDlg
        x: 0
        y: 0
    }

}
