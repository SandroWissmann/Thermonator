import QtQuick 2.15

Button {
    id: component_button_root

    property alias text: component_text.text

    Text {
        id: component_text
        anchors.centerIn: parent
    }

    states: [
        State {
            name: "disabled"
            PropertyChanges {
                target: component_text
                color: "grey"
            }
        },
        State {
            name: "enabled"
            PropertyChanges {
                target: component_text
                color: "black"
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: component_text
                color: "black"
            }
        }
    ]
}
