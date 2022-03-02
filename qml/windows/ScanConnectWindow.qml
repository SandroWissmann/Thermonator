import QtQuick 2.15
import QtQuick.Layouts 1.15

import "../components"

Item {
    id: window_item_root
    property QtObject controller: scanConnectWindowController
    property bool connectButtonIsActive: controller.connectButtonIsActive
    property var model: controller.scannedDevicesModel

    ColumnLayout {
        id: window_rowLayout
        anchors.fill: parent
        spacing: 0

        // swap list view with scanning animation?
        ListView {
            id: window_listView
            Layout.fillWidth: true
            Layout.preferredHeight: window_item_root.height * 0.8

            model: window_item_root.model

            delegate: ScanConnectWindowDelegate {
                property variant modelData: model

                width: window_listView.width
                height: window_listView.height / 10
            }

            onCountChanged: {
                console.warn("Count change to:" + count)
            }
        }

        RowLayout {
            id: window_columnLayout
            Layout.fillWidth: true
            Layout.preferredHeight: window_item_root.height * 0.2

            ButtonWithText {
                id: window_scan_button
                text: "Scan"
                Layout.preferredWidth: window_item_root.width * 0.5
                Layout.fillHeight: true

                onClicked: {
                    controller.startScanning()
                }
            }
            // make only visible if item in table is clicked
            ButtonWithText {
                id: window_connect_button
                isEnabled: window_item_root.connectButtonIsActive
                text: "Connect"
                Layout.preferredWidth: window_item_root.width * 0.5
                Layout.fillHeight: true

                onClicked: {
                    controller.connectToBluetoothDevice()
                }
            }
        }
    }
}
