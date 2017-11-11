.pragma library
.import QtQuick.LocalStorage 2.0 as Sql

// global variable to hold database instance
var db;

function openDB() {
    db = Sql.LocalStorage.openDatabaseSync("UnitConverterDB","1.0","Unit Converter Database",1e5);
    createTable();
}

function createTable() {
    db.transaction( function(tx) {
        tx.executeSql("CREATE TABLE IF NOT EXISTS\
           Favourites (Id INTEGER PRIMARY KEY AUTOINCREMENT,\
                       unitconverter TEXT,\
                       fromUnit TEXT,\
                       fromUnitAbb TEXT,\
                       fromValue TEXT,\
                       toUnit TEXT,\
                       toUnitAbb,\
                       toValue TEXT)");
    });
}

function addFavourite(unitconverter, fromUnit, fromUnitAbb, fromValue,
                      toUnit, toUnitAbb, toValue) {
    db.readTransaction( function(tx) {
       var rs = tx.executeSql("SELECT unitconverter, fromUnit, fromUnitAbb, fromValue,\
                               toUnit, toUnitAbb, toValue FROM Favourites WHERE unitconverter=? AND \
                               fromUnit=? AND fromValue=? AND toUnit=? AND toValue=?",
                               [unitconverter, fromUnit, fromValue, toUnit, toValue]);
        if (rs.rows.length > 0) {
            console.log("Database already has identical item.");
            return;
        }
    });
    db.transaction( function(tx) {
        tx.executeSql("INSERT INTO Favourites(unitconverter,fromUnit,fromUnitAbb,fromValue,toUnit,toUnitAbb,toValue) \
                       VALUES(?,?,?,?,?,?,?)", [unitconverter, fromUnit, fromUnitAbb,
                                                fromValue, toUnit, toUnitAbb, toValue]
        );
    });
}

function removeFavourite(unitconverter, fromUnit, fromValue, toUnit, toValue) {
    db.transaction( function(tx) {
        tx.executeSql("DELETE FROM Favourites WHERE unitconverter=? AND \
                      fromUnit=? AND fromValue=? AND toUnit=? AND toValue=?",
                      [unitconverter, fromUnit, fromValue, toUnit, toValue]);
    });
}

function updateFavourite(unitconverter_old, fromUnit_old, fromValue_old, toUnit_old, toValue_old,
                         unitconverter_new, fromUnit_new, fromUnitAbb_new, fromValue_new,
                         toUnit_new, toUnitAbb_new, toValue_new) {
    db.transaction( function(tx) {
        tx.executeSql("\
                UPDATE Favourites SET unitconverter=?, fromUnit=?, fromUnitAbb=?, fromValue=?, toUnit=?, toUnitAbb=?, toValue=? \
                WHERE unitconverter=? AND fromUnit=? AND fromValue=? AND toUnit=? AND toValue=?",
                      [unitconverter_new, fromUnit_new, fromUnitAbb_new, fromValue_new, toUnit_new,
                       toUnitAbb_new, toValue_new,
                       unitconverter_old, fromUnit_old, fromValue_old, toUnit_old, toValue_old]);
    });
}

function getFavourites() {
    var data = [];
    db.readTransaction( function(tx) {
       var rs = tx.executeSql("SELECT unitconverter, fromUnit, fromUnitAbb, fromValue, \
                               toUnit, toUnitAbb, toValue FROM Favourites");
       var i = 0, count = rs.rows.length;
       for (; i < count; i++) {
           data[i] = rs.rows.item(i);
        }
    });
    return data;
}
