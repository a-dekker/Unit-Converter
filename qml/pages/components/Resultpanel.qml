import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: resultpanel
    visible: false
    property alias unit1_text: panel_text1.text
    property alias unit1_value: panel_value1.text
    property alias unit2_text: panel_text2.text
    property alias unit2_value: panel_value2.text

    Column {
        anchors.centerIn: parent
        spacing: 20
        Column {
            id: col
            spacing: 0
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: Theme.paddingSmall
            Text {
                id: panel_value1
                anchors.horizontalCenter: panel_text1.horizontalCenter
                text: ""
                font.pixelSize: Theme.fontSizeLarge
                font.bold: true
                color: Theme.highlightColor
                font.family: Theme.fontFamily
            }
            Text {
                id: panel_text1
                horizontalAlignment: Text.AlignHCenter
                text: ""
                font.pixelSize: Theme.fontSizeLarge
                font.bold: true
                color: Theme.highlightColor
                font.family: Theme.fontFamily
            }
        }

        Canvas {
            id: canvas
            anchors.horizontalCenter: col.horizontalCenter
            smooth: true
            width: 75
            height: 25
            onPaint: {
                var cxt = canvas.getContext('2d')
                var width_ = width
                var height_ = height
                var arrowW_ = 0.35*width_
                var arrowH_ = 0.55*height_
                cxt.clearRect(0,0,width_,height_)
                cxt.fillStyle = "#0066FF"
                cxt.beginPath()
                cxt.moveTo(0,height_/2)
                cxt.lineTo(arrowW_,0)
                cxt.lineTo(arrowW_,(height_-arrowH_)/2)
                cxt.lineTo(width_-arrowW_,(height_-arrowH_)/2)
                cxt.lineTo(width_-arrowW_,0)
                cxt.lineTo(width_,height_/2)
                cxt.lineTo(width_-arrowW_,height_)
                cxt.lineTo(width_-arrowW_,height_/2+arrowH_/2)
                cxt.lineTo(arrowW_,height_/2+arrowH_/2)
                cxt.lineTo(arrowW_,height_)
                cxt.fill()
                cxt.closePath()
            }
        }
        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: Theme.paddingSmall
            Text {
                id: panel_value2
                anchors.horizontalCenter: parent.horizontalCenter
                text: ""
                font.pixelSize: Theme.fontSizeLarge
                font.bold: true
                color: Theme.highlightColor
                font.family: Theme.fontFamily
            }
            Text {
                id: panel_text2
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
}
