import QtQuick 2.5
import Sailfish.Silica 1.0
import QtQuick.XmlListModel 2.0
import "components"
import "scripts/Unitconverter.js" as UC
import "scripts/HelperVariables.js" as HV

Page {
    id: frontpage
    width: Screen.width
    height: Screen.height

    property string unittype: ""
    property string url: "http://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml"
    property bool largeScreen: screen.width > 540

    SilicaListView {
        id: listView
        anchors.fill: parent
        clip: true
        focus: false
        model: ListModel {
            id: listModel
        }
        header: PageHeader {
            id: pageheader
            title: qsTr("Unit Converter")
        }
        flickDeceleration: 500
        highlight: Rectangle {
            width: listView.width
            color: "#0066FF"
        }
        highlightFollowsCurrentItem: false

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
            MenuItem {
                text: qsTr("Options")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("OptionsPage.qml"))
                }
            }
            MenuItem {
                text: qsTr("Quick Search")
                onClicked: {
                    if (!proxymodel.isModelPopulated()) {
                        var i = 1, len = xmlModel.count, tmp = {
                            "Euro": "EUR"
                        }
                        for (i; i <= len; ++i) {
                            tmp[HV.UNITS["CURRENCY"][i]] = proxymodel.stripHTMLtags(
                                        xmlModel.get(i - 1).currency)
                        }
                        proxymodel.insertUnits("currency", tmp)
                    }
                    pageStack.push(Qt.resolvedUrl("QuickSearchPage.qml"))
                }
            }
            MenuItem {
                text: qsTr("Favourites")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("FavouritesPage.qml"), {
                                       "xmlListModel": xmlModel
                                   })
                }
            }
            MenuItem {
                text: qsTr("Ruler")
                onClicked: pageStack.push(Qt.resolvedUrl("RulerPage.qml"))
            }
        }

        XmlListModel {
            id: xmlModel
            xml: currencycache.xml
            namespaceDeclarations: "declare namespace gesmes='http://www.gesmes.org/xml/2002-08-01';" + "declare default element namespace 'http://www.ecb.int/vocabulary/2002-08-01/eurofxref';"
            query: "/gesmes:Envelope/Cube/Cube/Cube"
            XmlRole {
                name: "currency"
                query: "@currency/string()"
            }
            XmlRole {
                name: "rate"
                query: "@rate/string()"
            }
            onStatusChanged: {
                if (status == XmlListModel.Ready) {
                    console.log("Upload succeeded...")
                    var items = {

                    }
                    var i = 0
                    for (; i < count; i++) {
                        items[get(i).currency] = get(i).rate
                    }

                    if (HV.UNITS["CURRENCY"].length - 1 !== Object.getOwnPropertyNames(
                                items).length) {
                        console.log("Currencies has been changed and does not match the currency table...")
                    }
                    converter.getCurrencies(items)
                    proxymodel.updateCurrencies(items)
                } else if (status == XmlListModel.Loading) {
                    console.log("Loading...")
                } else if (status == XmlListModel.Error) {
                    console.log("Error occured: " + errorString())
                }
            }
        }

        delegate: unitDelegate

        VerticalScrollDecorator {
            flickable: listView
        }
    }

    Component {
        id: unitDelegate
        BackgroundItem {
            id: bgItem
            width: listView.width
            height: Theme.itemSizeLarge
            Row {
                id: row
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    verticalCenter: parent.verticalCenter
                }

                spacing: Theme.paddingLarge
                Image {
                    id: img
                    //anchors.verticalCenter: label.verticalCenter
                    source: imageSource
                    scale: largeScreen ? 2 : 1.25
                    smooth: true
                }
                Label {
                    id: unit
                    anchors.verticalCenter: img.verticalCenter
                    text: unitName
                    font.pixelSize: Theme.fontSizeLarge
                    color: bgItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                }
            }
            Image {
                id: arrowIcon
                source: "image://theme/icon-m-right"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: Theme.paddingLarge
            }
            onClicked: {
                pageStack.push(Qt.resolvedUrl("UnitConvertPage.qml"), {
                                   "unittype": unitName.replace(
                                                   /\s/g, "").toUpperCase(),
                                   "xmlListModel": xmlModel
                               })
            }
        }
    }
    onStatusChanged: {
        if (status === PageStatus.Activating) {
            if (listView.model.count !== 0) {
                return
            } else {
                var unitNames = ["Acceleration", "Angle", "Area", "Currency", "Data Storage", "Data Transfer", "Density", "Energy and Work", "Flow", "Force", "Frequency", "Fuel Consumption", "Length", "Magnetic Field Strength", "Magnetic Flux Density", "Mass", "Numbers", "Power", "Pressure", "Speed", "Temperature", "Time", "Torque", "Volume"]
                unitNames.sort()
                var i = 0, count = unitNames.length
                for (; i < count; ++i) {
                    listView.model.append({
                                              "imageSource": "qrc:/images/images/unit_icon_"
                                                             + (i + 1) + ".png",
                                              "unitName": unitNames[i]
                                          })
                }
            }
        }
    }
}
