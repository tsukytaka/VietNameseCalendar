import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.1
import QtGraphicalEffects 1.0
import "SystemMenu"


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 920
    flags: Qt.Window | Qt.FramelessWindowHint

    Material.theme: Material.Light

    Loader {
        id: topMenu
        width: parent.width
        height: parent.height * 0.1
        source: "TopBar.qml"
    }

    Loader {
        id: viewArea
        width: parent.width
        height: parent.height * 0.9
        source: "MonthScreen/MonthView.qml"
    }

    SystemMenu {
        id:systemMenu
        x: 0
        y: 0
        width: 200
        height: 920
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    }
}
