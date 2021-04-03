import QtQuick 2.5
import Sailfish.Silica 1.0
import "../scripts/HelperVariables.js" as HV
import Settings 1.0

Item {

    MySettings {
        id: myset
    }
    property real totalDistance: 0.0
    property bool isHorizontalLineActive: true
    property bool isVerticalLineActive: true
    property real cm_inch: myset.value("rulerunit",
                                       "cm") === "cm" ? 1 : 0.393700787

    Canvas {
        id: canvas
        width: Screen.width
        height: Screen.height
        smooth: true

        function drawBackground(cxt) {
            cxt.save()
            cxt.fillStyle = "#FFFF00"
            cxt.fillRect(0, 0, canvas.width, canvas.height)
            cxt.restore()
        }

        function drawHorizontalLines(cxt, cxt2) {
            cxt.save()
            cxt2.save()
            cxt.strokeStyle = "#000000"
            cxt.lineWidth = 1
            cxt.beginPath()
            for (var i = 0; i < 20; i++) {
                cxt.moveTo(0, totalDistance / cm_inch)
                cxt.lineTo(100, totalDistance / cm_inch)
                if (i > 0 && i < 20) {
                    cxt2.strokeText(i, 110, totalDistance / cm_inch + 10)
                }
                totalDistance += main.cRatio
                for (var k = 1; k < 10; k++) {
                    if (k === 5) {
                        cxt.moveTo(0, totalDistance / cm_inch)
                        cxt.lineTo(75, totalDistance / cm_inch)
                        totalDistance += main.cRatio
                    } else {
                        cxt.moveTo(0, totalDistance / cm_inch)
                        cxt.lineTo(50, totalDistance / cm_inch)
                        totalDistance += main.cRatio
                    }
                }
            }
            totalDistance = 0.0
            cxt.stroke()
            cxt.restore()
        }

        function drawVerticalLines(cxt, cxt2) {
            cxt.save()
            cxt2.save()
            cxt.strokeStyle = "#000000"
            cxt.lineWidth = 1
            cxt.beginPath()
            for (var i = 0; i < 20; i++) {
                cxt.moveTo(totalDistance / cm_inch, 0)
                cxt.lineTo(totalDistance / cm_inch, 100)
                if (i > 0 && i < 12) {
                    cxt2.strokeText(i, totalDistance / cm_inch - 5, 120)
                }
                totalDistance += main.cRatio
                for (var k = 1; k < 10; k++) {
                    if (k === 5) {
                        cxt.moveTo(totalDistance / cm_inch, 0)
                        cxt.lineTo(totalDistance / cm_inch, 75)
                        totalDistance += main.cRatio
                    } else {
                        cxt.moveTo(totalDistance / cm_inch, 0)
                        cxt.lineTo(totalDistance / cm_inch, 50)
                        totalDistance += main.cRatio
                    }
                }
            }
            totalDistance = 0.0
            cxt.stroke()
            cxt.restore()
        }

        onPaint: {
            var cxt = canvas.getContext('2d')
            var cxt2 = canvas.getContext('2d')
            cxt.globalCompositeOperation = "source-over"
            if (Screen.width >= 1080) {
                cxt2.font = "35px sans-serif"
            } else {
                cxt2.font = "20px sans-serif"
            }
            drawBackground(cxt)
            if (HV.HORIZONTALLINESACTIVE) {
                drawHorizontalLines(cxt, cxt2)
            }
            if (HV.VERTICALLINESACTIVE) {
                drawVerticalLines(cxt, cxt2)
            }
        }
    }
}
