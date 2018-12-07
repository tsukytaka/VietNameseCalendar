import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: topBar

    Button {
        id: menuBtn
        width: height
        height: parent.height
        anchors.left: parent.left
        text: "Menu"

        onClicked: {
            systemMenu.open()
        }
    }

}
