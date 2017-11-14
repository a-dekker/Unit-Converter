import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.XmlListModel 2.0
import "scripts/UnitConververDB.js" as DB
import "scripts/HelperVariables.js" as HV

/**
 * @brief Dialog for
 */
Dialog {
    id: favouriteDialog
    width: Screen.width
    height: Screen.height

    property string unittype: ""
    property var items: []
    property var keys: []
    property XmlListModel xmlListModel
    property string unitTypeFrom: ""
    property string unitTypeFromAbb: ""
    property string unitValueFrom: ""
    property string unitTypeTo: ""
    property string unitTypeToAbb: ""
    property string unitValueTo: ""
    property string unittype_old: ""
    property bool isUpdate: false

    //acceptDestinationAction: PageStackAction.Replace
    //acceptDestination: Qt.resolvedUrl("ImagePage.qml")
    //acceptDestinationProperties: {"path": path, "isScannedImage": true}

    function calculateConversion(value) {
        if (items[combo2.currentIndex] === items[combo3.currentIndex]) {
            return value;
        }
        var res;
        if (unittype === "NUMBERS") {
            res = String(converter.convert2Numbers(items[combo2.currentIndex],
                                                   items[combo3.currentIndex], value));
        } else {
            res = String(converter.convert2(items[combo2.currentIndex],
                                            items[combo3.currentIndex], value, unittype));
        }
        return res;
    }

    function populateModels() {
        fromUnitModel.clear();
        toUnitModel.clear();
        var i = 0, count = 0;
        if (unittype === "ACCELERATION") {
            items = ["cm/s2","ft/s2","g","m/s2","mm/s2"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "ANGLE") {
            items = ["deg","grad","rad"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "AREA") {
            items = ["acre", "ha", "cm2", "ft2", "in2",
                     "km2", "m2", "mi2","mm2","yd2"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "CURRENCY") {
            for(;i < HV.UNITS[unittype].length ; i++) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
            items.push("EUR");
            for(var k = 0; k < xmlListModel.count ; k++) {
                items.push(xmlListModel.get(k).currency)
            }
                //items[i+1] = Object.getOwnPropertyNames(HV.currencies)[i];
        } else if (unittype === "DATASTORAGE") {
            items = ["b", "B", "Gb", "GB", "kb",
                     "kB", "Mb", "MB", "word"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "DENSITY") {
            items = ["Al", "Cu", "Au", "g/cm3", "Fe",
                     "kg/m3", "Pb", "Ag"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "ENERGYANDWORK") {
            items = ["Btu", "cal", "eV", "erg", "ftlb",
                     "J", "kcal", "kJ", "kWh", "Nm"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "FLOW") {
            items = ["cfm","m3/h","m3/s","L/min"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "FORCE") {
            items = ["dyn","kN","kip","N","ozf","lbf"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "FREQUENCY") {
            items = ["GHz","Hz","kHz","MHz","rad/s","rpm","THz"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "FUELCONSUMPTION") {
            items = ["km/L","L/100km","mpg"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "LENGTH") {
            items = ["A","au","cm","dm","ft","in","km",
                     "ly","m","um","mil","mi","mm","nm","nautmi","pm","yd"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "MAGNETICFIELDSTRENGTH") {
            items = ["A/m","Oe"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "MAGNETICFLUXDENSITY") {
            items = ["gamma","Gs","T"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "MASS") {
            items = ["amu","gr","g","kg","ug","mg","oz","lbm","slug"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "NUMBERS") {
            items = ["bin","dec","hex","oct"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "POWER") {
            items = ["Btu/h","hpb","cal/s", "dBm", "dBW", "hpe",
                     "GW","kW","hp","MW","ftlb/s","TW","W"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "PRESSURE") {
            items = ["bar","dyn/cm2","ftAgua","hPa","inAgua",
                     "kPa","MPa","mbar","mmHg","Pa","psi","atm","Torr"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "SPEED") {
            items = ["ft/s","km/h","knot","mach","m/s","mph"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "TEMPERATURE") {
            items = ["C","F","K","R"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "TIME") {
            items = ["day","hr","us","ms","min","ns","s","wk","yr"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "TORQUE") {
            items = ["dyn-cm","dyn-m","gf-m","kgf-m","N-cm",
                     "N-m","ozf-in","lbf-ft","lbf-in"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        } else if (unittype === "VOLUME") {
            items = ["cl","cm3","f3","in3","km3","m3",
                     "mi3","mm3","yd3","l","ml","gal","oz","qt"];
            HV.UNITS[unittype].sort();
            count = HV.UNITS[unittype].length;
            for (; i < count; ++i) {
                fromUnitModel.append({"name": HV.UNITS[unittype][i]});
                toUnitModel.append({"name": HV.UNITS[unittype][i]});
            }
        }
    }

    SilicaFlickable {
        id: view
        anchors.fill: parent
        focus: true

        DialogHeader {
            id: dialogHeader
            width: parent.width
        }

        ComboBox {
            id: combo1
            width: parent.width
            label: "Unit converters"

            anchors {
                top: dialogHeader.bottom
                topMargin: Theme.paddingLarge * 2
            }

            menu: ContextMenu {
                Repeater {
                     id: rep1
                     model: ListModel { id: unitConverterModel }
                     MenuItem { text: model.name }
                }
            }
            Component.onCompleted: {
                var i = 0;
                keys = Object.keys(HV.UNITS);
                keys.sort();
                var count = Object.keys(HV.UNITS).length;
                for(;i < count; i++) {
                    unitConverterModel.append({name: keys[i]});
                }
            }

            onCurrentIndexChanged: {
                if (currentIndex !== -1) {
                    try {
                        unittype = currentItem.text;
                        populateModels();
                    } catch (err) {
                        console.log(err);
                    }
                }
            }
        }

        Column {
            id: col1
            width: parent.width
            spacing: Theme.paddingMedium
            anchors {
                top: combo1.bottom
                topMargin: Theme.paddingLarge * 2
                horizontalCenter: parent.horizontalCenter
            }
            ComboBox {
                id: combo2
                width: parent.width
                label: "Select from "

                menu: ContextMenu {
                    id: conMenu2
                    Repeater {
                         id: rep2
                         model: ListModel { id: fromUnitModel }
                         MenuItem { text: String(model.name).toLowerCase() }
                    }
                }
                onCurrentIndexChanged: {
                    var text = fromField.text;
                    if (text === "") {
                        toField.text = calculateConversion(0.0)
                    } else {
                        var value_ = Number(text);
                        if (isFinite(value_)) {
                            toField.text = calculateConversion(value_)
                        } else {
                            toField.text = calculateConversion(0.0)
                        }
                    }
                }
            }
            TextField {
                 id: fromField
                 focus: true
                 width: parent.width
                 text: ""
                 placeholderText: qsTr("Give a value...")
                 font.pixelSize: Theme.fontSizeLarge
                 font.underline: true
                 font.bold: true
                 color: "white"
                 placeholderColor: "white"
                 horizontalAlignment: TextInput.AlignLeft
                 label: "Value from"
                 validator: RegExpValidator{regExp: /^[0-9\+\-\,a-zA-Z]*$/}
                 errorHighlight: text ? !acceptableInput : false
                 inputMethodHints: unittype !== "NUMBERS" ? Qt.ImhDigitsOnly | Qt.ImhNoPredictiveText :
                                                            Qt.ImhNoPredictiveText

                 EnterKey.onClicked: {
                     if (text.length === 0 || text === 0) {
                         if (unittype !== "NUMBERS") {
                            calculateConversion(0.0)
                         } else {
                            calculateConversion(0)
                         }
                     }
                     focus = false;
                 }
                 EnterKey.iconSource: "image://theme/icon-m-enter-close"

                 onTextChanged: {
                     if (text === "") {
                         if (unittype !== "NUMBERS") {
                             toField.text = calculateConversion(0.0)
                         } else {
                             toField.text = calculateConversion(0)
                         }
                     } else {
                         if (unittype === "NUMBERS") {
                             toField.text = calculateConversion(text)
                         } else {
                             var value_ = Number(text);
                             if (isFinite(value_)) {
                                 toField.text = calculateConversion(value_)
                             } else {
                                 toField.text = calculateConversion(0.0)
                             }
                         }
                     }
                 }
            }
        }
        Column {
            id: col2
            spacing: Theme.paddingMedium
            width: parent.width
            anchors {
                top: col1.bottom
                topMargin: Theme.paddingLarge * 2
                horizontalCenter: parent.horizontalCenter
            }
            ComboBox {
                id: combo3
                width: parent.width
                label: "Select to "

                menu: ContextMenu {
                    Repeater {
                         id: rep3
                         model: ListModel { id: toUnitModel }
                         MenuItem { text: String(model.name).toLowerCase() }
                    }
                }
                onCurrentIndexChanged: {
                    var text = fromField.text;
                    if (text === "") {
                        if (unittype !== "NUMBERS") {
                            toField.text = calculateConversion(0.0)
                        } else {
                            toField.text = calculateConversion(0)
                        }
                    } else {
                        if (unittype === "NUMBERS") {
                            toField.text = calculateConversion(text)
                        } else {
                            var value_ = Number(text);
                            if (isFinite(value_)) {
                                toField.text = calculateConversion(value_)
                            } else {
                                toField.text = calculateConversion(0.0)
                            }
                        }
                    }
                }
            }
            TextField {
                 id: toField
                 focus: true
                 width: parent.width
                 placeholderText: Number(0.0).toPrecision(2).toString()
                 font.pixelSize: Theme.fontSizeLarge
                 font.underline: true
                 font.bold: true
                 color: "white"
                 placeholderColor: "white"
                 horizontalAlignment: TextInput.AlignLeft
                 label: "Value to"
                 validator: DoubleValidator{}
                 errorHighlight: text ? !acceptableInput : false
                 inputMethodHints: Qt.ImhDigitsOnly | Qt.ImhNoPredictiveText
                 readOnly: true
                 EnterKey.onClicked: {
                     if (text.length === 0 || text === 0) {
                         if (unittype !== "NUMBERS") {
                             text = calculateConversion(0.0)
                         } else {
                             text = calculateConversion(0)
                         }
                     }
                     focus = false;
                 }
                 EnterKey.iconSource: "image://theme/icon-m-enter-close"
            }
        }
    }

    states: [
        State {
            when: combo1.currentIndex !== -1
            PropertyChanges {
                target: col1; enabled: true; opacity: 1
            }
            PropertyChanges {
                target: col2; enabled: true; opacity: 1
            }
        },
        State {
            when: combo1.currentIndex === -1
            PropertyChanges {
                target: col1; enabled: false; opacity: 0.25
            }
            PropertyChanges {
                target: col2; enabled: false; opacity: 0.25
            }
        }
    ]

    onOpened: {
        if (unittype !== "" && unitConverterModel.count > 0) {
            populateModels(unittype);
            combo1.currentIndex = keys.indexOf(unittype);
            combo1.currentItem = rep1.itemAt(keys.indexOf(unittype));
            combo2.currentIndex = items.indexOf(unitTypeFromAbb);
            combo2.currentItem = rep2.itemAt(items.indexOf(unitTypeFromAbb));
            fromField.text = unitValueFrom;
            combo3.currentIndex = items.indexOf(unitTypeToAbb);
            combo3.currentItem = rep3.itemAt(items.indexOf(unitTypeToAbb));
            toField.text = unitValueTo;
            unittype_old = unittype;
        } else {
            combo1.currentIndex = -1;
        }
    }

    onAccepted: {
        if (unittype !== "") {
            if (isUpdate) {
                DB.updateFavourite(unittype_old,unitTypeFrom,unitValueFrom,unitTypeTo,unitValueTo,
                                   unittype, combo2.currentItem.text, items[combo2.currentIndex], fromField.text,
                                   combo3.currentItem.text, items[combo3.currentIndex], toField.text);
            } else {
                DB.addFavourite(unittype, combo2.currentItem.text, items[combo2.currentIndex], fromField.text,
                            combo3.currentItem.text, items[combo3.currentIndex], toField.text);
            }
        }
    }
    onRejected: {

    }
}
