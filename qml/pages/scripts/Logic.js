function createLine(startLine1X, startLine1Y, endLine1X, endLine1Y,
                    startLine2X, startLine2Y, endLine2X, endLine2Y,
                    hLine, vLine, parent) {
    var component = Qt.createComponent(Qt.resolvedUrl("../components/Line.qml"));
    if (component.status === Component.Ready) {
        var object = component.createObject(rulerPage, {
        "lineCanvas.sLine1X": startLine1X,
        "lineCanvas.sLine1Y": startLine1Y,
        "lineCanvas.eLine1X": endLine1X,
        "lineCanvas.eLine1Y": endLine1Y,
        "lineCanvas.sLine2X": startLine2X,
        "lineCanvas.sLine2Y": startLine2Y,
        "lineCanvas.eLine2X": endLine2X,
        "lineCanvas.eLine2Y": endLine2Y,
        "isHorizontal": hLine,
        "isVertical": vLine,
        "parent_": parent
    });
    return object;
    } else if (component.status === Component.Error) {
        console.log(component.errorString());
        return;
    }
}
