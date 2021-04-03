import QtQuick 2.5
import Sailfish.Silica 1.0

Item {
    id: resultpanel
    visible: false
    property alias unittype_text: unit_type.text
    property alias unit1_text: panel_text1.text
    property alias unit1_value: panel_value1.text
    property alias unit2_text: panel_text2.text
    property alias unit2_value: panel_value2.text
    property alias unit3_text: panel_text3.text
    property alias unit3_value: panel_value3.text
    property alias unit4_text: panel_text4.text
    property alias unit4_value: panel_value4.text

    Column {
        id: col
        spacing: 0
        width: parent.width
        Label {
            id: unit_type
            text: ""
            anchors.horizontalCenter: parent.horizontalCenter
            color: Theme.primaryColor
            font.pixelSize: Theme.fontSizeExtraLarge
        }
        Label {
            // just some empty space
            text: " "
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: Theme.fontSizeLarge
        }
        Label {
            id: panel_value1
            anchors.horizontalCenter: parent.horizontalCenter
            text: ""
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
            color: Theme.highlightColor
            font.family: Theme.fontFamily
        }
        Label {
            id: panel_text1
            anchors.horizontalCenter: parent.horizontalCenter
            text: ""
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
            color: Theme.highlightColor
            font.family: Theme.fontFamily
        }
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "="
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
            color: Theme.highlightColor
            font.family: Theme.fontFamily
        }
        Label {
            id: panel_value2
            anchors.horizontalCenter: parent.horizontalCenter
            text: ""
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
            color: Theme.highlightColor
            font.family: Theme.fontFamily
        }
        Label {
            id: panel_text2
            anchors.horizontalCenter: parent.horizontalCenter
            text: ""
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
            color: Theme.highlightColor
            font.family: Theme.fontFamily
            elide: Text.ElideRight
        }
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: panel_text3.text === "" ? "" : "="
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
            color: Theme.highlightColor
            font.family: Theme.fontFamily
        }
        Label {
            id: panel_value3
            anchors.horizontalCenter: parent.horizontalCenter
            text: ""
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
            color: Theme.highlightColor
            font.family: Theme.fontFamily
        }
        Label {
            id: panel_text3
            anchors.horizontalCenter: parent.horizontalCenter
            text: ""
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
            color: Theme.highlightColor
            font.family: Theme.fontFamily
            elide: Text.ElideRight
        }
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: panel_text4.text === "" ? "" : "="
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
            color: Theme.highlightColor
            font.family: Theme.fontFamily
        }
        Label {
            id: panel_value4
            anchors.horizontalCenter: parent.horizontalCenter
            text: ""
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
            color: Theme.highlightColor
            font.family: Theme.fontFamily
        }
        Label {
            id: panel_text4
            anchors.horizontalCenter: parent.horizontalCenter
            text: ""
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
            color: Theme.highlightColor
            font.family: Theme.fontFamily
            elide: Text.ElideRight
        }
    }
}
