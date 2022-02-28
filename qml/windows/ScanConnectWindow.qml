import QtQuick 2.15
import QtQuick.Layouts 1.15

import "../components"

Item {
    id: window_item_root
    property QtObject controller: scanConnectWindowController
    property bool connectButtonIsActive: controller.connectButtonIsActive

    ColumnLayout {
        id: window_rowLayout
        anchors.fill: parent
        spacing: 0

        // swap list view with scanning animation?
        ListView {
            id: window_listView
            Layout.fillWidth: true
            Layout.preferredHeight: window_item_root.height * 0.8
            model: ListModel {
                ListElement {
                    delgateText: "00:00:5e:00:53:af"
                }
                ListElement {
                    delgateText: "01:00:5e:00:53:af"
                }
                ListElement {
                    delgateText: "02:00:5e:00:53:af"
                }
                ListElement {
                    delgateText: "03:00:5e:00:53:af"
                }
                ListElement {
                    delgateText: "04:00:5e:00:53:af"
                }
                ListElement {
                    delgateText: "05:00:5e:00:53:af"
                }
                ListElement {
                    delgateText: "06:00:5e:00:53:af"
                }
                ListElement {
                    delgateText: "07:00:5e:00:53:af"
                }
                ListElement {
                    delgateText: "08:00:5e:00:53:af"
                }
                ListElement {
                    delgateText: "09:00:5e:00:53:af"
                }
            }
            delegate: Rectangle {
                width: window_listView.width
                height: window_listView.height / 10

                border.color: "black"
                border.width: 1
                Text {
                    anchors.centerIn: parent
                    text: delgateText
                }
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
