import QtQuick 2.5
import Sailfish.Silica 1.0
import "components"
import "scripts/HelperVariables.js" as HV
import "scripts/Logic.js" as Logic
import Settings 1.0

Page {
    id: rulerPage
    width: Screen.width
    backNavigation: false

    property var lineObj: null

    MySettings {
        id: myset
    }

    SilicaFlickable {
        id: flickable
        anchors.fill: parent
        contentHeight: 1000

        Component.onCompleted: {
            HV.HORIZONTALLINESACTIVE = myset.value("horizontallinesactive",
                                                   "true") === "true"
            HV.VERTICALLINESACTIVE = myset.value("verticallinesactive",
                                                 "true") === "true"
        }

        Column {
            spacing: 0
            anchors {
                bottom: parent.bottom
                bottomMargin: Theme.paddingExtraLarge
                right: parent.right
            }
            Label {
                id: measurementMM
                text: lineObj !== null ? Number(
                                             lineObj.objW / main.cRatio).toFixed(
                                             1) + ", " + Number(
                                             lineObj.objH / main.cRatio).toFixed(
                                             1) + " mm" : ""
                font.bold: true

                color: "#0066CC"
                font.pixelSize: Theme.fontSizeLarge
                font.family: "Modern"
            }
            Label {
                id: measurementInch
                anchors.left: measurementMM.left
                text: lineObj !== null ? Number(
                                             lineObj.objW / main.cRatio * 0.039370079).toFixed(
                                             2) + ", " + Number(
                                             lineObj.objH / main.cRatio * 0.039370079).toFixed(
                                             2) + " in" : ""
                font.bold: true

                color: "#0066CC"
                font.pixelSize: Theme.fontSizeLarge
                font.family: "Modern"
            }
            rotation: 90
            transform: Translate {
                y: -150
                x: 50
            }
            z: 100
        }
        Ruler {
            id: ruler
            anchors {
                top: parent.top
                left: parent.left
            }
        }

        MultiPointTouchArea {
            id: touchArea
            anchors.fill: parent
            touchPoints: [
                TouchPoint {
                    id: point1
                },
                TouchPoint {
                    id: point2
                }
            ]
            property var p1: {
                "x": point1.x,
                "y": point1.y
            }
            property var p2: {
                "x": point2.x,
                "y": point2.y
            }

            onPressed: {
                if (lineObj === null && HV.HORIZONTALLINESACTIVE
                        && !HV.VERTICALLINESACTIVE) {
                    if (p1.y < 1) {
                        p1.y = 100
                    } else if (p2.y < 1) {
                        p2.y = 100
                    }

                    lineObj = Logic.createLine(0, p1.y, parent.width, p1.y, 0,
                                               p2.y, parent.width, p2.y, true,
                                               false, rulerPage)
                    touchArea.enabled = false
                } else if (lineObj === null && !HV.HORIZONTALLINESACTIVE
                           && HV.VERTICALLINESACTIVE) {
                    if (p1.x < 1) {
                        p1.x = 100
                    } else if (p2.x < 1) {
                        p2.x = 100
                    }
                    lineObj = Logic.createLine(p1.x, 0, p1.x, rulerPage.height,
                                               p2.x, 0, p2.x, rulerPage.height,
                                               false, true, rulerPage)
                    touchArea.enabled = false
                }
            }
        }
    }

    onStatusChanged: {
        if (status === PageStatus.Activating) {
            if (lineObj !== null && typeof lineObj !== 'undefined') {
                lineObj.destroy()
                lineObj = null
            }
            if (HV.HORIZONTALLINESACTIVE && HV.VERTICALLINESACTIVE) {
                lineObj = Logic.createLine(parent.width / 2, 0,
                                           parent.width / 2, parent.height, 0,
                                           parent.height / 2,
                                           parent.width, parent.height / 2, true,
                                           true, rulerPage)
            }
        }
    }
}
