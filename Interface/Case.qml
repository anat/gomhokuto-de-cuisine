import QtQuick 1.0

BorderImage {
    id: button

    Rectangle {
        id: shade
        anchors.fill: button;
        radius: 10;
        color: "green";
        opacity: 1
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            doOp(operation)
            button.clicked()
        }
    }
    states: [
        State {
            name: "on_mouse"; when: mouseArea.pressed == true
            PropertyChanges { target: shade; opacity: .4 }
        }
    ]
}
