import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

import "windows"

Window {
    id: main_window_root_window
    width: 1024
    height: 768
    visible: true
    title: qsTr("Thermonator")

    ScanConnectWindow {
        id: main_window_scanConnectWindpw

        anchors.fill: parent
    }
}
