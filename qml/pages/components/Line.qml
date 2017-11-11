import QtQuick 2.0
import Sailfish.Silica 1.0
import "../scripts/HelperVariables.js" as HV

Item {
    anchors.fill: parent
    width: Screen.width
    height: Screen.height

    property QtObject parent_
    property alias lineCanvas: canvas
    property bool isHorizontal: false
    property bool isVertical: false

    property real objW: isHorizontal && isVertical ? canvas.sLine2Y : isHorizontal && !isVertical ?
                                                       Math.abs(canvas.sLine1Y - canvas.sLine2Y) : 0.0
    property real objH: isHorizontal && isVertical ? canvas.sLine1X : !isHorizontal && isVertical ?
                                                         Math.abs(canvas.sLine1X - canvas.sLine2X) : 0.0

    property bool line1Active: false
    property bool line2Active: false

    Canvas {
        id: canvas
        width: Screen.width
        height: Screen.height

        property real sLine1X: 0.0
        property real eLine1X: 0.0
        property real sLine1Y: 0.0
        property real eLine1Y: 0.0
        property real sLine2X: 0.0
        property real eLine2X: 0.0
        property real sLine2Y: 0.0
        property real eLine2Y: 0.0
        property var cxtLine1
        property var cxtLine2

        z: 10
        smooth: true
        onPaint: {
            if (isHorizontal && isVertical) {
                cxtLine1 = canvas.getContext('2d')
                cxtLine1.globalCompositeOperation = "source-over";
                cxtLine1.beginPath();
                cxtLine1.moveTo(sLine1X, sLine1Y);
                cxtLine1.lineTo(eLine1X, eLine1Y);
                cxtLine1.lineWidth = 2
                cxtLine1.strokeStyle = "#FF3300";
                cxtLine1.stroke();

                cxtLine2 = canvas.getContext('2d')
                cxtLine2.globalCompositeOperation = "source-over";
                cxtLine2.beginPath();
                cxtLine2.moveTo(sLine2X,sLine2Y);
                cxtLine2.lineTo(eLine2X, eLine2Y);
                cxtLine2.lineWidth = 2
                cxtLine2.strokeStyle = "#FF3300";
                cxtLine2.stroke();
            } else if (isHorizontal && !isVertical) {
                cxtLine1 = canvas.getContext('2d')
                cxtLine1.globalCompositeOperation = "source-over";
                cxtLine1.beginPath();
                cxtLine1.moveTo(sLine1X, sLine1Y);
                cxtLine1.lineTo(eLine1X, eLine1Y);
                cxtLine1.lineWidth = 2
                cxtLine1.strokeStyle = "#FF3300";
                cxtLine1.stroke();

                cxtLine2 = canvas.getContext('2d')
                cxtLine2.globalCompositeOperation = "source-over";
                cxtLine2.beginPath();
                cxtLine2.moveTo(sLine2X,sLine2Y);
                cxtLine2.lineTo(eLine2X, eLine2Y);
                cxtLine2.lineWidth = 2
                cxtLine2.strokeStyle = "#FF3300";
                cxtLine2.stroke();
            } else if (!isHorizontal && isVertical) {
                cxtLine1 = canvas.getContext('2d')
                cxtLine1.globalCompositeOperation = "source-over";
                cxtLine1.beginPath();
                cxtLine1.moveTo(sLine1X, sLine1Y);
                cxtLine1.lineTo(eLine1X, eLine1Y);
                cxtLine1.lineWidth = 2
                cxtLine1.strokeStyle = "#FF3300";
                cxtLine1.stroke();

                cxtLine2 = canvas.getContext('2d')
                cxtLine2.globalCompositeOperation = "source-over";
                cxtLine2.beginPath();
                cxtLine2.moveTo(sLine2X,sLine2Y);
                cxtLine2.lineTo(eLine2X, eLine2Y);
                cxtLine2.lineWidth = 2
                cxtLine2.strokeStyle = "#FF3300";
                cxtLine2.stroke();
            }
        }

        MouseArea {
            id: area
            anchors.fill: parent
            onPressed: {
                if (mouseX < 50 && mouseY < 50) {
                    parent_.backNavigation = true;
                } else {
                    parent_.backNavigation = false;
                }

                switch (findLine(mouseX, mouseY)) {
                    case 0:
                        parent_.backNavigation = true;
                        break;
                    case 1:
                        line1Active = true;
                        line2Active = false;
                        break;
                    case 2:
                        line1Active = false;
                        line2Active = true;
                        break;
                }
            }
            onMouseXChanged: {
                if (line1Active) {
                    if (isHorizontal && isVertical) {
                        canvas.sLine1X = mouseX;
                        canvas.eLine1X = mouseX;
                    } else if (!isHorizontal && isVertical) {
                        canvas.sLine1X = mouseX;
                        canvas.eLine1X = mouseX;
                    }
                } else if (line2Active) {
                    if (!isHorizontal && isVertical) {
                        canvas.sLine2X = mouseX;
                        canvas.eLine2X = mouseX;
                    }
                }
            }

            onMouseYChanged: {
                if (line1Active) {
                    if (!isVertical && isHorizontal) {
                        canvas.sLine1Y = mouseY;
                        canvas.eLine1Y = mouseY;
                    }
                } else if (line2Active) {
                    if (isHorizontal && isVertical) {
                        canvas.sLine2Y = mouseY;
                        canvas.eLine2Y = mouseY;
                    } else if (isHorizontal && !isVertical) {
                        canvas.sLine2Y = mouseY;
                        canvas.eLine2Y = mouseY;
                    }
                }
            }

            onPositionChanged: {
                canvas.cxtLine1.clearRect(0, 0, canvas.width, canvas.height);
                canvas.cxtLine2.clearRect(0, 0, canvas.width, canvas.height);
                canvas.requestPaint();
            }

            onReleased: {
                line1Active = false;
                line2Active = false;
            }
        }
    }

    function findLine(x,y) {

        var lineArray = [calculatePointLineDistance(x,y,1) < 50,
                         calculatePointLineDistance(x,y,2) < 50];
        if (lineArray.every(function(element, index, array) {
            return element === false;
          })) {
            return 0;
        }
        return lineArray.indexOf(true) + 1;
    }

    function calculatePointLineDistance(x, y, lineNum) {
        // d = abs(det(x2 - x1, x1 - x0)) / norm(x2 - x1)
        switch (lineNum) {
         case 1:
             var d1 = Math.abs((canvas.sLine1X - canvas.eLine1X) * (canvas.sLine1Y - y) -
                                (canvas.sLine1X - x) * (canvas.sLine1Y - canvas.eLine1Y)) /
                     Math.sqrt(Math.pow(canvas.sLine1X - canvas.eLine1X,2) +
                                                        Math.pow(canvas.sLine1Y - canvas.eLine1Y,2))
             return d1;
         case 2:
             var d2 = Math.abs((canvas.sLine2X - canvas.eLine2X) * (canvas.sLine2Y - y) -
                                (canvas.sLine2X - x) * (canvas.sLine2Y - canvas.eLine2Y)) /
                     Math.sqrt(Math.pow(canvas.sLine2X - canvas.eLine2X,2) +
                                                        Math.pow(canvas.sLine2Y - canvas.eLine2Y,2))
             return d2;

        }
    }
}
