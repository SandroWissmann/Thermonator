import QtQuick 2.15

Rectangle {
    id: delegate_rectangle_root

    property string macAddress: model.macAddress

    border.color: "black"
    border.width: 1
    Text {
        id: delegate_text
        anchors.centerIn: parent
        text: delegate_rectangle_root.macAddress
    }

    Component.onCompleted: {
        console.warn("create delegate")
    }
}
