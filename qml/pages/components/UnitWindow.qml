import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: unitWindow
    property alias fromUnitField_text: fromField_.text
    property alias toUnitField_text: toField_.text
    property alias currencyRateField: currencyField
    property alias currencyRateField_text: currencyField.text
    property alias currencyRateVisible: currencyField.visible
    //property alias convertLabel_text: convertingLabel.text

    Separator {
        id: separator1
        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            rightMargin: Theme.paddingLarge
        }
        color: Theme.secondaryHighlightColor
        height: 2
        width: parent.width - Theme.paddingLarge*2
    }

    Column {
        id: col
        anchors {
            top: separator1.bottom
            topMargin: Theme.paddingLarge/2
        }
        spacing: Theme.paddingMedium
        Column {
            spacing: Theme.paddingMedium
            x: Theme.paddingLarge
            Row {
                spacing: Theme.paddingSmall
                Label {
                    id: fromLabel
                    text: qsTr("From") + ":"
                    font.pixelSize: Theme.fontSizeMedium
                    color: Theme.primaryColor
                }
                Text {
                    id: fromField_
                    anchors.verticalCenter: fromLabel.verticalCenter
                    smooth: true
                    text: ""
                    font.pixelSize: Theme.fontSizeMedium
                    elide: Text.ElideRight
                    color: "steelblue"
                }
            }
            Row {
                spacing: Theme.paddingSmall
                Label {
                    id: toLabel
                    text: qsTr("To") + ":"
                    font.pixelSize: Theme.fontSizeMedium
                    color: Theme.primaryColor
                }
                Text {
                    id: toField_
                    anchors.verticalCenter: toLabel.verticalCenter
                    text: ""
                    smooth: true
                    font.pixelSize: Theme.fontSizeMedium
                    elide: Text.ElideRight
                    color: "steelblue"
                }
            }
            TextField {
                id: currencyField
                visible: false
                width: Screen.width * 0.9
                x: -Theme.paddingLarge
                height: Theme.itemSizeMedium
                text: ""
                placeholderText: qsTr("Give a new rate")
                label: qsTr("Currency rate")
                font.pixelSize: Theme.fontSizeLarge
                color: errorHighlight && text !== "" ? "red" : "lightgreen"
                placeholderColor: "steelblue"
                validator: DoubleValidator{}
                errorHighlight: text ? !acceptableInput : false
                inputMethodHints: Qt.ImhDigitsOnly | Qt.ImhNoPredictiveText
            }
        }
    }
    Separator {
        id: separator2
        anchors {
            top: col.bottom
            topMargin: Theme.paddingLarge
            left: parent.left
            leftMargin: Theme.paddingLarge
            rightMargin: Theme.paddingLarge
        }
        color: Theme.secondaryHighlightColor
        height: 2
        width: parent.width - Theme.paddingLarge*2
    }
}

