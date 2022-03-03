import QtQuick 2.15

Rectangle {
    id: delegate_rectangle_root

    property string macAddress: model.macAddress
    color: model.delegateBackgroundColor

    property QtObject controller

    border.color: "black"
    border.width: 1
    Text {
        id: delegate_text
        anchors.centerIn: parent
        text: delegate_rectangle_root.macAddress
    }

    MouseArea {
        id: delegate_mouseArea

        anchors.fill: parent
        onClicked: controller.selectScannedDevice(
                       delegate_rectangle_root.macAddress)
    }
}
