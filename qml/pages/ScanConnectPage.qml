import QtQuick 2.15
import QtQuick.Layouts 1.15

import "../components"
import "ScanConnectPage"

Item {
    id: page_item_root
    property QtObject controller: scanConnectPageController
    property bool connectButtonIsActive: controller.connectButtonIsActive
    property var model: controller.scannedDevicesModel

    ColumnLayout {
        id: page_rowLayout
        anchors.fill: parent
        spacing: 0

        // swap list view with scanning animation?
        ListView {
            id: page_listView
            Layout.fillWidth: true
            Layout.preferredHeight: page_item_root.height * 0.8

            model: page_item_root.model

            delegate: ScanConnectPageDelegate {
                property variant modelData: model

                controller: page_item_root.controller

                width: page_listView.width
                height: page_listView.height / 10
            }
        }

        RowLayout {
            id: page_columnLayout
            Layout.fillWidth: true
            Layout.preferredHeight: page_item_root.height * 0.2

            ButtonWithText {
                id: page_scan_button
                text: "Scan"
                Layout.preferredWidth: page_item_root.width * 0.5
                Layout.fillHeight: true

                onClicked: {
                    controller.startScanning()
                }
            }
            // make only visible if item in table is clicked
            ButtonWithText {
                id: page_connect_button
                isEnabled: page_item_root.connectButtonIsActive
                text: "Connect"
                Layout.preferredWidth: page_item_root.width * 0.5
                Layout.fillHeight: true

                onClicked: {
                    controller.connectToSelectedBluetoothDevice()
                }
            }
        }
    }
}
