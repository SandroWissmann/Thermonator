import QtQuick 2.15

Rectangle {
    id: component_rectangle_root
    implicitHeight: 60
    implicitWidth: 100

    state: "enabled"

    property bool isEnabled: true

    signal clicked

    MouseArea {
        id: component_mouseArea
        anchors.fill: parent

        onClicked: {
            if (!isEnabled) {
                return
            }
            component_rectangle_root.clicked()
        }

        onPressed: {
            if (!component_rectangle_root.isEnabled) {
                return
            }
            component_rectangle_root.state = "pressed"
        }
        onReleased: {
            if (!component_rectangle_root.isEnabled) {
                return
            }

            component_rectangle_root.state = "enabled"
        }
    }

    states: [
        State {
            name: "disabled"
            PropertyChanges {
                target: component_rectangle_root
                color: "blue"
                border.color: "black"
            }
        },
        State {
            name: "enabled"
            PropertyChanges {
                target: component_rectangle_root
                color: "yellow"
                border.color: "yellow"
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: component_rectangle_root
                color: "orange"
                border.color: "orange"
            }
        }
    ]

    Component.onCompleted: {
        if (!isEnabled) {
            state = "disabled"
        }
    }

    onIsEnabledChanged: {
        if (isEnabled) {
            state = "enabled"
        } else {
            state = "disabled"
        }
    }
}
