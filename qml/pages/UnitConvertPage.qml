import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.XmlListModel 2.0
import "components"
import "scripts/Unitconverter.js" as UC
import "scripts/HelperVariables.js" as HV

Page {
    id: unitpage
    width: Screen.width
    height: Screen.height

    property string unittype: ""
    property string unit_from: ""
    property string unit_to: ""
    property XmlListModel xmlListModel
    property var items: []
    property bool newrate: false
    property string activeUnitName: ""


    function calculateConversion(value, unitName) {
        var idx = HV.UNITS[unittype].indexOf(unitName);
        var results = [];
        var count, i = 0;
        count = HV.UNITS[unittype].length
        for (; i < count; ++i) {
            if (i === idx) {
                listModel.setProperty(i,"convValue", String(value).replace(".",","));
                continue;
            } else {
                var res;
                if (unittype === "NUMBERS") {
                    res = String(converter.convert2Numbers(items[idx], items[i], value));
                } else {
                    res = String(converter.convert2(items[idx], items[i], value, unittype));
                }
                res = res.replace(".",",");
                listModel.setProperty(i,"convValue", res);
                //listModel.get(i).convValue = res;
            }
        }
    }
    PageHeader {
        id: pageHeader
        title: ""
    }
    SilicaListView {
        id: listView
        anchors {
            top: pageHeader.bottom
            topMargin: Theme.paddingLarge * 6
            fill: parent
            //topMargin: pageHeader.height + fromField.height + toField.height +
            //           unitWindowBox.childrenRect.height + Theme.paddingLarge*2
        }
        clip: true
        focus: false
        model: ListModel{id: listModel}
        flickDeceleration: 500
        highlight: Rectangle {
            width: listView.width
            color: "#0066FF"
        }
        //spacing: Theme.paddingMedium
        highlightFollowsCurrentItem: false

        delegate: unitTypeDelegate

        VerticalScrollDecorator {
            flickable: listView
        }
    }

    Component {
        id: unitTypeDelegate
        BackgroundItem {
            id: bgItem
            width: ListView.view.width
            height: col.childrenRect.height
            Column {
                id: col
                spacing: Theme.paddingMedium
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }
                Label {
                    id: unit
                    width: parent.width
                    transform: Translate{x: 10}
                    text: String(unitName).toLowerCase()
                    font.pixelSize: Theme.fontSizeMedium + 5
                    // color: "#3399CC" //bgItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    color: Theme.highlightColor
                    truncationMode: TruncationMode.Fade
                }
                TextField {
                    id: inputField
                    width: parent.width
                    transform: Translate{x: -10}
                    text: convValue
                    placeholderText: Number(0.0).toPrecision(2).toString().replace(".",",")
                    font.pixelSize: Theme.fontSizeLarge
                    font.underline: true
                    font.bold: true
                    color: "white"
                    placeholderColor: "white"
                    horizontalAlignment: TextInput.AlignLeft
                    label: items[HV.UNITS[unittype].indexOf(unitName)] //unittype !== "CURRENCY" ? items[HV.UNITS[unittype].indexOf(unitName)] :
                           //unitName === "Euro" ? "EUR" : xmlListModel.get(HV.UNITS[unittype].indexOf(unitName)-1).currency
                    errorHighlight: text ? !acceptableInput : false
                    inputMethodHints: unittype !== "NUMBERS" ? Qt.ImhDigitsOnly | Qt.ImhNoPredictiveText :
                                                               Qt.ImhNoPredictiveText
                    validator: RegExpValidator{regExp: /^[0-9\+\-\,a-zA-Z]*$/}

                    EnterKey.onClicked: {
                        if (text.length === 0 || text === 0) {
                            if (unittype !== "NUMBERS") {
                                calculateConversion(0.0, unitName)
                            } else {
                                calculateConversion(0, unitName)
                            }
                        }
                        focus = false;
                    }
                    EnterKey.iconSource: "image://theme/icon-m-enter-close"

                    /*
                    Keys.onEnterPressed: {
                        if (event.key === Qt.Key_Enter) {
                            focus = false;
                        }
                    }
                    */

                    onClicked: {
                        activeUnitName = unitName;
                    }

                    onTextChanged: {
                        if (activeUnitName === unitName) {
                            if (text === "") {
                                if (unittype !== "NUMBERS") {
                                    calculateConversion(0.0, unitName)
                                } else {
                                    calculateConversion(0, unitName)
                                }
                            } else {
                                if (unittype === "NUMBERS") {
                                    calculateConversion(text, unitName)
                                } else {
                                    var value_ = Number(text.replace(",","."));
                                    if (isFinite(value_)) {
                                        calculateConversion(value_, unitName)
                                    } else {
                                        calculateConversion(0.0, unitName)
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    onStatusChanged: {
        if (status === PageStatus.Activating) {
            var i = 0, count = 0;
            if (unittype === "ACCELERATION") {
                items = ["cm/s2","ft/s2","g","m/s2","mm/s2"];
                pageHeader.title = "Acceleration";
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "ANGLE") {
                items = ["deg","grad","rad"];
                pageHeader.title = "Angle";
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "AREA") {
                pageHeader.title = "Area";
                items = ["acre", "ha", "cm2", "ft2", "in2",
                         "km2", "m2", "mi2","mm2","yd2"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "CURRENCY") {
                pageHeader.title = "Currency";
                for(;i < HV.UNITS[unittype].length ; i++) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
                items.push("EUR");
                for(var k = 0; k < xmlListModel.count ; k++) {
                    items.push(xmlListModel.get(k).currency)
                }
                    //items[i+1] = Object.getOwnPropertyNames(HV.currencies)[i];
            } else if (unittype === "DATASTORAGE") {
                pageHeader.title = "Data Storage";
                items = ["b", "B", "Gb", "GB", "kb",
                         "kB", "Mb", "MB", "word"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "DENSITY") {
                pageHeader.title = "Density";
                items = ["Al", "Cu", "Au", "g/cm3", "Fe",
                         "kg/m3", "Pb", "Ag"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "ENERGYANDWORK") {
                pageHeader.title = "Energy and Work";
                items = ["Btu", "cal", "eV", "erg", "ftlb",
                         "J", "kcal", "kJ", "kWh", "Nm"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "FLOW") {
                pageHeader.title = "Flow";
                items = ["cfm","m3/h","m3/s","L/min"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "FORCE") {
                pageHeader.title = "Force";
                items = ["dyn","kN","kip","N","ozf","lbf"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "FREQUENCY") {
                pageHeader.title = "Frequency";
                items = ["GHz","Hz","kHz","MHz","rad/s","rpm","THz"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "FUELCONSUMPTION") {
                pageHeader.title = "Fuel Consumption";
                items = ["km/L","L/100km","mpg"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "LENGTH") {
                pageHeader.title = "Length";
                items = ["A","au","cm","dm","ft","in","km",
                         "ly","m","um","mil","mi","mm","nm","nautmi","pm","yd"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "MAGNETICFIELDSTRENGTH") {
                pageHeader.title = "Magnetic Field Strength";
                items = ["A/m","Oe"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "MAGNETICFLUXDENSITY") {
                pageHeader.title = "Magnetic Flux Density";
                items = ["gamma","Gs","T"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "MASS") {
                pageHeader.title = "Mass";
                items = ["amu","gr","g","kg","ug","mg","oz","lbm","slug"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "NUMBERS") {
                pageHeader.title = "Numbers";
                //fromField.inputMethodHints = Qt.ImhNoPredictiveText
                //fromField.validator.destroy()
                items = ["bin","dec","hex","oct"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "POWER") {
                pageHeader.title = "Power";
                items = ["Btu/h","hpb","cal/s", "dBm", "dBW", "hpe",
                         "GW","kW","hp","MW","ftlb/s","TW","W"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "PRESSURE") {
                pageHeader.title = "Pressure";
                items = ["bar","dyn/cm2","ftAgua","hPa","inAgua",
                         "kPa","MPa","mbar","mmHg","Pa","psi","atm","Torr"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "SPEED") {
                pageHeader.title = "Speed";
                items = ["ft/s","km/h","knot","mach","m/s","mph"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "TEMPERATURE") {
                pageHeader.title = "Temperature";
                items = ["C","F","K","R"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "TIME") {
                pageHeader.title = "Time";
                items = ["day","hr","us","ms","min","ns","s","wk","yr"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "TORQUE") {
                pageHeader.title = "Torque";
                items = ["dyn-cm","dyn-m","gf-m","kgf-m","N-cm",
                         "N-m","ozf-in","lbf-ft","lbf-in"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            } else if (unittype === "VOLUME") {
                pageHeader.title = "Volume";
                items = ["cl","cm3","f3","in3","km3","m3",
                         "mi3","mm3","yd3","l","ml","gal","oz","qt"];
                HV.UNITS[unittype].sort();
                count = HV.UNITS[unittype].length;
                for (; i < count; ++i) {
                    listModel.append({"unitName": HV.UNITS[unittype][i],
                                      "convValue": ""});
                }
            }
        } else if (status === PageStatus.Deactivating) {
            HV.COVER_UNIT1 = HV.COVER_UNIT2 = null
        }
    }
}
