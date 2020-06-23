import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Rectangle {
    id: topBar
    color: Material.background

    Button {
        id: menuBtn
        width: height
        height: parent.height
        anchors.left: parent.left
        text: "Menu"

        onClicked: {
            systemMenu.open()
            console.log("Material.primary = " + Material.primary)
            console.log("Material.background = " + Material.background)
        }
    }

}
