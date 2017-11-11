import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.XmlListModel 2.0
import "scripts/UnitConververDB.js" as DB

/**
 * @brief Page
 */
Page {
    id: favouritesPage
    width: Screen.width
    height: Screen.height

    property var log: []
    property XmlListModel xmlListModel
    property Item contextMenu: null
    property bool menuOpen: contextMenu !== null
    property var ind

    function clearAll() {
        if (listModel.count > 0) {
            remorseItems.execute(qsTr("Deleting all favourites..."), function() {
                if (listModel.count > 0) {
                    var i = 0, count = listModel.count
                    for (; i < count; i++) {
                        DB.removeFavourite(log[i].unitconverter, log[i].fromUnit, log[i].fromValue,
                                           log[i].toUnit, log[i].toValue)
                    }
                    listModel.clear();
                    log = [];
                }
            });
        }
    }

    RemorsePopup { id: remorseItems;}


    SilicaListView {
        id: listView
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        clip: true

        model: ListModel {id: listModel}

        header: PageHeader {
            id: pageheader
            title: qsTr("Favourites")
        }

        ViewPlaceholder {
            enabled: listModel.count === 0
            text: qsTr("No favourites available")
        }

        PullDownMenu {
            MenuItem {
                id: menuItem
                text: qsTr("Delete all")
                onClicked: {
                    clearAll();
                }
            }
            MenuItem {
                text: qsTr("Add favourite")
                onClicked: pageStack.push(Qt.resolvedUrl("FavouriteDialog.qml"),
                                          {"xmlListModel": xmlListModel});
            }
        }
        spacing: Theme.paddingLarge

        delegate: favouriteDelegate

        VerticalScrollDecorator {}
    }

    Component {
        id: favouriteDelegate
        BackgroundItem {
            id: bgItem
            width: favouritesPage.width
            height: menuOpen ? contextMenu.height + col.childrenRect.height : col.childrenRect.height

            Column {
                id: col
                width: parent.width
                spacing: Theme.paddingMedium
                Text {
                    width: favouritesPage.width
                    horizontalAlignment: Text.AlignHCenter
                    text: String(fromUnit).toLowerCase() + " (" + fromUnitAbb + ")"
                    font.pixelSize: Theme.fontSizeMedium
                    color:Theme.primaryColor
                    font.family: Theme.fontFamily
                }
                Text {
                    id: fromValue_
                    width: favouritesPage.width
                    horizontalAlignment: Text.AlignHCenter
                    text: fromValue
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                    color: Theme.secondaryHighlightColor
                    font.family: Theme.fontFamily
                }

                Canvas {
                    id: canvas
                    anchors.horizontalCenter: fromValue_.horizontalCenter
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
                        var gradient1 = cxt.createLinearGradient(0,0,
                                                                 canvas.width,0)
                        gradient1.addColorStop(0, "#1919FF")
                        gradient1.addColorStop(0.25, "#3333FF")
                        gradient1.addColorStop(0.40, "#4D4DFF")
                        gradient1.addColorStop(0.5, '#4D4DFF')
                        gradient1.addColorStop(0.60, "#4D4DFF")
                        gradient1.addColorStop(0.75, "#3333FF")
                        gradient1.addColorStop(1.0, "#1919FF")
                        cxt.fillStyle = gradient1
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
                Text {
                    id: toValue_
                    width: favouritesPage.width
                    horizontalAlignment: Text.AlignHCenter
                    text: toValue
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                    color: Theme.secondaryHighlightColor
                    font.family: Theme.fontFamily
                }
                Text {
                    width: favouritesPage.width
                    horizontalAlignment: Text.AlignHCenter
                    text: String(toUnit).toLowerCase() + " (" + toUnitAbb + ")"
                    font.pixelSize: Theme.fontSizeMedium
                    color: Theme.primaryColor
                    font.family: Theme.fontFamily
                    elide: Text.ElideRight
                }
                Separator {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: favouritesPage.width * 0.9
                    height: 2
                    color: "#00FF00"
                }
            }

            onPressAndHold: {
                ind = index;
                if (!contextMenu) {
                    contextMenu = contextMenuComponent.createObject(listView)
                }
                contextMenu.show(bgItem)
            }
        }
    }

    Component {
        id: contextMenuComponent
        ContextMenu {
            MenuItem {
                text: "Update favourite"
                onClicked: pageStack.push(Qt.resolvedUrl("FavouriteDialog.qml"),
                                                        {"xmlListModel": xmlListModel,
                                                         "unittype": log[ind].unitconverter,
                                                         "unitTypeFrom": log[ind].fromUnit,
                                                         "unitTypeFromAbb": log[ind].fromUnitAbb,
                                                         "unitValueFrom": log[ind].fromValue,
                                                         "unitTypeTo": log[ind].toUnit,
                                                         "unitTypeToAbb": log[ind].toUnitAbb,
                                                         "unitValueTo": log[ind].toValue,
                                                         "isUpdate": true});
            }
            MenuItem {
                text: "Remove"
                onClicked: remorse.execute(contextMenu.parent, qsTr("Deleting favourite..."), function() {
                    DB.removeFavourite(log[ind].unitconverter, log[ind].fromUnit, log[ind].fromValue,
                                       log[ind].toUnit, log[ind].toValue)
                    log.splice(ind,1);
                    listModel.remove(ind);
                    if (ind > 1) {
                        listView.positionViewAtIndex(ind - 1,ListView.SnapPosition)
                    }
                });
            }

            RemorseItem { id: remorse;}
        }
    }

    onStatusChanged: {
        if (status === PageStatus.Activating) {
            if (listModel.count !== 0) listModel.clear();
            log = DB.getFavourites();
            var i = 0, count = log.length;
            for (; i < count; i++) {
                if (log[i].unitconverter === "CURRENCY") {
                    var res = String(converter.convert2(log[i].fromUnitAbb,
                                                        log[i].toUnitAbb, log[i].fromValue.replace(",","."),
                                                        "CURRENCY"));
                    res = res.replace(".",",");
                    if (res !== log[i].toValue) {
                        DB.updateFavourite("CURRENCY",log[i].fromUnit, log[i].fromValue, log[i].toUnit,
                                           log[i].toValue,"CURRENCY",log[i].fromUnit, log[i].fromUnitAbb,
                                           log[i].fromValue, log[i].toUnit, log[i].toUnitAbb, res);
                        listModel.append({"fromValue": log[i].fromValue, "fromUnit": log[i].fromUnit,
                                          "fromUnitAbb": log[i].fromUnitAbb, "toValue": res,
                                          "toUnit": log[i].toUnit, "toUnitAbb": log[i].toUnitAbb});
                    } else {
                        listModel.append({"fromValue": log[i].fromValue, "fromUnit": log[i].fromUnit,
                                          "fromUnitAbb": log[i].fromUnitAbb, "toValue": log[i].toValue,
                                          "toUnit": log[i].toUnit, "toUnitAbb": log[i].toUnitAbb});
                    }
                } else {
                    listModel.append({"fromValue": log[i].fromValue, "fromUnit": log[i].fromUnit,
                                     "fromUnitAbb": log[i].fromUnitAbb, "toValue": log[i].toValue,
                                    "toUnit": log[i].toUnit, "toUnitAbb": log[i].toUnitAbb});
                }
            }
        }
    }

}
