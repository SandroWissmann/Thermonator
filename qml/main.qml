import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

import "pages"

Window {
    id: main_window_root_window
    width: 1024
    height: 768
    visible: true
    title: qsTr("Thermonator")

    Loader {
        id: main_window_page_loader
        anchors.fill: parent
    }

    Component.onCompleted: {
        main_window_page_loader.source = "pages/ScanConnectPage.qml"
    }
}
