import QtQuick 2.5
import Sailfish.Silica 1.0
import "scripts/HelperVariables.js" as HV
import "components"

Page {
    id: quickpage
    width: Screen.width
    height: Screen.height

    property Item _currentItem: null
    property string searchString: ""
    property string unit_1: ""
    property string unit_2: ""

    Resultpanel {
        id: resultpanel
        anchors.centerIn: parent
        unit1_text: ""
        unit2_text: ""
        unit1_value: ""
        unit2_value: ""
    }

    SilicaListView {
        id: listView

        PullDownMenu {
            MenuItem {
                text: qsTr("Help")
                onClicked: pageStack.push(Qt.resolvedUrl("QuickSearchHelp.qml"))
            }
        }
        PushUpMenu {
            MenuItem {
                text: qsTr("Scroll to top")
                onClicked: {
                    listView.scrollToTop()
                }
            }
        }
        width: parent.width
        anchors {
            fill: parent
        }
        model: proxymodel
        clip: true
        focus: true
        snapMode: ListView.SnapToItem
        flickDeceleration: 500
        highlight: Rectangle {
            width: listView.width
            color: "#0066FF"
        }
        spacing: Theme.paddingLarge
        header: SearchField {
            width: quickpage.width * 0.95
            placeholderText: qsTr("Search")
            text: ""
            focus: true
            clip: true
            validator: RegExpValidator {
                regExp: /^[A-Za-z\s]+$/
            }
            inputMethodHints: Qt.ImhLatinOnly | Qt.ImhNoPredictiveText
            errorHighlight: text ? !acceptableInput : false
            onTextChanged: {
                if (unit_1 !== "" && unit_2 !== "") {
                    unit_1 = ""
                    unit_2 = ""
                    resultpanel.visible = false
                }
                searchString = text
                if (["angle", "area", "curr", "data", "dens", "ener", "flow", "force", "freq", "fuel", "leng", "magnetic fi", "magnetic fl", "mass", "numb", "power", "pres", "speed", "temp", "time", "torq", "trans", "vol"].indexOf(
                            searchString.toLowerCase()) !== -1) {
                    if (searchString.toLowerCase() === "ener") {
                        searchString = "energy and work"
                    } else if (searchString.toLowerCase() === "freq") {
                        searchString = "frequency"
                    } else if (searchString.toLowerCase() === "temp") {
                        searchString = "temperature"
                    } else if (searchString.toLowerCase() === "vol") {
                        searchString = "volume"
                    } else if (searchString.toLowerCase() === "curr") {
                        searchString = "currency"
                    } else if (searchString.toLowerCase() === "leng") {
                        searchString = "length"
                    } else if (searchString.toLowerCase() === "pres") {
                        searchString = "pressure"
                    } else if (searchString.toLowerCase() === "numb") {
                        searchString = "numbers"
                    } else if (searchString.toLowerCase() === "data") {
                        searchString = "data storage"
                    } else if (searchString.toLowerCase() === "trans") {
                        searchString = "data tranfer"
                    } else if (searchString.toLowerCase() === "dens") {
                        searchString = "density"
                    } else if (searchString.toLowerCase() === "fuel") {
                        searchString = "fuel consumption"
                    } else if (searchString.toLowerCase() === "magnetic fi") {
                        searchString = "magnetic field strength"
                    } else if (searchString.toLowerCase() === "magnetic fl") {
                        searchString = "magnetic flux density"
                    } else if (searchString.toLowerCase() === "torq") {
                        searchString = "torque"
                    }

                    proxymodel.setFilterWildcard("")
                    proxymodel.filterModel(searchString)
                    searchString = ""
                } else {
                    if (searchString) {
                        proxymodel.setFilterWildcard(searchString)
                    } else {
                        proxymodel.setupModel()
                        proxymodel.setFilterWildcard("#null#")
                        focus = true
                    }
                }
            }
            EnterKey.iconSource: "image://theme/icon-m-enter-close"
            EnterKey.onClicked: focus = false
        }
        delegate: quickSearchDelegate

        onCurrentIndexChanged: {
            _currentItem = currentItem
        }

        currentIndex: -1

        VerticalScrollDecorator {
            flickable: listView
        }
    }

    Component {
        id: quickSearchDelegate
        BackgroundItem {
            id: item
            width: listView.width
            height: Theme.itemSizeSmall
            Text {
                id: textItem
                width: parent.width
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    verticalCenter: parent.verticalCenter
                }
                font.pixelSize: Theme.fontSizeLarge
                text: String(Theme.highlightText(
                                 display, searchString,
                                 Theme.highlightColor)).toLowerCase()
                color: item.highlighted ? Theme.highlightColor : Theme.primaryColor
            }

            onClicked: {
                if (unit_1 !== "" && unit_2 !== "") {
                    unit_1 = ""
                    unit_2 = ""
                    resultpanel.visible = false
                    return
                }
                if (unit_1 === "") {
                    unit_1 = display
                    return
                } else if (unit_2 === "") {
                    unit_2 = display
                    var res = proxymodel.doCalculation(unit_1, unit_2)
                    if (Number(res) > -1e30) {
                        if (res.indexOf(".") !== -1) {
                            res = parseFloat(res)
                            if (res > -1 && res < 1) {
                                res = res.toPrecision(6)
                            } else if (res > -1000 && res < 1000) {
                                res = res.toFixed(2)
                            } else {
                                res = res.toFixed(0)
                            }
                        }
                        resultpanel.unit1_text = unit_1
                        HV.COVER_UNIT1 = unit_1
                        resultpanel.unit2_text = unit_2
                        HV.COVER_UNIT2 = unit_2
                        HV.COVER_VALUE1 = "1"
                        resultpanel.unit1_value = "1"
                        HV.COVER_VALUE2 = res
                        resultpanel.unit2_value = res
                        resultpanel.visible = true
                    }
                    return
                }
            }
        }
    }

    states: [
        State {
            name: "panel visible"
            when: resultpanel.visible
            PropertyChanges {
                target: listView
                opacity: 0.25
            }
        },
        State {
            name: "panel not visible"
            when: !resultpanel.visible
            PropertyChanges {
                target: listView
                opacity: 1.0
            }
        }
    ]

    onStatusChanged: {
        if (status === PageStatus.Activating) {
            if (!proxymodel.isModelPopulated()) {
                proxymodel.insertUnits("angle", {
                                           "degrees": "deg",
                                           "gradian": "grad",
                                           "radians": "rad"
                                       })
                proxymodel.insertUnits("area", {
                                           "acres": "acre",
                                           "hectares": "ha",
                                           "square centimeters": "cm2",
                                           "square feet": "ft2",
                                           "square inches": "in2",
                                           "square kilometers": "km2",
                                           "square meters": "m2",
                                           "square miles": "mi2",
                                           "square millimeters": "mm2",
                                           "square yards": "yd2"
                                       })
                proxymodel.insertUnits("data storage", {
                                           "bit": "b",
                                           "byte": "B",
                                           "kibibit": "kb",
                                           "kibibyte": "KiB",
                                           "mebibit": "Mb",
                                           "mebibyte": "MiB",
                                           "gibibit": "Gb",
                                           "gibibyte": "GiB",
                                           "word": "word"
                                       })
                proxymodel.insertUnits("data transfer", {
                                           "bit/s": "bits",
                                           "B/s": "Bs",
                                           "kbit/s": "kbits",
                                           "Kibit/s": "Kibits",
                                           "kB/s": "kBs",
                                           "KiB/s": "KiBs",
                                           "Mbit/s": "Mbits",
                                           "Mibit/s": "Mibits",
                                           "MB/s": "MBs",
                                           "MiB/s": "MiBs",
                                           "Gbit/s": "Gbits",
                                           "Gibit/s": "Gibits",
                                           "GB/s": "GBs",
                                           "GiB/s": "GiBs",
                                           "Tbit/s": "Tbits",
                                           "Tibit/s": "Tibits",
                                           "TB/s": "TBs",
                                           "TiB/s": "TiBs"
                                       })
                proxymodel.insertUnits("density", {
                                           "aluminum": "Al",
                                           "copper": "Cu",
                                           "gold": "Au",
                                           "gram per cubic centimeter": "g/cm3",
                                           "iron": "Fe",
                                           "kilogram per cubic metre": "kg/m3",
                                           "lead": "Pb",
                                           "silver": "Ag"
                                       })
                proxymodel.insertUnits("energy and work", {
                                           "British thermal units": "Btu",
                                           "calories": "cal",
                                           "electron volts": "eV",
                                           "ergs": "erg",
                                           "foot-pounds": "ftlb",
                                           "joules": "J",
                                           "kilocalories": "kcal",
                                           "kilojoules": "kJ",
                                           "kilowatt-hours": "kWh",
                                           "newton-meters": "Nm"
                                       })
                proxymodel.insertUnits("flow", {
                                           "cubic foot per minute": "cfm",
                                           "cubic meter per hour": "m3/h",
                                           "cubic meter per second": "m3/s",
                                           "litres per minute": "L/min"
                                       })
                proxymodel.insertUnits("force", {
                                           "dynes": "dyn",
                                           "kilopounds": "kip",
                                           "kilonewtons": "kN",
                                           "pounds": "lbf",
                                           "newtons": "N",
                                           "ounces-force": "ozf"
                                       })
                proxymodel.insertUnits("frequency", {
                                           "gigahertz": "GHz",
                                           "hertz": "Hz",
                                           "kilohertz": "kHz",
                                           "megahertz": "MHz",
                                           "radians per second": "rad/s",
                                           "revolutions per minute": "rpm",
                                           "terahertz": "THz"
                                       })
                proxymodel.insertUnits("fuel consumption", {
                                           "kilometers per liter": "km/L",
                                           "litres per 100 km": "L/100km",
                                           "miles per gallon (UK)": "impg",
                                           "miles per gallon (US)": "mpg"
                                       })
                proxymodel.insertUnits("length", {
                                           "angstroms": "A",
                                           "astronomical units": "au",
                                           "centimeters": "cm",
                                           "decimeters": "dm",
                                           "feet": "ft",
                                           "inches": "in",
                                           "kilometers": "km",
                                           "light years": "ly",
                                           "meters": "m",
                                           "micrometers or microns": "um",
                                           "miles": "mi",
                                           "millimeters": "mm",
                                           "mil or thou": "mil",
                                           "nautical miles": "nautmi",
                                           "nanometers": "nm",
                                           "picometers": "pm",
                                           "yards": "yd"
                                       })
                proxymodel.insertUnits("magnetic field strength", {
                                           "ampere per meter": "A/m",
                                           "oersted": "Oe"
                                       })
                proxymodel.insertUnits("magnetic flux density", {
                                           "gamma": "gamma",
                                           "gauss": "Gs",
                                           "tesla": "T"
                                       })
                proxymodel.insertUnits("mass", {
                                           "atomic mass units": "amu",
                                           "grams": "g",
                                           "grains": "gr",
                                           "kilograms": "kg",
                                           "pounds-mass": "lbm",
                                           "microgram": "ug",
                                           "milligrams": "mg",
                                           "ounce": "oz",
                                           "slugs": "slug"
                                       })
                proxymodel.insertUnits("numbers", {
                                           "binary": "bin",
                                           "decimal": "dec",
                                           "hexadecimal": "hex",
                                           "octal": "oct"
                                       })
                proxymodel.insertUnits("power", {
                                           "boiler horsepower": "hpb",
                                           "British thermal units per hour": "Btu/h",
                                           "calorie per second": "cal/s",
                                           "decibel milliwatts": "dBm",
                                           "decibel watts": "dBW",
                                           "electrical horsepower": "hpe",
                                           "pound-foot per second": "ftlb/2",
                                           "gigawatts": "GW",
                                           "kilowatts": "kW",
                                           "mechanical horsepower": "hp",
                                           "megawatts": "MW",
                                           "terawatts": "TW",
                                           "watts": "W"
                                       })
                proxymodel.insertUnits("pressure", {
                                           "standard atmospheres": "atm",
                                           "bar": "bar",
                                           "dynes per square centimeter": "dyn/cm2",
                                           "feet of water column at 4°C": "ftAgua",
                                           "hectopascals": "hPa",
                                           "inches of water column at 4°C": "inAgua",
                                           "megapascals": "MPA",
                                           "kilopascals": "kPa",
                                           "millibar": "mbar",
                                           "millimeters of mercury at 0°C": "mmHg",
                                           "pascals(newton per meter)": "Pa",
                                           "pounds per square inch": "psi",
                                           "torr": "Torr"
                                       })
                proxymodel.insertUnits("speed", {
                                           "feet per second": "ft/s",
                                           "kilometers per hour": "km/h",
                                           "knots": "knot",
                                           "mach number at STP": "mach",
                                           "miles per hour": "mph",
                                           "meters per second": "m/s"
                                       })
                proxymodel.insertUnits("temperature", {
                                           "celsius": "C",
                                           "fahrenheit": "F",
                                           "kelvin": "K",
                                           "rankine": "R"
                                       })
                proxymodel.insertUnits("time", {
                                           "days": "day",
                                           "hours": "hr",
                                           "microseconds": "us",
                                           "minutes": "min",
                                           "milliseconds": "ms",
                                           "nanoseconds": "ns",
                                           "seconds": "s",
                                           "years": "yr",
                                           "weeks": "wk"
                                       })
                proxymodel.insertUnits("torque", {
                                           "dyne centimeter": "dyn-cm",
                                           "dyne meter": "dyn-m",
                                           "gram-force meter": "gf-m",
                                           "kilogram-force meter": "kgf-m",
                                           "newton centimeter": "N-cm",
                                           "newton meter": "N-m",
                                           "ounce-force inch": "ozf-in",
                                           "pound-force foot": "lbf-ft",
                                           "pound-force inch": "lbf-in"
                                       })
                proxymodel.insertUnits("volume", {
                                           "centiliters": "cl",
                                           "cubic centimeters": "cm3",
                                           "cubic feet": "f3",
                                           "cubic inches": "in3",
                                           "cubic kilometers": "km3",
                                           "cubic meters": "m3",
                                           "cubic miles": "mi3",
                                           "cubic millimeters": "mm3",
                                           "cubic yards": "yd3",
                                           "liters": "l",
                                           "milliliters": "ml",
                                           "UK liquid gallons": "galuk",
                                           "US liquid gallons": "gal",
                                           "US liquid ounces": "oz",
                                           "US liquid quarts": "qt"
                                       })
                proxymodel.setupModel()
            }
            proxymodel.setFilterWildcard("#null#")
        } else if (status === PageStatus.Deactivating) {
            HV.COVER_UNIT1 = HV.COVER_UNIT2 = null
        }
    }
}
