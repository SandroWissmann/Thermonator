import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

import "components"

Window {
    id: main_window_root_window
    width: 1024
    height: 768
    visible: true
    title: qsTr("Thermonator")

    property QtObject controller: scanConnectWindowController
    property bool connectButtonIsActive: controller.connectButtonIsActive

    ColumnLayout {
        id: main_window_rowLayout
        anchors.fill: parent
        spacing: 0

        // swap list view with scanning animation?
        ListView {
            id: main_window_listView
            Layout.fillWidth: true
            Layout.preferredHeight: main_window_root_window.height * 0.8
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
                width: main_window_listView.width
                height: main_window_listView.height / 10

                border.color: "black"
                border.width: 1
                Text {
                    anchors.centerIn: parent
                    text: delgateText
                }
            }
        }

        RowLayout {
            id: main_window_columnLayout
            Layout.fillWidth: true
            Layout.preferredHeight: main_window_root_window.height * 0.2

            ButtonWithText {
                id: main_window_scan_button
                text: "Scan"
                Layout.preferredWidth: main_window_root_window.width * 0.5
                Layout.fillHeight: true

                onClicked: {
                    controller.startScanning()
                }
            }
            // make only visible if item in table is clicked
            ButtonWithText {
                id: main_window_connect_button
                isEnabled: main_window_root_window.connectButtonIsActive
                text: "Connect"
                Layout.preferredWidth: main_window_root_window.width * 0.5
                Layout.fillHeight: true

                onClicked: {
                    controller.connectToBluetoothDevice()
                }
            }
        }
    }
}
