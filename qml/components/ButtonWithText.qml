import QtQuick 2.15

Button {
    id: component_button_root

    property alias text: component_text.text

    Text {
        id: component_text
        anchors.centerIn: parent
    }

    onStateChanged: {
        if (state === "disabled") {
            component_text.color = "grey"
        } else if (state === "enabled") {
            component_text.color = "black"
        } else if (state === "pressed") {
            component_text.color = "black"
        }
    }
}
