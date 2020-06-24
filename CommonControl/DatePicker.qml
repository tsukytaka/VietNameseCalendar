import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0

TextField {
    id: datePicker
    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("test")
            datePickerDlg.open()
        }
    }

    DatePickerDialog {
        id: datePickerDlg
        x: 0
        y: 0
        width: 128
        height: 128
    }

}
