import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4

Popup {
    id: popupCtrl
    padding: 0

    Rectangle {
        id: backgroundRg
        width: popupCtrl.width
        height: popupCtrl.height
        color: "black"
//        opacity: 0.8

//        ScrollView {
//            anchors.fill: parent
//            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
//            verticalScrollBarPolicy: Qt.ScrollBarAsNeeded
//            contentItem: Rectangle {
//                id: contentRg
//                width: popupCtrl.width
//                height: popupCtrl.height
//                //color: "#eff3e7"
////                opacity: 0.8
//            }
//        }
    }

    Component.onCompleted: {
    }
}
