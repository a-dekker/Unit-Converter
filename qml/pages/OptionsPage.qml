import QtQuick 2.0
import Sailfish.Silica 1.0
import "scripts/HelperVariables.js" as HV
import Settings 1.0

Dialog {
    id: dialog
    width: Screen.width
    height: Screen.height

    MySettings {
        id: myset
    }

    SilicaFlickable {
        id: view
        anchors.fill: parent
        clip: true
        focus: true
        contentHeight: col.height + dialogHeader.height + 2 * Theme.paddingMedium

        DialogHeader {
            id: dialogHeader
            width: parent.width
        }

        ScrollDecorator {}

        Column {
            id: col
            anchors {
                top: dialogHeader.bottom
                topMargin: Theme.paddingMedium
                horizontalCenter: parent.horizontalCenter
            }
            width: dialog.width
            spacing: Theme.paddingMedium

            SectionHeader {
                text: qsTr("Ruler")
                font.family: "Verdana"
            }
            TextArea {
                id: textarea
                focus: true
                font.family: "Verdana"
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                wrapMode: TextEdit.WordWrap
                text: qsTr("You can activate/deactivate ruler's horizontal/vertical scale. If you deactivate one of the scales, " +
                           "you need to touch(or multi-touch) on the screen in order to bring the measurement lines visible. " +
                           "By default the ruler page's back navigation is off. " +
                           "It can be activated by pressing on the top-left corner of the screen.")
                readOnly: true

            }
            TextSwitch {
                id: hActivationSwitch
                text: qsTr("Activate ruler's horizontal lines")
                description: qsTr("Activates ruler's horizontal lines")
                onCheckedChanged: {
                    if (!checked && !vActivationSwitch.checked) {
                        HV.HORIZONTALLINESACTIVE = checked;
                        vActivationSwitch.checked = true;
                    } else {
                        HV.HORIZONTALLINESACTIVE = checked;
                    }
                }
            }
            TextSwitch {
                id: vActivationSwitch
                text: qsTr("Activate ruler's vertical lines")
                description: qsTr("Activates ruler's vertical lines")
                onCheckedChanged: {
                    if (!checked && !vActivationSwitch.checked) {
                        HV.VERTICALLINESACTIVE = checked;
                        hActivationSwitch.checked = true;
                    } else {
                        HV.VERTICALLINESACTIVE = checked;
                    }
                }
            }
            SectionHeader {
                text: qsTr("Currency")
                font.family: "Verdana"
            }
            TextArea {
                focus: true
                font.family: "Verdana"
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                wrapMode: TextEdit.WordWrap
                text: qsTr("You can change the rate at which the currency rates are updated. " +
                           "If you disable the automatic update, you have to start the update process manually.")
                readOnly: true
            }
            ComboBox {
                id: intervalselection
                visible: true
                label: qsTr("Select update interval")
                width: parent.width
                currentIndex: currencycache.interval()
                menu: ContextMenu {
                    MenuItem { text: qsTr("Daily update"); font.family: "Verdana" }
                    MenuItem { text: qsTr("Weekly update"); font.family: "Verdana" }
                    MenuItem { text: qsTr("Monthly update"); font.family: "Verdana" }
                    MenuItem { text: qsTr("Always at application start"); font.family: "Verdana" }
                    MenuItem { text: qsTr("Disable automatic update"); font.family: "Verdana" }
                }
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Update currency cache")
                onClicked: currencycache.updateNow()
            }
            SectionHeader {
                font.family: "Verdana"
                text: qsTr("Notation")
            }
            ComboBox {
                id: notation
                width: parent.width
                label: qsTr("Select number notation")
                description: qsTr("Preferred number notation")
                currentIndex: myset.value("notation","scientific") === "scientific" ? 1 : 0
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("standard") // 0
                        font.family: "Verdana"
                    }
                    MenuItem {
                        text: qsTr("scientific") // 1
                        font.family: "Verdana"
                    }
                }
            }
        }
    }
    onAccepted: {
        currencycache.setInterval(intervalselection.currentIndex)
        if (notation.currentIndex === 0) {
            myset.setValue("notation", "standard")
        }
        if (notation.currentIndex === 1) {
            myset.setValue("notation", "scientific")
        }
        myset.sync()
    }
    onOpened: {
        hActivationSwitch.checked = HV.HORIZONTALLINESACTIVE;
        vActivationSwitch.checked = HV.VERTICALLINESACTIVE;
    }
}
