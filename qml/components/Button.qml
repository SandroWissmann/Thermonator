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

            console.warn("pressed")
        }

        onReleased: {
            if (!component_rectangle_root.isEnabled) {
                return
            }

            component_rectangle_root.state = "enabled"
            console.warn("enabled")
        }
    }

    states: [
        State {
            name: "disabled"
            PropertyChanges {
                target: component_rectangle_root
                color: "white"
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

    onStateChanged: {
        console.warn("sandroo: state changen: " + state)
    }

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
