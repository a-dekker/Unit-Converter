import QtQuick 2.5
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
        var idx = HV.UNITS[unittype].indexOf(unitName)
        var results = []
        var count, i = 0
        count = HV.UNITS[unittype].length
        for (; i < count; ++i) {
            if (i === idx) {
                if (main.commaSep) {
                    listModel.setProperty(i, "convValue",
                                          String(value).replace(".", ","))
                } else {
                    listModel.setProperty(i, "convValue", String(value))
                }
                continue
            } else {
                var res
                if (unittype === "NUMBERS") {
                    res = String(converter.convert2Numbers(items[idx],
                                                           items[i], value))
                } else {
                    res = String(converter.convert2(items[idx], items[i],
                                                    value, unittype))
                }
                res = main.commaSep ? res.replace(".", ",") : res
                listModel.setProperty(i, "convValue", res)
                //listModel.get(i).convValue = res;
            }
        }
        HV.COVER_VALUE1 = listModel.get(0).convValue
        HV.COVER_VALUE2 = listModel.get(1).convValue
        if (count > 3) {
            HV.COVER_VALUE4 = listModel.get(3).convValue
        } else {
            HV.COVER_VALUE4 = ""
        }
        if (count > 2) {
            HV.COVER_VALUE3 = listModel.get(2).convValue
        } else {
            HV.COVER_VALUE3 = ""
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
        }
        clip: true
        focus: false
        model: ListModel {
            id: listModel
        }
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
                    transform: Translate {
                        x: 10
                    }
                    text: String(unitName).toLowerCase()
                    font.pixelSize: Theme.fontSizeMedium + 5
                    // color: "#3399CC" //bgItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    color: Theme.highlightColor
                    truncationMode: TruncationMode.Fade
                }
                TextField {
                    id: inputField
                    width: parent.width
                    transform: Translate {
                        x: -10
                    }
                    text: convValue
                    placeholderText: main.commaSep ? Number(0.0).toPrecision(
                                                         2).toString().replace(
                                                         ".", ",") : Number(
                                                         0.0).toPrecision(
                                                         2).toString()
                    font.pixelSize: Theme.fontSizeLarge
                    font.underline: true
                    font.bold: true
                    color: Theme.primaryColor
                    placeholderColor: Theme.primaryColor
                    horizontalAlignment: TextInput.AlignLeft
                    label: items[HV.UNITS[unittype].indexOf(
                                     unitName)] //unittype !== "CURRENCY" ? items[HV.UNITS[unittype].indexOf(unitName)] :
                    //unitName === "Euro" ? "EUR" : xmlListModel.get(HV.UNITS[unittype].indexOf(unitName)-1).currency
                    errorHighlight: text ? !acceptableInput : false
                    inputMethodHints: unittype !== "NUMBERS" ? Qt.ImhDigitsOnly | Qt.ImhNoPredictiveText : Qt.ImhNoPredictiveText
                    validator: RegExpValidator {
                        regExp: /^[0-9\+\-\,\.a-zA-Z]*$/
                    }

                    EnterKey.onClicked: {
                        if (text.length === 0 || text === 0) {
                            if (unittype !== "NUMBERS") {
                                calculateConversion(0.0, unitName)
                            } else {
                                calculateConversion(0, unitName)
                            }
                        }
                        focus = false
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
                        activeUnitName = unitName
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
                                    var value_ = main.commaSep ? Number(
                                                                     text.replace(
                                                                         ",",
                                                                         ".")) : Number(
                                                                     text)
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
            HV.COVER_UNIT1 = HV.COVER_UNIT2 = HV.COVER_UNIT3 = HV.COVER_UNIT4 = null
            HV.COVER_VALUE1 = HV.COVER_VALUE2 = HV.COVER_VALUE3 = HV.COVER_VALUE4 = "0"
            var i = 0, count = 0
            if (unittype === "ACCELERATION") {
                items = ["cm/s2", "ft/s2", "g", "m/s2", "mm/s2"]
                pageHeader.title = qsTr("Acceleration")
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "ANGLE") {
                items = ["deg", "grad", "rad"]
                pageHeader.title = qsTr("Angle")
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "AREA") {
                pageHeader.title = qsTr("Area")
                items = ["acre", "ha", "cm2", "ft2", "in2", "km2", "m2", "mi2", "mm2", "yd2"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "CURRENCY") {
                pageHeader.title = qsTr("Currency")
                items = ["AUD", "BRL", "BGN", "CAD", "CNY", "HRK", "CZK", "DKK", "EUR", "HKD", "HUF", "ISK", "INR", "IDR", "ILS", "JPY", "MYR", "MXN", "RON", "NZD", "NOK", "PHP", "PLN", "GBP", "RUB", "SGD", "ZAR", "KRW", "SEK", "CHF", "THB", "TRY", "USD"]
                HV.UNITS[unittype].sort()
                for (; i < HV.UNITS[unittype].length; i++) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "DATASTORAGE") {
                pageHeader.title = qsTr("Data Storage")
                items = ["b", "B", "Gb", "GiB", "kb", "KiB", "Mb", "MiB", "word"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "DATATRANSFER") {
                pageHeader.title = qsTr("Data Transfer")
                items = ["bits", "Bs", "kbits", "Kibits", "kBs", "KiBs", "Mbits", "Mibits", "MBs", "MiBs", "Gbits", "Gibits", "GBs", "GiBs", "Tbits", "Tibits", "TBs", "TiBs"]
                // HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "DENSITY") {
                pageHeader.title = qsTr("Density")
                items = ["Al", "Cu", "Au", "g/cm3", "Fe", "kg/m3", "Pb", "Ag"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "ENERGYANDWORK") {
                pageHeader.title = qsTr("Energy and Work")
                items = ["Btu", "cal", "eV", "erg", "ftlb", "J", "kcal", "kJ", "kWh", "Nm"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "FLOW") {
                pageHeader.title = qsTr("Flow")
                items = ["cfm", "m3/h", "m3/s", "L/min"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "FORCE") {
                pageHeader.title = qsTr("Force")
                items = ["dyn", "kN", "kip", "N", "ozf", "lbf"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "FREQUENCY") {
                pageHeader.title = qsTr("Frequency")
                items = ["GHz", "Hz", "kHz", "MHz", "rad/s", "rpm", "THz"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "FUELCONSUMPTION") {
                pageHeader.title = qsTr("Fuel Consumption")
                items = ["km/L", "L/100km", "impg", "mpg"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "LENGTH") {
                pageHeader.title = qsTr("Length")
                items = ["A", "au", "cm", "dm", "ft", "in", "km", "ly", "m", "um", "mil", "mi", "mm", "nm", "nautmi", "pm", "yd"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "MAGNETICFIELDSTRENGTH") {
                pageHeader.title = qsTr("Magnetic Field Strength")
                items = ["A/m", "Oe"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "MAGNETICFLUXDENSITY") {
                pageHeader.title = qsTr("Magnetic Flux Density")
                items = ["gamma", "Gs", "T"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "MASS") {
                pageHeader.title = qsTr("Mass")
                items = ["amu", "gr", "g", "kg", "ug", "mg", "oz", "lbm", "slug"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "NUMBERS") {
                pageHeader.title = qsTr("Numbers")
                //fromField.inputMethodHints = Qt.ImhNoPredictiveText
                //fromField.validator.destroy()
                items = ["bin", "dec", "hex", "oct"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "POWER") {
                pageHeader.title = qsTr("Power")
                items = ["hpb", "Btu/h", "cal/s", "dBm", "dBW", "hpe", "GW", "kW", "hp", "MW", "ftlb/s", "TW", "W"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "PRESSURE") {
                pageHeader.title = qsTr("Pressure")
                items = ["bar", "dyn/cm2", "ftAgua", "hPa", "inAgua", "kPa", "MPa", "mbar", "mmHg", "Pa", "psi", "atm", "Torr"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "SPEED") {
                pageHeader.title = qsTr("Speed")
                items = ["ft/s", "km/h", "knot", "mach", "m/s", "mph"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "TEMPERATURE") {
                pageHeader.title = qsTr("Temperature")
                items = ["C", "F", "K", "R"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "TIME") {
                pageHeader.title = qsTr("Time")
                items = ["day", "hr", "us", "ms", "min", "ns", "s", "wk", "yr"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "TORQUE") {
                pageHeader.title = qsTr("Torque")
                items = ["dyn-cm", "dyn-m", "gf-m", "kgf-m", "N-cm", "N-m", "ozf-in", "lbf-ft", "lbf-in"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            } else if (unittype === "VOLUME") {
                pageHeader.title = qsTr("Volume")
                items = ["cl", "cm3", "f3", "in3", "km3", "m3", "mi3", "mm3", "yd3", "l", "ml", "galuk", "ipt", "gal", "oz", "qt", "upt"]
                HV.UNITS[unittype].sort()
                count = HV.UNITS[unittype].length
                for (; i < count; ++i) {
                    listModel.append({
                                         "unitName": HV.UNITS[unittype][i],
                                         "convValue": ""
                                     })
                }
            }
            HV.COVER_UNIT1 = HV.UNITS[unittype][0]
            HV.COVER_UNIT2 = HV.UNITS[unittype][1]
            HV.UNITTYPE = pageHeader.title
            if (count > 3) {
                HV.COVER_UNIT4 = HV.UNITS[unittype][3]
            } else {
                if (HV.UNITTYPE === "Currency") {
                    HV.COVER_UNIT4 = HV.UNITS[unittype][3]
                } else {
                    HV.COVER_UNIT4 = ""
                }
            }
            if (count > 2) {
                HV.COVER_UNIT3 = HV.UNITS[unittype][2]
            } else {
                if (HV.UNITTYPE === "Currency") {
                    HV.COVER_UNIT3 = HV.UNITS[unittype][2]
                } else {
                    HV.COVER_UNIT3 = ""
                }
            }
        } else if (status === PageStatus.Deactivating) {
            HV.COVER_UNIT1 = HV.COVER_UNIT2 = HV.COVER_UNIT3 = HV.COVER_UNIT4 = null
            HV.COVER_VALUE1 = HV.COVER_VALUE2 = HV.COVER_VALUE3 = HV.COVER_VALUE4 = "0"
        }
    }
}
