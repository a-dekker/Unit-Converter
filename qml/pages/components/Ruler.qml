import QtQuick 2.1
import Sailfish.Silica 1.0
import "../scripts/HelperVariables.js" as HV

Item {

    property int lineW: 10
    property real pixelToMM: 3.7795
    property real totalDistance: 0.0
    property bool isHorizontalLineActive: true
    property bool isVerticalLineActive: true

    Canvas {
        id: canvas
        width: Screen.width
        // width: 540
        // height: 960
        height: Screen.height
        smooth: true

        function drawBackground(cxt) {
            cxt.save();
            cxt.fillStyle = "#FFFF00";
            cxt.fillRect(0, 0, canvas.width, canvas.height);
            cxt.restore();
        }

        function drawHorizontalLines(cxt, cxt2) {
            cxt.save();
            cxt2.save();
            cxt.strokeStyle = "#000000";
            cxt.lineWidth = 1;
            cxt.beginPath();
            for (var i = 0; i < 20; i++) {
                cxt.moveTo(0,totalDistance);
                cxt.lineTo(100,totalDistance);
                if (i > 0 && i < 10) {
                    cxt2.strokeText(i,110,totalDistance + 5);
                }
                totalDistance += main.cRatio;
                for (var k = 1; k < 10; k++) {
                    if (k === 5) {
                        cxt.moveTo(0,totalDistance);
                        cxt.lineTo(75,totalDistance);
                        totalDistance += main.cRatio;
                    } else {
                        cxt.moveTo(0,totalDistance);
                        cxt.lineTo(50,totalDistance);
                        totalDistance += main.cRatio;
                    }
                }
            }
            totalDistance = 0.0;
            cxt.stroke();
            cxt.restore();
        }

        function drawVerticalLines(cxt, cxt2) {
            cxt.save();
            cxt2.save();
            cxt.strokeStyle = "#000000";
            cxt.lineWidth = 1;
            cxt.beginPath();
            for (var i = 0; i < 20; i++) {
                cxt.moveTo(totalDistance,0);
                cxt.lineTo(totalDistance,100);
                if (i > 0 && i < 6) {
                    cxt2.strokeText(i,totalDistance - 5, 120);
                }
                totalDistance += main.cRatio
                for (var k = 1; k < 10; k++) {
                    if (k === 5) {
                        cxt.moveTo(totalDistance,0);
                        cxt.lineTo(totalDistance,75);
                        totalDistance += main.cRatio;
                    } else {
                        cxt.moveTo(totalDistance,0);
                        cxt.lineTo(totalDistance,50);
                        totalDistance += main.cRatio;
                    }
                }
            }
            totalDistance = 0.0;
            cxt.stroke();
            cxt.restore();
        }

        onPaint: {

            var cxt = canvas.getContext('2d')
            var cxt2 = canvas.getContext('2d')
            cxt.globalCompositeOperation = "source-over";
            cxt2.font="20px sans-serif";
            drawBackground(cxt);
            if (HV.HORIZONTALLINESACTIVE) {
                drawHorizontalLines(cxt,cxt2);
            }
            if (HV.VERTICALLINESACTIVE) {
                drawVerticalLines(cxt, cxt2);
            }
        }

    }
}
