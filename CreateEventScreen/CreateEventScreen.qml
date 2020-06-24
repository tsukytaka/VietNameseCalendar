import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0
import VCalendar 1.0
import "qrc:/CommonControl"

Rectangle {
    id: recCreateEvent
    color: Material.background

    CreateEventScreenVM {
        id: vmObject
        isAllDay: chkbAllDay.checked
    }

    Row {
        spacing: 40

        Button {
            id: btnCancel
            width: 48
            height: 48
            background: Image {
                id: bgtnCancel
                anchors.centerIn: parent
                source: "image://ImgProvider/baseline_clear_black_48dp.png"
            }


        }

        Column {
            id: mainArea
            width: 680
            height: 240

            TextField {
                id: txtfTitle
                width: mainArea.width
                height: 64
                placeholderText: vmObject.placeHolderTextTitle
                text: vmObject.eventTitle
            }

            Row {
                spacing: 20

                TextField{
                    id: txtfStartDate
                    width: 120
                    height: 64
//                    // Click to select date here
//                    MouseArea {
//                        anchors.fill: parent
//                        onClicked: {
////                            txtfStartDate.focus = true;
//                            onClicked: {
////                                datePickerDlg.parent = txtfStartDate
//                                datePickerDlg.open()
//                            }
//                        }
//                    }
                }

                TextField {
                    id: txtfStartTime
                    width: 120
                    height: 64
                    visible: !vmObject.isAllDay
                }

                Label {
                    id: txtConnectDate
                    width: 80
                    height: 64
                    verticalAlignment : Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: vmObject.connectDateText
                }

                TextField {
                    id: txtfEndTime
                    width: 120
                    height: 64
                    visible: !vmObject.isAllDay
                }

                TextField {
                    id: txtfEndDate
                    width: 120
                    height: 64
                }

                Button {
                    id: btnTimeZone
                    width: 96
                    height: 48
                    visible: !vmObject.isAllDay

                }
            }

            Row {

                CheckBox {
                    id: chkbAllDay
                    Component.onCompleted: {
                        checked = vmObject.isAllDay;
                    }
                }

                Label {
                    id: lbAllDay
                    text: vmObject.textAllDay
                }

                ComboBox {
                    id: cmbbRepeatMode
                    model: ListModel {
                        ListElement { text : 1}
                        ListElement { text : 2}
                        ListElement { text : 3}
                    }
                }
            }
        }

        Button {
            id: btnSave
            width: 96
            height: 48

            onClicked: {

            }
        }


    }
}
