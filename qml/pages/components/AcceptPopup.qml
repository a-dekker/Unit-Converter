import QtQuick 2.0
import Sailfish.Silica 1.0
import "../scripts/HelperVariables.js" as HV

Item {
    id: messageBox
    property bool active: false

    Column {
        id: col
        Label {
            id: label
            text: "Close ruler?"
            font.pixelSize: Theme.fontSizeLarge
            color: "white"
        }
        Row {
            id: row
            anchors.horizontalCenter: label.horizontalCenter
            Button {
                id: okButton
                text: "Ok"
                color: "white"

                onClicked: {
                    pageStack.clear();
                    pageStack.push(Qt.resolvedUrl("../MainPage.qml"));
                }
            }
            Button {
                id: cancelButton
                text: "Cancel"
                color: "white"

                onClicked: {
                    active = false;
                }
            }
        }
    }
    states: [
        State {
            name: "show notification"
            when: active
            PropertyChanges {
                target: col; visible: true
            }
        },
        State {
            name: "hide notification"
            when: !active
            PropertyChanges {
                target: col; visible: false
            }
        }
    ]
    transitions: Transition {
            from: "*"
            to: "*"
            NumberAnimation { property: "visible"
                              duration: 500; easing.type: Easing.InOutQuad }
            }
    Timer {
        id: timer
        interval: 5000
        repeat: false
        running: active
        onTriggered: {active = false;}
    }
}
