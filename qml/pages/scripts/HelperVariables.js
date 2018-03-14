.pragma library

var UNITTYPE = null;;
var COVER_UNIT1 = null;
var COVER_UNIT2 = null;
var COVER_UNIT3 = null;
var COVER_UNIT4 = null;
var COVER_VALUE1 = "0";
var COVER_VALUE2 = "0";
var COVER_VALUE3 = "0";
var COVER_VALUE4 = "0";
var CURRENTRATE = null;
var NEWCURRENCYRATE = null;
var VERSION = "";
var HORIZONTALLINESACTIVE = true;
var VERTICALLINESACTIVE = true;

var UNITS = {
    ACCELERATION: ["Centimeter per Second Squared",
        "Foot per Second Squared",
        "Free Fall", "Metre per Second Squared",
        "Millimeter per Second Squared"
    ],
    ANGLE: ["Degrees", "Radians", "Gradian"],
    AREA: ["Acres", "Hectares", "Square Centimeters", "Square Feet",
        "Square Inches", "Square Kilometers", "Square Meters",
        "Square Miles", "Square Millimeters", "Square Yards"
    ],
    CURRENCY: ["Euro", "US Dollar", "Japanese Yen", "Bulgarian Lev",
        "Czech Koruna", "Danish Krone", "Pound Sterling",
        "Hungarian Forint","Polish Zloty", "New Romanian Leu",
        "Swedish Krona", "Swiss Franc", "Icelandic Krona",
        "Norwegian Krone", "Croatian Kuna", "Russian Rouble",
        "Turkish Lira", "Australian Dollar", "Brasilian Real",
        "Canadian Dollar", "Chinese Yuan Renminbi", "Hong Kong Dollar",
        "Indonesian Rupiah", "Israeli Shekel", "Indian Rupee",
        "South Korean Won", "Mexican Peso", "Malaysian Ringgit",
        "New Zealand Dollar", "Philippine Peso", "Singapore Dollar",
        "Thai Baht", "South African Rand"
    ],

    DATASTORAGE: ["Bit", "Byte", "Gigabit", "Gigabyte", "Kilobit",
        "Kilobyte", "Megabit", "Megabyte", "Word"
    ],

    DENSITY: ["Aluminum", "Copper", "Gold", "Gram per Cubic Centimeter",
        "Iron", "Kilogram per Cubic Metre", "Lead", "Silver"
    ],
    ENERGYANDWORK: ["British Thermal Units", "Calories", "Electron Volts",
        "Ergs", "Foot-pounds", "Joules", "Kilocalories", "Kilojoules",
        "Kilowatt-hours", "Newton-meters"
    ],

    FLOW: ["Cubic Foot per Minute", "Cubic Meter per Hour",
        "Cubic Meter per Second", "Litres per Minute"
    ],

    FORCE: ["Dynes", "Kilopounds", "Kilonewtons", "Pounds", "Newtons",
        "Ounces-force"
    ],

    FREQUENCY: ["Gigahertz", "Hertz", "Kilohertz", "Megahertz",
        "Radians per Second", "Revolutions per Minute", "Terahertz"
    ],

    FUELCONSUMPTION: ["Kilometers per Liter", "Litres per 100 km",
        "Miles per Gallon (UK)", "Miles per Gallon (US)"
    ],

    LENGTH: ["Angstroms", "Astronomical Units", "Centimeters", "Decimeters",
        "Feet", "Inches", "Kilometers", "Light Years", "Meters",
        "Micrometers or Microns", "Miles", "Millimeters", "Mil or Thou",
        "Nautical Miles", "Nanometers", "Picometers", "Yards"
    ],

    MAGNETICFIELDSTRENGTH: ["Ampere per Meter", "Oersted"],

    MAGNETICFLUXDENSITY: ["Gamma", "Gauss", "Tesla"],

    MASS: ["Atomic Mass Units", "Grains", "Grams", "Kilograms",
        "Pounds-mass", "Microgram", "Milligrams", "Ounce", "Slugs"
    ],

    NUMBERS: ["Binary", "Decimal", "Hexadecimal", "Octal"],

    POWER: ["Boiler Horsepower", "British Thermal Units per Hour",
        "Calorie per Second","Decibel Milliwatts" , "Decibel Watts", "Electrical Horsepower",
        "Pound-Foot per Second", "Gigawatts", "Kilowatts",
        "Mechanical Horsepower", "Megawatts", "Terawatts", "Watts"
    ],

    PRESSURE: ["Bar", "Dynes per Square Centimeter",
        "Feet of Water Column at 4°C", "Hectopascals",
        "Inches of Water Column at 4°C", "Kilopascals", "Megapascals",
        "Millibar", "Millimeters of Mercury at 0°C",
        "Pascals(Newton per Meter)", "Pounds per Square Inch",
        "Standard Atmospheres", "Torr"
    ],

    SPEED: ["Feet per Second", "Kilometers per Hour", "Knots",
        "Mach Number at STP", "Miles per Hour", "Meters per Second"
    ],

    TEMPERATURE: ["Celsius", "Fahrenheit", "Kelvin", "Rankine"],

    TIME: ["Days", "Hours", "Microseconds", "Minutes", "Milliseconds",
        "Nanoseconds", "Seconds", "Years", "Weeks"
    ],

    TORQUE: ["Dyne Centimeter", "Dyne Meter", "Gram-Force Meter",
        "Kilogram-Force Meter",
        "Newton Centimeter", "Newton Meter", "Ounce-Force Inch",
        "Pound-Force Foot", "Pound-Force Inch"
    ],

    VOLUME: ["Centiliters", "Cubic Centimeters", "Cubic Feet",
        "Cubic Inches", "Cubic Kilometers", "Cubic Meters", "Cubic Miles",
        "Cubic Millimeters","Cubic Yards", "Liters", "Milliliters", "UK Liquid Gallons",
        "US Liquid Gallons", "US Liquid Ounces", "US Liquid Quarts"
    ],
}
