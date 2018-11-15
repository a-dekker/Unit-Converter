import QtQuick 2.0
import Sailfish.Silica 1.0
import "../pages/scripts/HelperVariables.js" as HV

Page {
    SilicaFlickable {
        anchors.fill: parent;
        Image {
            id: img
            anchors.centerIn: parent
            sourceSize.width: 86
            sourceSize.height: 86
            horizontalAlignment: Image.AlignRight
            source: "qrc:/images/images/harbour-unitconverter.png"
            smooth: true
            scale: 2

            transform: Translate{y: -Theme.paddingMedium}
        }
        Column {
            id: col
            spacing: 5
            anchors {
                top: img.bottom
                topMargin: Theme.paddingLarge
                horizontalCenter: parent.horizontalCenter
            }
            Label {
                id: label1
                text: qsTr("Unit Converter")
                horizontalAlignment: Text.AlignHCenter;
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeExtraLarge * 1.3
            }
            Label {
                text: qsTr("Sailfish OS")
                anchors.horizontalCenter: label1.horizontalCenter
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }
        }
        Text {
            anchors {
                top: col.bottom
                topMargin: Theme.paddingLarge
            }
            width: parent.width;
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere;
            horizontalAlignment: Text.AlignHCenter;
            textFormat: Text.RichText;
            font.pixelSize: Theme.fontSizeMedium
            color: Theme.primaryColor
            text: "<style>a:link { color: " + Theme.highlightColor + "; }</style>" +
                  qsTr("Version %1").arg(HV.VERSION) + "<br/>" +
                  qsTr('Created by Mikko Leppänen') + '<br/>' +
                  qsTr('Adapted by Arno Dekker') + '<br/>' +
                  qsTr('The source code is available at %1').
                  arg('<br/> <a href="https://github.com/a-dekker/Unit-Converter">%1</a>').arg("Project webpage")

            onLinkActivated: {
                Qt.openUrlExternally(link);
            }
        }
    }
}
