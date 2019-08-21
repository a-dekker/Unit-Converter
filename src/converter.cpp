#include <QString>
#include <QMap>
#include <QVector>
#include <QSet>
#include <QRegExp>
#include <QMetaEnum>
#include <QtCore/QtMath>
#include <math.h>
#include <QRegularExpression>
#include "settings.h"
#include "converter.h"

QString doConvert(double val, double conv_val)
{
    QSettings mySets;
    QString retval;
    QString notation = mySets.value("notation", "scientific").toString();
    if (notation == "scientific") {
        retval = QString::number(val * conv_val, 'g');
    }
    else {
        retval = QString::number(val * conv_val, 'f').replace(QRegularExpression("\\.?0+$"), "");
    }
    return retval;
}

Converter::Converter(QObject *parent) : QObject(parent) {}

QString Converter::convert2(QString from, QString to, QString value_,
                            QString unittype) const
{
    QStringList unitOptions;
    auto value = getType(value_.toDouble());
    QString unit = from;
    QString toCurrency = to;
    QString from2to = from + "2" + to;
    QMap<QString, QString> values;
    QMetaObject metaObj = this->staticMetaObject;
    QMetaEnum metaEnum = metaObj.enumerator(metaObj.indexOfEnumerator("Units"));

    double P = 1 * qPow(10, value / 10.0);
    double Pm = 1 * qPow(10, (value - 30) / 10.0);

    switch (metaEnum.keysToValue(
        unittype.replace(QRegExp(" "), "").toUpper().toLatin1())) {

    case ACCELERATION:

        values["m/s22cm/s2"] = doConvert(value, 100);
        values["m/s22mm/s2"] = doConvert(value, 1000);
        values["m/s22ft/s2"] = doConvert(value, 3.2808398950131);
        values["m/s22g"] = doConvert(value, 0.101971621);
        values["cm/s22m/s2"] = doConvert(value, 0.01);
        values["cm/s22mm/s2"] = doConvert(value, 10);
        values["cm/s22ft/s2"] = doConvert(value, 0.032808399);
        values["cm/s22g"] = doConvert(value, 0.001019716);
        values["mm/s22cm/s2"] = doConvert(value, 0.1);
        values["mm/s22m/s2"] = doConvert(value, 0.001);
        values["mm/s22ft/s2"] = doConvert(value, 0.00328084);
        values["mm/s22g"] = doConvert(value, 0.000101972);
        values["ft/s22m/s2"] = doConvert(value, 0.3048);
        values["ft/s22mm/s2"] = doConvert(value, 304.8);
        values["ft/s22cm/s2"] = doConvert(value, 30.48);
        values["ft/s22g"] = doConvert(value, 0.03108095);
        values["g2m/s2"] = doConvert(value, 9.80665);
        values["g2mm/s2"] = doConvert(value, 9806.65);
        values["g2ft/s2"] = doConvert(value, 32.174048556);
        values["g2cm/s2"] = doConvert(value, 980.665);

        return values[from2to];

    case ANGLE:
        values["deg2rad"] = doConvert(value, PI() / 180);
        values["deg2grad"] = doConvert(value, 1.111111111);
        values["rad2deg"] = doConvert(value, 180 / PI());
        values["rad2grad"] = doConvert(value, 200 / PI());
        values["grad2deg"] = doConvert(value, 0.9);
        values["grad2rad"] = doConvert(value, PI() / 200);

        return values[from2to];

    case AREA:
        unitOptions = (QStringList() << "acre"
                                     << "ha"
                                     << "cm2"
                                     << "ft2"
                                     << "in2"
                                     << "km2"
                                     << "m2"
                                     << "mi2"
                                     << "mm2"
                                     << "yd2");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["acre2ha"] = doConvert(value, 0.40468564224);
            values["acre2cm2"] = doConvert(value, 40468564.224);
            values["acre2ft2"] = doConvert(value, 43560);
            values["acre2in2"] = doConvert(value, 6272640);
            values["acre2km2"] = doConvert(value, 0.0040468564224);
            values["acre2m2"] = doConvert(value, 4046.8564224);
            values["acre2mi2"] = doConvert(value, 0.0015625);
            values["acre2mm2"] = doConvert(value, 4046856422.4);
            values["acre2yd2"] = doConvert(value, 4840);

            return values[from2to];
        case 1:
            values["ha2acre"] = doConvert(value, 2.471053814672);
            values["ha2cm2"] = doConvert(value, 100000000);
            values["ha2ft2"] = doConvert(value, 107639.1041671);
            values["ha2in2"] = doConvert(value, 15500031.00006);
            values["ha2km2"] = doConvert(value, 0.01);
            values["ha2m2"] = doConvert(value, 10000);
            values["ha2mi2"] = doConvert(value, 0.003861021585424);
            values["ha2mm2"] = doConvert(value, 10000000000);
            values["ha2yd2"] = doConvert(value, 11959.90046301);

            return values[from2to];
        case 2:
            values["cm22acre"] = doConvert(value, 2.471053814672e-8);
            values["cm22ha"] = doConvert(value, 1e-8);
            values["cm22ft2"] = doConvert(value, 0.001076391041671);
            values["cm22in2"] = doConvert(value, 0.1550003100006);
            values["cm22km2"] = doConvert(value, 1e-10);
            values["cm22m2"] = doConvert(value, 0.0001);
            values["cm22mi2"] = doConvert(value, 3.861021585424e-11);
            values["cm22mm2"] = doConvert(value, 100);
            values["cm22yd2"] = doConvert(value, 0.0001195990046301);

            return values[from2to];
        case 3:
            values["ft22acre"] = doConvert(value, 0.00002295684113866);
            values["ft22ha"] = doConvert(value, 0.000009290304);
            values["ft22cm2"] = doConvert(value, 929.0304);
            values["ft22in2"] = doConvert(value, 144);
            values["ft22km2"] = doConvert(value, 9.290304e-8);
            values["ft22m2"] = doConvert(value, 0.09290304);
            values["ft22mi2"] = doConvert(value, 3.587006427915e-8);
            values["ft22mm2"] = doConvert(value, 92903.04);
            values["ft22yd2"] = doConvert(value, 0.1111111111111111);

            return values[from2to];
        case 4:
            values["in22acre"] = doConvert(value, 1.594225079074e-7);
            values["in22ha"] = doConvert(value, 6.4516e-8);
            values["in22cm2"] = doConvert(value, 6.4516);
            values["in22ft2"] = doConvert(value, 0.006944444444444444);
            values["in22km2"] = doConvert(value, 6.4516e-10);
            values["in22m2"] = doConvert(value, 0.00064516);
            values["in22mi2"] = doConvert(value, 2.490976686052e-10);
            values["in22mm2"] = doConvert(value, 645.16);
            values["in22yd2"] = doConvert(value, 0.0007716049382716);

            return values[from2to];
        case 5:
            values["km22acre"] = doConvert(value, 247.1053814672);
            values["km22ha"] = doConvert(value, 100);
            values["km22cm2"] = doConvert(value, 1e10);
            values["km22ft2"] = doConvert(value, 10763910.41671);
            values["km22in2"] = doConvert(value, 1550003100.006);
            values["km22m2"] = doConvert(value, 1000000);
            values["km22mi2"] = doConvert(value, 0.3861021585425);
            values["km22mm2"] = doConvert(value, 1000000000000.0);
            values["km22yd2"] = doConvert(value, 1195990.046301);

            return values[from2to];
        case 6:
            values["m22acre"] = doConvert(value, 0.000247105381467);
            values["m22ha"] = doConvert(value, 0.0001);
            values["m22cm2"] = doConvert(value, 10000);
            values["m22ft2"] = doConvert(value, 10.76391041671);
            values["m22in2"] = doConvert(value, 1550.003100006);
            values["m22km2"] = doConvert(value, 0.000001);
            values["m22mi2"] = doConvert(value, 3.8610215854252e-7);
            values["m22mm2"] = doConvert(value, 1000000);
            values["m22yd2"] = doConvert(value, 1.195990046301);

            return values[from2to];
        case 7:
            values["mi22acre"] = doConvert(value, 640);
            values["mi22ha"] = doConvert(value, 258.9988110336);
            values["mi22cm2"] = doConvert(value, 25899881103.3);
            values["mi22ft2"] = doConvert(value, 27878400);
            values["mi22in2"] = doConvert(value, 4014489600.0);
            values["mi22km2"] = doConvert(value, 2.589988110336);
            values["mi22m2"] = doConvert(value, 2589988.110336);
            values["mi22mm2"] = doConvert(value, 2589988110336.0);
            values["mi22yd2"] = doConvert(value, 3097600);

            return values[from2to];
        case 8:
            values["mm22acre"] = doConvert(value, 2.471053814672e-10);
            values["mm22ha"] = doConvert(value, 1e-10);
            values["mm22cm2"] = doConvert(value, 0.01);
            values["mm22ft2"] = doConvert(value, 0.00001076391041671);
            values["mm22in2"] = doConvert(value, 0.001550003100006);
            values["mm22km2"] = doConvert(value, 1e-12);
            values["mm22m2"] = doConvert(value, 0.000001);
            values["mm22mi2"] = doConvert(value, 3.861021585425e-13);
            values["mm22yd2"] = doConvert(value, 0.000001195990046301);

            return values[from2to];
        case 9:
            values["yd22acre"] = doConvert(value, 0.0002066115702479);
            values["yd22ha"] = doConvert(value, 0.000083612736);
            values["yd22cm2"] = doConvert(value, 8361.2736);
            values["yd22ft2"] = doConvert(value, 9);
            values["yd22in2"] = doConvert(value, 1296);
            values["yd22km2"] = doConvert(value, 8.3612736e-7);
            values["yd22m2"] = doConvert(value, 0.83612736);
            values["yd22mi2"] = doConvert(value, 3.228305785124e-7);
            values["yd22mm2"] = doConvert(value, 836127.36);

            return values[from2to];
        }
        break;

    case CURRENCY:
        return QString::number(value *
                               currency_rate[toCurrency].value<double>() /
                               currency_rate[unit].value<double>());

    case DATASTORAGE:
        unitOptions = (QStringList() << "b"
                                     << "B"
                                     << "word"
                                     << "kb"
                                     << "KiB"
                                     << "Mb"
                                     << "MiB"
                                     << "Gb"
                                     << "GiB");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["b2B"] = doConvert(value, 0.125);
            values["b2word"] = doConvert(value, 0.0625);
            values["b2kb"] = doConvert(value, 0.000976563);
            values["b2KiB"] = doConvert(value, 0.00012207);
            values["b2Mb"] = doConvert(value, 0.000000954);
            values["b2MiB"] = doConvert(value, 0.000000119);
            values["b2Gb"] = doConvert(value, 9.313225746e-10);
            values["b2GiB"] = doConvert(value, 1.164153218e-10);

            return values[from2to];
        case 1:
            values["B2b"] = doConvert(value, 8);
            values["B2word"] = doConvert(value, 0.5);
            values["B2kb"] = doConvert(value, 0.0078125);
            values["B2KiB"] = doConvert(value, 0.000976563);
            values["B2Mb"] = doConvert(value, 0.000007629);
            values["B2MiB"] = doConvert(value, 0.000000954);
            values["B2Gb"] = doConvert(value, 0.000000007);
            values["B2GiB"] = doConvert(value, 9.313225746e-10);

            return values[from2to];
        case 2:
            values["word2b"] = doConvert(value, 16);
            values["word2B"] = doConvert(value, 2);
            values["word2kb"] = doConvert(value, 0.015625);
            values["word2KiB"] = doConvert(value, 0.001953125);
            values["word2Mb"] = doConvert(value, 0.000015259);
            values["word2MiB"] = doConvert(value, 0.000001907);
            values["word2Gb"] = doConvert(value, 0.000000015);
            values["word2GiB"] = doConvert(value, 0.000000002);

            return values[from2to];
        case 3:
            values["kb2B"] = doConvert(value, 128);
            values["kb2word"] = doConvert(value, 64);
            values["kb2b"] = doConvert(value, 1024);
            values["kb2KiB"] = doConvert(value, 0.125);
            values["kb2Mb"] = doConvert(value, 0.000976563);
            values["kb2MiB"] = doConvert(value, 0.00012207);
            values["kb2Gb"] = doConvert(value, 0.000000954);
            values["kb2GiB"] = doConvert(value, 0.000000119);

            return values[from2to];
        case 4:
            values["KiB2B"] = doConvert(value, 1024);
            values["KiB2word"] = doConvert(value, 512);
            values["KiB2kb"] = doConvert(value, 8);
            values["KiB2b"] = doConvert(value, 8192);
            values["KiB2Mb"] = doConvert(value, 0.0078125);
            values["KiB2MiB"] = doConvert(value, 0.000976562);
            values["KiB2Gb"] = doConvert(value, 0.000007629);
            values["KiB2GiB"] = doConvert(value, 0.000000954);

            return values[from2to];
        case 5:
            values["Mb2B"] = doConvert(value, 131072);
            values["Mb2word"] = doConvert(value, 65536);
            values["Mb2kb"] = doConvert(value, 1024);
            values["Mb2KiB"] = doConvert(value, 128);
            values["Mb2b"] = doConvert(value, 1048576);
            values["Mb2MiB"] = doConvert(value, 0.125);
            values["Mb2Gb"] = doConvert(value, 0.000976562);
            values["Mb2GiB"] = doConvert(value, 0.00012207);

            return values[from2to];
        case 6:
            values["MiB2B"] = doConvert(value, 1048576);
            values["MiB2word"] = doConvert(value, 524288);
            values["MiB2kb"] = doConvert(value, 8192);
            values["MiB2KiB"] = doConvert(value, 1024);
            values["MiB2Mb"] = doConvert(value, 8);
            values["MiB2b"] = doConvert(value, 8388608);
            values["MiB2Gb"] = doConvert(value, 0.0078125);
            values["MiB2GiB"] = doConvert(value, 0.000976563);

            return values[from2to];
        case 7:
            values["Gb2B"] = doConvert(value, 134217728);
            values["Gb2word"] = doConvert(value, 67108864);
            values["Gb2kb"] = doConvert(value, 1048576);
            values["Gb2KiB"] = doConvert(value, 131072);
            values["Gb2Mb"] = doConvert(value, 1024);
            values["Gb2MiB"] = doConvert(value, 128);
            values["Gb2b"] = doConvert(value, 1073741824);
            values["Gb2GiB"] = doConvert(value, 0.125);

            return values[from2to];
        case 8:
            values["GiB2B"] = doConvert(value, 1073741824);
            values["GiB2word"] = doConvert(value, 536870912);
            values["GiB2kb"] = doConvert(value, 8388608);
            values["GiB2KiB"] = doConvert(value, 1048576);
            values["GiB2Mb"] = doConvert(value, 8192);
            values["GiB2MiB"] = doConvert(value, 1024);
            values["GiB2Gb"] = doConvert(value, 8);
            values["GiB2b"] = doConvert(value, 8589934592);

            return values[from2to];
        }
        break;

    case DENSITY:
        unitOptions = (QStringList() << "Al"
                                     << "Cu"
                                     << "Au"
                                     << "g/cm3"
                                     << "Fe"
                                     << "kg/m3"
                                     << "Pb"
                                     << "Ag");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["Al2Cu"] = doConvert(value, 0.296766);
            values["Al2Au"] = doConvert(value, 0.136943);
            values["Al2g/cm3"] = doConvert(value, 2.699);
            values["Al2Fe"] = doConvert(value, 0.345129);
            values["Al2kg/m3"] = doConvert(value, 2699);
            values["Al2Pb"] = doConvert(value, 0.232454);
            values["Al2Ag"] = doConvert(value, 0.251475);

            return values[from2to];
        case 1:
            values["Cu2Al"] = doConvert(value, 3.369656);
            values["Cu2g/cm3"] = doConvert(value, 8.906);
            values["Cu2Fe"] = doConvert(value, 1.162967);
            values["Cu2kg/m3"] = doConvert(value, 8906);
            values["Cu2Pb"] = doConvert(value, 0.783289);
            values["Cu2Ag"] = doConvert(value, 0.847383);
            values["Cu2Au"] = doConvert(value, 0.461451);

            return values[from2to];
        case 2:
            values["Au2Cu"] = doConvert(value, 2.167078);
            values["Au2Al"] = doConvert(value, 7.302308);
            values["Au2g/cm3"] = doConvert(value, 19.3);
            values["Au2Fe"] = doConvert(value, 2.52024);
            values["Au2kg/m3"] = doConvert(value, 19300);
            values["Au2Pb"] = doConvert(value, 1.697449);
            values["Au2Ag"] = doConvert(value, 1.836346);

            return values[from2to];
        case 3:
            values["g/cm32Cu"] = doConvert(value, 0.112284);
            values["g/cm32Au"] = doConvert(value, 0.051813);
            values["g/cm32Al"] = doConvert(value, 0.378358);
            values["g/cm32Fe"] = doConvert(value, 0.130582);
            values["g/cm32kg/m3"] = doConvert(value, 1000);
            values["g/cm32Pb"] = doConvert(value, 0.087951);
            values["g/cm32Ag"] = doConvert(value, 0.095147);

            return values[from2to];
        case 4:
            values["Fe2Cu"] = doConvert(value, 0.85987);
            values["Fe2Au"] = doConvert(value, 0.396788);
            values["Fe2g/cm3"] = doConvert(value, 7.658);
            values["Fe2Al"] = doConvert(value, 2.897465);
            values["Fe2kg/m3"] = doConvert(value, 7658);
            values["Fe2Pb"] = doConvert(value, 0.673527);
            values["Fe2Ag"] = doConvert(value, 0.728639);

            return values[from2to];
        case 5:
            values["kg/m32Cu"] = doConvert(value, 0.000112);
            values["kg/m32Au"] = doConvert(value, 5.18134715025907e-5);
            values["kg/m32g/cm3"] = doConvert(value, 0.001);
            values["kg/m32Fe"] = doConvert(value, 0.000131);
            values["kg/m32Al"] = doConvert(value, 0.000378);
            values["kg/m32Pb"] = doConvert(value, 8.79507475813544e-5);
            values["kg/m32Ag"] = doConvert(value, 9.51474785918173e-5);

            return values[from2to];
        case 6:
            values["Pb2Cu"] = doConvert(value, 1.276667);
            values["Pb2Au"] = doConvert(value, 0.589119);
            values["Pb2g/cm3"] = doConvert(value, 11.37);
            values["Pb2Fe"] = doConvert(value, 1.484722);
            values["Pb2kg/m3"] = doConvert(value, 11370);
            values["Pb2Al"] = doConvert(value, 4.30193);
            values["Pb2Ag"] = doConvert(value, 1.081827);

            return values[from2to];
        case 7:
            values["Ag2Cu"] = doConvert(value, 1.180103);
            values["Ag2Au"] = doConvert(value, 0.54456);
            values["Ag2g/cm3"] = doConvert(value, 10.51);
            values["Ag2Fe"] = doConvert(value, 1.372421);
            values["Ag2kg/m3"] = doConvert(value, 10510);
            values["Ag2Pb"] = doConvert(value, 0.924362);
            values["Ag2Al"] = doConvert(value, 3.976542);

            return values[from2to];
        }
        break;

    case ENERGYANDWORK:
        unitOptions = (QStringList() << "Btu"
                                     << "cal"
                                     << "eV"
                                     << "erg"
                                     << "ftlb"
                                     << "J"
                                     << "kcal"
                                     << "kJ"
                                     << "kWh"
                                     << "Nm");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["Btu2cal"] = doConvert(value, 251.99577243);
            values["Btu2eV"] = doConvert(value, 6.5851382366e21);
            values["Btu2erg"] = doConvert(value, 10550559000);
            values["Btu2ftlb"] = doConvert(value, 778.16932495);
            values["Btu2J"] = doConvert(value, 1055.0559);
            values["Btu2kcal"] = doConvert(value, 0.25199577243);
            values["Btu2kJ"] = doConvert(value, 1.0550559);
            values["Btu2kWh"] = doConvert(value, 0.00029307108333);
            values["Btu2Nm"] = doConvert(value, 1055.0559);

            return values[from2to];
        case 1:
            values["cal2Btu"] = doConvert(value, 0.0039683205411);
            values["cal2eV"] = doConvert(value, 2613193933e10);
            values["cal2erg"] = doConvert(value, 41868000);
            values["cal2ftlb"] = doConvert(value, 3.0880253167);
            values["cal2J"] = doConvert(value, 4.1868);
            values["cal2kcal"] = doConvert(value, 0.001);
            values["cal2kJ"] = doConvert(value, 0.0041868);
            values["cal2kWh"] = doConvert(value, 0.000001163);
            values["cal2Nm"] = doConvert(value, 4.1868);

            return values[from2to];
        case 2:
            values["eV2Btu"] = doConvert(value, 1.5185710065e-22);
            values["eV2cal"] = doConvert(value, 3.8267347377e-20);
            values["eV2erg"] = doConvert(value, 1.6021773e-12);
            values["eV2ftlb"] = doConvert(value, 1.181705375e-19);
            values["eV2J"] = doConvert(value, 1.6021773e-19);
            values["eV2kcal"] = doConvert(value, 3.8267347377e-23);
            values["eV2kJ"] = doConvert(value, 1.6021773e-22);
            values["eV2kWh"] = doConvert(value, 4.4504925e-26);
            values["eV2Nm"] = doConvert(value, 1.6021773e-19);

            return values[from2to];
        case 3:
            values["erg2Btu"] = doConvert(value, 9.4781707775e-11);
            values["erg2cal"] = doConvert(value, 2.3884589663e-8);
            values["erg2eV"] = doConvert(value, 624150648000);
            values["erg2ftlb"] = doConvert(value, 7.3756217557e-8);
            values["erg2J"] = doConvert(value, 1e-7);
            values["erg2kcal"] = doConvert(value, 2.3884589663e-11);
            values["erg2kJ"] = doConvert(value, 1e-10);
            values["erg2kWh"] = doConvert(value, 2.7777777778e-14);
            values["erg2Nm"] = doConvert(value, 1e-7);

            return values[from2to];
        case 4:
            values["ftlb2Btu"] = doConvert(value, 0.0012850673599);
            values["ftlb2cal"] = doConvert(value, 0.32383154199);
            values["ftlb2eV"] = doConvert(value, 8462346208500000000);
            values["ftlb2erg"] = doConvert(value, 13558179);
            values["ftlb2J"] = doConvert(value, 1.3558179);
            values["ftlb2kcal"] = doConvert(value, 0.00032383154199);
            values["ftlb2kJ"] = doConvert(value, 0.0013558179);
            values["ftlb2kWh"] = doConvert(value, 3.7661608333e-7);
            values["ftlb2Nm"] = doConvert(value, 1.3558179);

            return values[from2to];
        case 5:
            values["J2Btu"] = doConvert(value, 0.00094781707775);
            values["J2cal"] = doConvert(value, 0.23884589663);
            values["J2eV"] = doConvert(value, 6241506480000000000);
            values["J2erg"] = doConvert(value, 10000000);
            values["J2ftlb"] = doConvert(value, 0.73756217557);
            values["J2kcal"] = doConvert(value, 0.00023884589663);
            values["J2kJ"] = doConvert(value, 0.001);
            values["J2kWh"] = doConvert(value, 2.7777777778e-7);
            values["J2Nm"] = QString::number(value);

            return values[from2to];
        case 6:
            values["kcal2Btu"] = doConvert(value, 0.0041868);
            values["kcal2cal"] = doConvert(value, 1000);
            values["kcal2eV"] = doConvert(value, 2.613193933e+22);
            values["kcal2erg"] = doConvert(value, 41868000000);
            values["kcal2ftlb"] = doConvert(value, 3088.0253167);
            values["kcal2J"] = doConvert(value, 4186.8);
            values["kcal2kJ"] = doConvert(value, 4.1868);
            values["kcal2kWh"] = doConvert(value, 0.001163);
            values["kcal2Nm"] = doConvert(value, 4186.8);

            return values[from2to];
        case 7:
            values["kJ2Btu"] = doConvert(value, 0.94781707775);
            values["kJ2cal"] = doConvert(value, 238.84589663);
            values["kJ2eV"] = doConvert(value, 6.24150648e+21);
            values["kJ2erg"] = doConvert(value, 10000000000);
            values["kJ2ftlb"] = doConvert(value, 737.56217557);
            values["kJ2J"] = doConvert(value, 1000);
            values["kJ2kcal"] = doConvert(value, 0.23884589663);
            values["kJ2kWh"] = doConvert(value, 0.00027777777778);
            values["kJ2Nm"] = doConvert(value, 1000);

            return values[from2to];
        case 8:
            values["kWh2Btu"] = doConvert(value, 3412.1414799);
            values["kWh2cal"] = doConvert(value, 859845.22786);
            values["kWh2eV"] = doConvert(value, 2.2469423328e+25);
            values["kWh2erg"] = doConvert(value, 36000000000000);
            values["kWh2ftlb"] = doConvert(value, 2655223.8321);
            values["kWh2J"] = doConvert(value, 3600000);
            values["kWh2kcal"] = doConvert(value, 859.84522786);
            values["kWh2kJ"] = doConvert(value, 3600);
            values["kWh2Nm"] = doConvert(value, 3600000);

            return values[from2to];
        case 9:
            values["Nm2Btu"] = doConvert(value, 0.00094781707775);
            values["Nm2cal"] = doConvert(value, 0.23884589663);
            values["Nm2eV"] = doConvert(value, 6241506480000000000);
            values["Nm2erg"] = doConvert(value, 10000000);
            values["Nm2ftlb"] = doConvert(value, 0.73756217557);
            values["Nm2J"] = QString::number(value);
            values["Nm2kcal"] = doConvert(value, 0.00023884589663);
            values["Nm2kJ"] = doConvert(value, 0.001);
            values["Nm2kWh"] = doConvert(value, 2.7777777778e-7);

            return values[from2to];
        }
        break;
    case FLOW:
        unitOptions = (QStringList() << "m3/h"
                                     << "m3/s"
                                     << "cfm"
                                     << "L/min");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["m3/h2m3/s"] = doConvert(value, 0.000277778);
            values["m3/h2cfm"] = doConvert(value, 0.588577779);
            values["m3/h2L/min"] = doConvert(value, 16.666666667);
            return values[from2to];
        case 1:
            values["m3/s2m3/h"] = doConvert(value, 3600);
            values["m3/s2cfm"] = doConvert(value, 2118.880003185);
            values["m3/s2L/min"] = doConvert(value, 60000);
            return values[from2to];
        case 2:
            values["cfm2m3/s"] = doConvert(value, 0.000471947);
            values["cfm2m3/h"] = doConvert(value, 1.699010796);
            values["cfm2L/min"] = doConvert(value, 28.316846593);
            return values[from2to];
        case 3:
            values["L/min2m3/s"] = doConvert(value, 0.000016667);
            values["L/min2cfm"] = doConvert(value, 0.035314667);
            values["L/min2m3/h"] = doConvert(value, 0.06);
            return values[from2to];
        }
        break;
    case FORCE:
        unitOptions = (QStringList() << "dyn"
                                     << "kip"
                                     << "kN"
                                     << "lbf"
                                     << "N"
                                     << "ozf");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["dyn2kip"] = doConvert(value, 2.2480894387e-9);
            values["dyn2kN"] = doConvert(value, 1e-8);
            values["dyn2lbf"] = doConvert(value, 0.0000022480894387);
            values["dyn2N"] = doConvert(value, 0.00001);
            values["dyn2ozf"] = doConvert(value, 0.000035969431019);

            return values[from2to];
        case 1:
            values["kip2dyn"] = doConvert(value, 444822160);
            values["kip2kN"] = doConvert(value, 4.4482216);
            values["kip2lbf"] = doConvert(value, 1e3);
            values["kip2N"] = doConvert(value, 4448.2216);
            values["kip2ozf"] = doConvert(value, 16000);

            return values[from2to];
        case 2:
            values["kN2dyn"] = doConvert(value, 100000000);
            values["kN2kip"] = doConvert(value, 0.22480894387);
            values["kN2lbf"] = doConvert(value, 224.80894309971052);
            values["kN2N"] = doConvert(value, 1000);
            values["kN2ozf"] = doConvert(value, 3596.9431019);

            return values[from2to];
        case 3:
            values["lbf2dyn"] = doConvert(value, 444822.16);
            values["lbf2kip"] = doConvert(value, 0.001);
            values["lbf2kN"] = doConvert(value, 0.004448221615260499);
            values["lbf2N"] = doConvert(value, 4.4482216152605);
            values["lbf2ozf"] = doConvert(value, 16);

            return values[from2to];
        case 4:
            values["N2dyn"] = doConvert(value, 100000);
            values["N2kip"] = doConvert(value, 0.00022480894387);
            values["N2kN"] = doConvert(value, 0.001);
            values["N2lbf"] = doConvert(value, 0.2248089430997105);
            values["N2ozf"] = doConvert(value, 3.5969431019);

            return values[from2to];
        case 5:
            values["ozf2dyn"] = doConvert(value, 27801.385);
            values["ozf2kip"] = doConvert(value, 0.0000625);
            values["ozf2kN"] = doConvert(value, 0.00027801385);
            values["ozf2lbf"] = doConvert(value, 0.0625);
            values["ozf2N"] = doConvert(value, 0.27801385);

            return values[from2to];
        }
        break;

    case FREQUENCY:
        unitOptions = (QStringList() << "GHz"
                                     << "Hz"
                                     << "kHz"
                                     << "MHz"
                                     << "rad/s"
                                     << "rpm"
                                     << "THz");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["GHz2Hz"] = doConvert(value, 1e9);
            values["GHz2kHz"] = doConvert(value, 1e6);
            values["GHz2MHz"] = doConvert(value, 1e3);
            values["GHz2rad/s"] = doConvert(value, 2 * PI() * 1e9);
            values["GHz2rpm"] = doConvert(value, 60 * 1e9);
            values["GHz2THz"] = doConvert(value, 1e-3);

            return values[from2to];
        case 1:
            values["Hz2GHz"] = doConvert(value, 1e-9);
            values["Hz2kHz"] = doConvert(value, 1e-3);
            values["Hz2MHz"] = doConvert(value, 1e-6);
            values["Hz2rad/s"] = doConvert(value, 2 * PI());
            values["Hz2rpm"] = doConvert(value, 60);
            values["Hz2THz"] = doConvert(value, 1e-12);

            return values[from2to];
        case 2:
            values["kHz2GHz"] = doConvert(value, 1e-6);
            values["kHz2Hz"] = doConvert(value, 1e3);
            values["kHz2MHz"] = doConvert(value, 1e-3);
            values["kHz2rad/s"] = doConvert(value, 2 * PI() * 1e3);
            values["kHz2rpm"] = doConvert(value, 60 * 1e3);
            values["kHz2THz"] = doConvert(value, 1e-9);

            return values[from2to];
        case 3:
            values["MHz2GHz"] = doConvert(value, 1e-3);
            values["MHz2Hz"] = doConvert(value, 1e6);
            values["MHz2kHz"] = doConvert(value, 1e3);
            values["MHz2rad/s"] = doConvert(value, 2 * PI() * 1e6);
            values["MHz2rpm"] = doConvert(value, 60 * 1e6);
            values["MHz2THz"] = doConvert(value, 1e-6);

            return values[from2to];
        case 4:
            values["rad/s2GHz"] = QString::number(value / (2 * PI()) * 1e-9);
            values["rad/s2Hz"] = QString::number(value / (2 * PI()));
            values["rad/s2kHz"] = QString::number(value / (2 * PI()) * 1e-3);
            values["rad/s2MHz"] = QString::number(value / (2 * PI()) * 1e-6);
            values["rad/s2rpm"] = QString::number(value / (2 * PI()) * 60);
            values["rad/s2THz"] = QString::number(value / (2 * PI()) * 1e-12);

            return values[from2to];
        case 5:
            values["rpm2GHz"] = QString::number(value / 60 * 1e-9);
            values["rpm2Hz"] = QString::number(value / 60);
            values["rpm2kHz"] = QString::number(value / 60 * 1e-3);
            values["rpm2MHz"] = QString::number(value / 60 * 1e-6);
            values["rpm2rad/s"] = doConvert(value, (2 * PI()) / 60);
            values["rpm2THz"] = QString::number(value / 60 * 1e-12);

            return values[from2to];
        case 6:
            values["THz2GHz"] = doConvert(value, 1e3);
            values["THz2Hz"] = doConvert(value, 1e12);
            values["THz2kHz"] = doConvert(value, 1e9);
            values["THz2MHz"] = doConvert(value, 1e6);
            values["THz2rad/s"] = doConvert(value, (2 * PI()) * 1e12);
            values["THz2rmp"] = doConvert(value, 60 * 1e12);

            return values[from2to];
        }
        break;
    case FUELCONSUMPTION:
        unitOptions = (QStringList() << "km/L"
                                     << "L/100km"
                                     << "mpg"
                                     << "impg");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["km/L2L/100km"] = QString::number(100/value);
            values["km/L2mpg"] = doConvert(value, 2.352145833);
            values["km/L2impg"] = doConvert(value, 2.8248093627967);
            return values[from2to];
        case 1:
            values["L/100km2km/L"] = QString::number(100/value);
            values["L/100km2mpg"] = QString::number(235.214583295/value);
            values["L/100km2impg"] = QString::number(282.48093627967/value);
            return values[from2to];
        case 2:
            values["mpg2km/L"] = doConvert(value, 0.425143707);
            values["mpg2L/100km"] = QString::number(235.214583295/value);
            values["mpg2impg"] = doConvert(value, 1.2009499254801);
            return values[from2to];
        case 3:
            values["impg2km/L"] = doConvert(value, 0.35400619);
            values["impg2L/100km"] = doConvert(value, 282.48093627967);
            values["impg2mpg"] = doConvert(value, 0.83267418464614);
            return values[from2to];
        }
    case LENGTH:
        unitOptions = (QStringList() << "A"
                                     << "au"
                                     << "cm"
                                     << "dm"
                                     << "ft"
                                     << "in"
                                     << "km"
                                     << "ly"
                                     << "m"
                                     << "um"
                                     << "mi"
                                     << "mm"
                                     << "mil"
                                     << "nautmi"
                                     << "nm"
                                     << "pm"
                                     << "yd");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["A2au"] = doConvert(value, 6.684587122671e-22);
            values["A2cm"] = doConvert(value, 1e-8);
            values["A2dm"] = doConvert(value, 1e-9);
            values["A2ft"] = doConvert(value, 3.280839895013e-10);
            values["A2in"] = doConvert(value, 3.937007874016e-9);
            values["A2km"] = doConvert(value, 1e-13);
            values["A2ly"] = doConvert(value, 1.057000834025e-26);
            values["A2m"] = doConvert(value, 1e-10);
            values["A2um"] = doConvert(value, 0.0001);
            values["A2mi"] = doConvert(value, 6.213711922373e-14);
            values["A2mm"] = doConvert(value, 1e-7);
            values["A2mil"] = doConvert(value, 3.937007874015748e-06);
            values["A2nautmi"] = doConvert(value, 5.399568034557e-14);
            values["A2nm"] = doConvert(value, 0.1);
            values["A2pm"] = doConvert(value, 100);
            values["A2yd"] = doConvert(value, 1.093613298338e-10);

            return values[from2to];
        case 1:
            values["au2A"] = doConvert(value, 1.49597870691e21);
            values["au2cm"] = doConvert(value, 1.49597870691e13);
            values["au2dm"] = doConvert(value, 1.49597870691e12);
            values["au2ft"] = doConvert(value, 490806662372);
            values["au2in"] = doConvert(value, 5889679948464);
            values["au2km"] = doConvert(value, 1.49597870691e8);
            values["au2ly"] = doConvert(value, 0.00001581250740887);
            values["au2m"] = doConvert(value, 1.49597870691e11);
            values["au2um"] = doConvert(value, 1.49597870691e17);
            values["au2mi"] = doConvert(value, 92955807.26743);
            values["au2mm"] = doConvert(value, 1.49597870691e14);
            values["au2mil"] = doConvert(value, 5889679948818897.0);
            values["au2nautmi"] = doConvert(value, 80776388.06695464);
            values["au2nm"] = doConvert(value, 1.49597870691e20);
            values["au2pm"] = doConvert(value, 1.49597870691e23);
            values["au2yd"] = doConvert(value, 163602220790.7);

            return values[from2to];
        case 2:
            values["cm2A"] = doConvert(value, 100000000);
            values["cm2au"] = doConvert(value, 6.684587122268446e-14);
            values["cm2dm"] = doConvert(value, 0.1);
            values["cm2ft"] = doConvert(value, 0.03280839895013);
            values["cm2in"] = doConvert(value, 0.39370078740157477);
            values["cm2km"] = doConvert(value, 0.00001);
            values["cm2ly"] = doConvert(value, 1.0570008340246155e-18);
            values["cm2m"] = doConvert(value, 0.01);
            values["cm2um"] = doConvert(value, 10000);
            values["cm2mi"] = doConvert(value, 0.000006213711922373);
            values["cm2mm"] = doConvert(value, 10);
            values["cm2mil"] = doConvert(value, 393.7007874015748);
            values["cm2nautmi"] =
                QString::number(value * 5.399568034557236e-06);
            values["cm2nm"] = doConvert(value, 10000000);
            values["cm2pm"] = doConvert(value, 10000000000);
            values["cm2yd"] = doConvert(value, 0.01093613298338);

            return values[from2to];
        case 3:
            values["dm2A"] = doConvert(value, 10000000);
            values["dm2au"] = doConvert(value, 6.684587122268446e-13);
            values["dm2cm"] = doConvert(value, 10);
            values["dm2ft"] = doConvert(value, 0.3280839895013);
            values["dm2in"] = doConvert(value, 3.9370078740157477);
            values["dm2km"] = doConvert(value, 0.0001);
            values["dm2ly"] = doConvert(value, 1.0570008340246155e-17);
            values["dm2m"] = doConvert(value, 0.1);
            values["dm2um"] = doConvert(value, 100000);
            values["dm2mi"] = doConvert(value, 0.00006213711922373);
            values["dm2mm"] = doConvert(value, 100);
            values["dm2mil"] = doConvert(value, 3937.007874015748);
            values["dm2nautmi"] =
                QString::number(value * 5.399568034557236e-05);
            values["dm2nm"] = doConvert(value, 100000000);
            values["dm2pm"] = doConvert(value, 100000000000);
            values["dm2yd"] = doConvert(value, 0.1093613298338);

            return values[from2to];
        case 4:
            values["ft2A"] = doConvert(value, 3.048e9);
            values["ft2au"] = doConvert(value, 2.03746215499e-12);
            values["ft2cm"] = doConvert(value, 30.48);
            values["ft2dm"] = doConvert(value, 3.048);
            values["ft2in"] = doConvert(value, 12);
            values["ft2km"] = doConvert(value, 0.0003048);
            values["ft2ly"] = doConvert(value, 3.221738542107e-17);
            values["ft2m"] = doConvert(value, 0.3048);
            values["ft2um"] = doConvert(value, 304800);
            values["ft2mi"] = QString::number(value / 5280);
            values["ft2mm"] = doConvert(value, 304.8);
            values["ft2mil"] = doConvert(value, 12000);
            values["ft2nautmi"] = doConvert(value, 0.0001645788336933);
            values["ft2nm"] = doConvert(value, 304800000);
            values["ft2pm"] = doConvert(value, 304800000000);
            values["ft2yd"] = QString::number(value / 3);

            return values[from2to];
        case 5:
            values["in2A"] = doConvert(value, 254000000);
            values["in2au"] = doConvert(value, 1.697885129158e-13);
            values["in2cm"] = doConvert(value, 2.54);
            values["in2dm"] = doConvert(value, 0.254);
            values["in2ft"] = QString::number(value / 12);
            values["in2km"] = doConvert(value, 0.0000254);
            values["in2ly"] = QString::number(value / 3.725e+17);
            values["in2m"] = doConvert(value, 0.0254);
            values["in2um"] = doConvert(value, 25400);
            values["in2mi"] = doConvert(value, 0.00001578282828283);
            values["in2mm"] = doConvert(value, 25.4);
            values["in2mil"] = doConvert(value, 1000);
            values["in2nautmi"] = doConvert(value, 0.00001371490280778);
            values["in2nm"] = doConvert(value, 25400000);
            values["in2pm"] = QString::number(value / 2.54e+10);
            values["in2yd"] = QString::number(value / 36);

            return values[from2to];
        case 6:
            values["km2A"] = doConvert(value, 1e13);
            values["km2au"] = doConvert(value, 6.684587122671e-9);
            values["km2cm"] = doConvert(value, 100000);
            values["km2dm"] = doConvert(value, 10000);
            values["km2ft"] = doConvert(value, 3280.839895013);
            values["km2in"] = QString::number(value / 0.0000254);
            values["km2ly"] = doConvert(value, 1.057000834025e-13);
            values["km2m"] = doConvert(value, 1e3);
            values["km2um"] = doConvert(value, 1000000000);
            values["km2mi"] = QString::number(value / 1.609344);
            values["km2mm"] = doConvert(value, 1000000);
            values["km2mil"] = doConvert(value, 39370078.740158);
            values["km2nautmi"] = doConvert(value, 0.5399568034557);
            values["km2nm"] = doConvert(value, 1e12);
            values["km2pm"] = doConvert(value, 1e15);
            values["km2yd"] = doConvert(value, 1093.613298338);

            return values[from2to];
        case 7:
            values["ly2A"] = doConvert(value, 9.460730473e25);
            values["ly2au"] = doConvert(value, 63241.07708807);
            values["ly2cm"] = doConvert(value, 9.46073047258100000e17);
            values["ly2dm"] = doConvert(value, 9.460730473e+16);
            values["ly2ft"] = doConvert(value, 3.1039141970410000e16);
            values["ly2in"] = doConvert(value, 3.72469703644900000e17);
            values["ly2km"] = doConvert(value, 9.460730473e+12);
            values["ly2m"] = doConvert(value, 9.460730473e+15);
            values["ly2um"] = doConvert(value, 9.460730473e+21);
            values["ly2mi"] = doConvert(value, 5878625373184);
            values["ly2mm"] = doConvert(value, 9.460730473e+21);
            values["ly2mil"] = doConvert(value, 3.724697036e+20);
            values["ly2nautmi"] = doConvert(value, 5108385784331);
            values["ly2nm"] = doConvert(value, 9.460730473e+24);
            values["ly2pm"] = doConvert(value, 9.460730473e+27);
            values["ly2yd"] = doConvert(value, 1.034638066e+16);

            return values[from2to];
        case 8:
            values["m2A"] = doConvert(value, 1e+10);
            values["m2au"] = doConvert(value, 6.684587122671e-12);
            values["m2cm"] = doConvert(value, 100);
            values["m2dm"] = doConvert(value, 10);
            values["m2ft"] = doConvert(value, 3.280839895013);
            values["m2in"] = QString::number(value / 0.0254);
            values["m2ly"] = doConvert(value, 1.057000834025e-16);
            values["m2km"] = QString::number(value / 1000);
            values["m2um"] = doConvert(value, 1000000);
            values["m2mi"] = doConvert(value, 0.0006213711922373);
            values["m2mm"] = doConvert(value, 1000);
            values["m2mil"] = doConvert(value, 39370.078740158);
            values["m2nautmi"] = doConvert(value, 0.0005399568034557);
            values["m2nm"] = doConvert(value, 1e9);
            values["m2pm"] = doConvert(value, 1e12);
            values["m2yd"] = doConvert(value, 1.093613298338);

            return values[from2to];
        case 9:
            values["um2A"] = doConvert(value, 10000);
            values["um2au"] = doConvert(value, 6.684587123e-18);
            values["um2cm"] = doConvert(value, 0.0001);
            values["um2dm"] = doConvert(value, 0.00001);
            values["um2ft"] = doConvert(value, 0.000003281);
            values["um2in"] = QString::number(value / 25400);
            values["um2ly"] = doConvert(value, 1.057000834e-22);
            values["um2km"] = doConvert(value, 0.000000001);
            values["um2m"] = doConvert(value, 1e-6);
            values["um2mi"] = doConvert(value, 6.213711922e-10);
            values["um2mm"] = doConvert(value, 0.001);
            values["um2mil"] = doConvert(value, 0.039370079);
            values["um2nautmi"] = doConvert(value, 5.399568035e-10);
            values["um2nm"] = doConvert(value, 1e3);
            values["um2pm"] = doConvert(value, 1e6);
            values["um2yd"] = doConvert(value, 0.000001094);

            return values[from2to];
        case 10:
            values["mi2A"] = doConvert(value, 1.609344e+13);
            values["mi2au"] = doConvert(value, 0.000000011);
            values["mi2cm"] = doConvert(value, 160934.4);
            values["mi2dm"] = doConvert(value, 16093.44);
            values["mi2ft"] = doConvert(value, 5280);
            values["mi2in"] = doConvert(value, 63360);
            values["mi2ly"] = doConvert(value, 1.701077950232e-13);
            values["mi2km"] = doConvert(value, 1.609344);
            values["mi2m"] = doConvert(value, 1609.344);
            values["mi2um"] = doConvert(value, 1609344000);
            values["mi2mm"] = doConvert(value, 1609344);
            values["mi2mil"] = doConvert(value, 63360000);
            values["mi2nautmi"] = doConvert(value, 0.8689762419006);
            values["mi2nm"] = doConvert(value, 1.609344e+12);
            values["mi2pm"] = doConvert(value, 1.609344e+15);
            values["mi2yd"] = doConvert(value, 1760);

            return values[from2to];
        case 11:
            values["mm2A"] = doConvert(value, 10000000);
            values["mm2au"] = doConvert(value, 6.684587123e-15);
            values["mm2cm"] = doConvert(value, 0.1);
            values["mm2dm"] = doConvert(value, 0.01);
            values["mm2ft"] = doConvert(value, 0.00328084);
            values["mm2in"] = doConvert(value, 0.039370079);
            values["mm2ly"] = doConvert(value, 1.057000834e-19);
            values["mm2km"] = doConvert(value, 0.000001);
            values["mm2m"] = doConvert(value, 0.001);
            values["mm2um"] = doConvert(value, 1e3);
            values["mm2mi"] = doConvert(value, 6.213711922373e-7);
            values["mm2mil"] = doConvert(value, 39.37007874);
            values["mm2nautmi"] = doConvert(value, 0.00000054);
            values["mm2nm"] = doConvert(value, 1000000);
            values["mm2pm"] = doConvert(value, 1000000000);
            values["mm2yd"] = doConvert(value, 0.001093613298338);

            return values[from2to];
        case 12:
            values["mil2A"] = doConvert(value, 254000);
            values["mil2au"] = doConvert(value, 1.697885129e-16);
            values["mil2cm"] = doConvert(value, 0.00254);
            values["mil2dm"] = doConvert(value, 0.000254);
            values["mil2ft"] = doConvert(value, 0.000083333);
            values["mil2in"] = doConvert(value, 0.001);
            values["mil2ly"] = doConvert(value, 2.684782118e-21);
            values["mil2km"] = doConvert(value, 0.000000025);
            values["mil2m"] = doConvert(value, 0.0000254);
            values["mil2um"] = doConvert(value, 25.4);
            values["mil2mi"] = doConvert(value, 0.000000016);
            values["mil2mm"] = doConvert(value, 0.0254);
            values["mil2nautmi"] = doConvert(value, 0.000000014);
            values["mil2nm"] = doConvert(value, 25400);
            values["mil2pm"] = doConvert(value, 25400000);
            values["mil2yd"] = doConvert(value, 0.000027778);

            return values[from2to];
        case 13:
            values["nautmi2A"] = doConvert(value, 1.852e13);
            values["nautmi2au"] = doConvert(value, 0.000000012);
            values["nautmi2cm"] = doConvert(value, 185200);
            values["nautmi2dm"] = doConvert(value, 18520);
            values["nautmi2ft"] = doConvert(value, 6076.115485564);
            values["nautmi2in"] = doConvert(value, 72913.385826772);
            values["nautmi2ly"] = doConvert(value, 1.957565545e-13);
            values["nautmi2km"] = doConvert(value, 1.852);
            values["nautmi2m"] = doConvert(value, 1852);
            values["nautmi2um"] = doConvert(value, 1852000000);
            values["nautmi2mi"] = doConvert(value, 1.150779448);
            values["nautmi2mm"] = doConvert(value, 1852000);
            values["nautmi2mil"] = doConvert(value, 72913385.826772);
            values["nautmi2nm"] = doConvert(value, 1.852e12);
            values["nautmi2pm"] = doConvert(value, 1.852e15);
            values["nautmi2yd"] = doConvert(value, 2025.371828521);

            return values[from2to];
        case 14:
            values["nm2A"] = doConvert(value, 10);
            values["nm2au"] = doConvert(value, 6.684587123e-21);
            values["nm2cm"] = doConvert(value, 0.0000001);
            values["nm2dm"] = doConvert(value, 0.00000001);
            values["nm2ft"] = doConvert(value, 0.000000003);
            values["nm2in"] = doConvert(value, 0.000000039);
            values["nm2ly"] = doConvert(value, 1.057000834e-25);
            values["nm2km"] = doConvert(value, 1e-12);
            values["nm2m"] = doConvert(value, 1e-9);
            values["nm2um"] = doConvert(value, 0.001);
            values["nm2mi"] = doConvert(value, 6.213711922e-13);
            values["nm2mm"] = doConvert(value, 0.000001);
            values["nm2mil"] = doConvert(value, 0.00003937);
            values["nm2nautmi"] = doConvert(value, 5.399568035e-13);
            values["nm2pm"] = doConvert(value, 1000);
            values["nm2yd"] = doConvert(value, 0.000000001);

            return values[from2to];
        case 15:
            values["pm2A"] = doConvert(value, 6.684587123e-24);
            values["pm2au"] = doConvert(value, 6.684587123e-24);
            values["pm2cm"] = doConvert(value, 0.01);
            values["pm2dm"] = doConvert(value, 1e-11);
            values["pm2ft"] = doConvert(value, 3.280839895e-12);
            values["pm2in"] = doConvert(value, 3.937007874e-11);
            values["pm2ly"] = doConvert(value, 1.057000834e-28);
            values["pm2km"] = doConvert(value, 1e-15);
            values["pm2m"] = doConvert(value, 1e-12);
            values["pm2um"] = doConvert(value, 0.000001);
            values["pm2mi"] = doConvert(value, 6.213711922e-16);
            values["pm2mm"] = doConvert(value, 1e-9);
            values["pm2mil"] = doConvert(value, 0.000000039);
            values["pm2nautmi"] = doConvert(value, 5.399568035e-16);
            values["pm2nm"] = doConvert(value, 0.001);
            values["pm2yd"] = doConvert(value, 1.093613298e-12);

            return values[from2to];
        case 16:
            values["yd2A"] = doConvert(value, 9144000000);
            values["yd2au"] = doConvert(value, 6.112386465e-12);
            values["yd2cm"] = doConvert(value, 91.44);
            values["yd2dm"] = doConvert(value, 9.144);
            values["yd2ft"] = doConvert(value, 3);
            values["yd2in"] = doConvert(value, 36);
            values["yd2ly"] = doConvert(value, 9.665215626e-17);
            values["yd2km"] = doConvert(value, 0.0009144);
            values["yd2m"] = doConvert(value, 0.9144);
            values["yd2um"] = doConvert(value, 914400);
            values["yd2mi"] = doConvert(value, 0.000568182);
            values["yd2mm"] = doConvert(value, 914.4);
            values["yd2mil"] = doConvert(value, 36000);
            values["yd2nautmi"] = doConvert(value, 0.000493737);
            values["yd2nm"] = doConvert(value, 914400000);
            values["yd2pm"] = doConvert(value, 9.144e11);

            return values[from2to];
        }
        break;

    case MASS:
        unitOptions = (QStringList() << "amu"
                                     << "g"
                                     << "gr"
                                     << "kg"
                                     << "lbm"
                                     << "ug"
                                     << "mg"
                                     << "oz"
                                     << "slug");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["amu2g"] = doConvert(value, 1.6605402e-24);
            values["amu2gr"] = doConvert(value, 2.562605143e-23);
            values["amu2kg"] = doConvert(value, 1.6605402e-27);
            values["amu2lbm"] = doConvert(value, 3.660864489409e-27);
            values["amu2ug"] = doConvert(value, 1.6605402e-18);
            values["amu2mg"] = doConvert(value, 1.6605402e-21);
            values["amu2oz"] = doConvert(value, 5.857383183e-26);
            values["amu2slug"] =
                QString::number(value * (3.660864489409 * 1e-27) / 32.17405);

            return values[from2to];
        case 1:
            values["g2amu"] = doConvert(value, 6.022136651675 * 1e23);
            values["g2gr"] = doConvert(value, 15.432358353);
            values["g2kg"] = doConvert(value, 1e-3);
            values["g2lbm"] = doConvert(value, 0.002204622621849);
            values["g2ug"] = doConvert(value, 1e6);
            values["g2mg"] = doConvert(value, 1e3);
            values["g2oz"] = doConvert(value, 0.035273962);
            values["g2slug"] =
                QString::number(value * 0.002204622621849 / 32.17405);

            return values[from2to];

        case 2:
            values["gr2amu"] = doConvert(value, 3.902278909e22);
            values["gr2g"] = doConvert(value, 0.06479891);
            values["gr2kg"] = doConvert(value, 0.000064799);
            values["gr2lbm"] = doConvert(value, 0.000142857);
            values["gr2ug"] = doConvert(value, 64798.910000174);
            values["gr2mg"] = doConvert(value, 64.79891);
            values["gr2oz"] = doConvert(value, 0.002285714);
            values["gr2slug"] = doConvert(value, 0.00000444);

            return values[from2to];

        case 3:
            values["kg2amu"] = doConvert(value, 6.022136651675e26);
            values["kg2g"] = doConvert(value, 1000);
            values["kg2gr"] = doConvert(value, 15432.3583529);
            values["kg2lbm"] = QString::number(value / 0.45359237);
            values["kg2ug"] = doConvert(value, 1000000000);
            values["kg2mg"] = doConvert(value, 1000000);
            values["kg2oz"] = doConvert(value, 35.27396195);
            values["kg2slug"] = QString::number(value / 14.5939);

            return values[from2to];
        case 4:
            values["lbm2amu"] = doConvert(value, 2.731595236297e26);
            values["lbm2g"] = doConvert(value, 453.59237);
            values["lbm2gr"] = doConvert(value, 6999.999999981);
            values["lbm2kg"] = doConvert(value, 0.45359237);
            values["lbm2ug"] = doConvert(value, 453592370);
            values["lbm2mg"] = doConvert(value, 453592.37);
            values["lbm2oz"] = doConvert(value, 16);
            values["lbm2slug"] = QString::number(value / 32.17405);

            return values[from2to];
        case 5:
            values["ug2amu"] = doConvert(value, 602213665167500000);
            values["ug2g"] = doConvert(value, 0.000001);
            values["ug2gr"] = doConvert(value, 0.000015432);
            values["ug2kg"] = doConvert(value, 1e-9);
            values["ug2lbm"] = doConvert(value, 2.204622621849e-9);
            values["ug2mg"] = doConvert(value, 0.001);
            values["ug2oz"] = doConvert(value, 0.000000035);
            values["ug2slug"] =
                QString::number(value * 2.204622621849e-9 / 32.17405);

            return values[from2to];

        case 6:
            values["mg2g"] = doConvert(value, 0.001);
            values["mg2gr"] = doConvert(value, 0.015432358);
            values["mg2kg"] = doConvert(value, 0.000001);
            values["mg2lbm"] = doConvert(value, 0.000002204622621849);
            values["mg2ug"] = doConvert(value, 1e3);
            values["mg2amu"] = doConvert(value, 6.022136651675e20);
            values["mg2oz"] = doConvert(value, 0.000035274);
            values["mg2slug"] =
                QString::number(value * 0.000002204622621849 / 32.17405);

            return values[from2to];

        case 7:
            values["oz2g"] = doConvert(value, 28.349523125);
            values["oz2gr"] = doConvert(value, 437.499999999);
            values["oz2kg"] = doConvert(value, 0.028349523);
            values["oz2lbm"] = doConvert(value, 0.0625);
            values["oz2ug"] = doConvert(value, 28349523.125);
            values["oz2amu"] = doConvert(value, 1.707247023e25);
            values["oz2slug"] = doConvert(value, 0.001942559);
            values["oz2mg"] = doConvert(value, 28349.523125);

            return values[from2to];

        case 8:
            values["slug2amu"] = doConvert(value, 8.78865485e+27);
            values["slug2g"] = doConvert(value, 14.5939 * 1000);
            values["slug2gr"] = doConvert(value, 225218.33989438);
            values["slug2kg"] = doConvert(value, 14.5939);
            values["slug2lbm"] = doConvert(value, 32.17405);
            values["slug2mg"] = doConvert(value, 14.5939 * 1000000);
            values["slug2ug"] = doConvert(value, 14.5939 * 1000000000);
            values["slug2oz"] = doConvert(value, 514.784776903);

            return values[from2to];
        }
        break;
    case MAGNETICFIELDSTRENGTH:
        unitOptions = (QStringList() << "A/m"
                                     << "Oe");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["A/m2Oe"] = doConvert(value, 0.012566371);
            return values[from2to];
        case 1:
            values["Oe2A/m"] = doConvert(value, 79.577471546);
            return values[from2to];
        }
        break;
    case MAGNETICFLUXDENSITY:
        unitOptions = (QStringList() << "gamma"
                                     << "Gs"
                                     << "T");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["gamma2Gs"] = doConvert(value, 0.00001);
            values["gamma2T"] = doConvert(value, 0.000000001);
            return values[from2to];
        case 1:
            values["Gs2gamma"] = doConvert(value, 100000);
            values["Gs2T"] = doConvert(value, 0.0001);
            return values[from2to];
        case 2:
            values["T2Gs"] = doConvert(value, 10000);
            values["T2gamma"] = doConvert(value, 1e9);
            return values[from2to];
        }
        break;
    case POWER:
        unitOptions = (QStringList() << "hpb"
                                     << "Btu/h"
                                     << "cal/s"
                                     << "hpe"
                                     << "ftlb/s"
                                     << "GW"
                                     << "kW"
                                     << "hp"
                                     << "MW"
                                     << "TW"
                                     << "W"
                                     << "dBm"
                                     << "dBW");

        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["hpb2Btu/h"] = doConvert(value, 33471.403350169);
            values["hpb2cal/s"] = doConvert(value, 2342.958822967);
            values["hpb2hpe"] = doConvert(value, 13.149463807);
            values["hpb2ftlb/s"] = doConvert(value, 7235.115903346);
            values["hpb2GW"] = doConvert(value, 0.00000981);
            values["hpb2kW"] = doConvert(value, 9.8095);
            values["hpb2hp"] = doConvert(value, 13.337208255);
            values["hpb2MW"] = doConvert(value, 0.0098095);
            values["hpb2TW"] = doConvert(value, 0.00000001);
            values["hpb2W"] = doConvert(value, 9809.5);
            values["hpb2dBm"] =
                QString::number(convertdBm(value * 9809.5 * 1e3));
            values["hpb2dBW"] = QString::number(convertdBW(value * 9809.5));

            return values[from2to];

        case 1:
            values["Btu/h2hpb"] = doConvert(value, 0.000029876);
            values["Btu/h2cal/s"] = doConvert(value, 0.069998823);
            values["Btu/h2hpe"] = doConvert(value, 0.000392857);
            values["Btu/h2ftlb/s"] = doConvert(value, 0.216158128);
            values["Btu/h2GW"] = doConvert(value, 2.930710702e-10);
            values["Btu/h2kW"] = doConvert(value, 0.000293071);
            values["Btu/h2hp"] = doConvert(value, 0.000398466);
            values["Btu/h2MW"] = doConvert(value, 0.000038392);
            values["Btu/h2TW"] = doConvert(value, 2.930710702e-13);
            values["Btu/h2W"] = doConvert(value, 0.29307107);
            values["Btu/h2dBm"] =
                QString::number(convertdBm(value * 0.29307107 * 1e3));
            values["Btu/h2dBW"] =
                QString::number(convertdBW(value * 0.29307107));

            return values[from2to];

        case 2:
            values["cal/s2hpb"] = doConvert(value, 0.000426811);
            values["cal/s2Btu/h"] = doConvert(value, 14.28595459);
            values["cal/s2hpe"] = doConvert(value, 0.005612332);
            values["cal/s2ftlb/s"] = doConvert(value, 3.088025207);
            values["cal/s2GW"] = doConvert(value, 0.000000004);
            values["cal/s2kW"] = doConvert(value, 0.0041868);
            values["cal/s2hp"] = doConvert(value, 0.005692464);
            values["cal/s2MW"] = doConvert(value, 0.000004187);
            values["cal/s2TW"] = doConvert(value, 4.1868e-12);
            values["cal/s2W"] = doConvert(value, 4.1868);
            values["cal/s2dBm"] =
                QString::number(convertdBm(value * 4.1868 * 1e3));
            values["cal/s2dBW"] = QString::number(convertdBW(value * 4.1868));

            return values[from2to];

        case 3:
            values["hpe2Btu/h"] = doConvert(value, 2545.457658313);
            values["hpe2cal/s"] = doConvert(value, 178.179038884);
            values["hpe2hpb"] = doConvert(value, 0.076048728);
            values["hpe2ftlb/s"] = doConvert(value, 550.221363362);
            values["hpe2GW"] = doConvert(value, 0.000000746);
            values["hpe2kW"] = doConvert(value, 0.746);
            values["hpe2hp"] = doConvert(value, 1.014277727);
            values["hpe2MW"] = doConvert(value, 0.000746);
            values["hpe2TW"] = doConvert(value, 7.46e-10);
            values["hpe2W"] = doConvert(value, 746);
            values["hpe2dBm"] = QString::number(convertdBm(value * 746 * 1e3));
            values["hpe2dBW"] = QString::number(convertdBW(value * 746));

            return values[from2to];

        case 4:
            values["ftlb/s2Btu/h"] = doConvert(value, 4.626242868);
            values["ftlb/s2cal/s"] = doConvert(value, 0.323831554);
            values["ftlb/s2hpe"] = doConvert(value, 0.00181745);
            values["ftlb/s2hpb"] = doConvert(value, 0.000138215);
            values["ftlb/s2GW"] = doConvert(value, 0.000000001);
            values["ftlb/s2kW"] = doConvert(value, 0.001355818);
            values["ftlb/s2hp"] = doConvert(value, 0.001843399);
            values["ftlb/s2MW"] = doConvert(value, 0.000001356);
            values["ftlb/s2TW"] = doConvert(value, 1.355817948e-12);
            values["ftlb/s2W"] = doConvert(value, 1.355817948);
            values["ftlb/s2dBm"] =
                QString::number(convertdBm(value * 1.355817948 * 1e3));
            values["ftlb/s2dBW"] =
                QString::number(convertdBW(value * 1.355817948));

            return values[from2to];

        case 5:
            values["GW2Btu/h"] = doConvert(value, 3412141633.1279);
            values["GW2cal/s"] = doConvert(value, 238845896.6275);
            values["GW2hpe"] = doConvert(value, 1340482.5737265);
            values["GW2ftlb/s"] = doConvert(value, 737562149.27833);
            values["GW2hpb"] = doConvert(value, 101941.99500484);
            values["GW2kW"] = doConvert(value, 1000000);
            values["GW2hp"] = doConvert(value, 1359621.6173039);
            values["GW2MW"] = doConvert(value, 1000);
            values["GW2TW"] = doConvert(value, 0.001);
            values["GW2W"] = doConvert(value, 1000000000);
            values["GW2dBm"] = QString::number(convertdBm(value * 1e9 * 1e3));
            values["GW2dBW"] = QString::number(convertdBW(value * 1e9));

            return values[from2to];

        case 6:
            values["kW2Btu/h"] = doConvert(value, 3412.141633128);
            values["kW2cal/s"] = doConvert(value, 238.845896627);
            values["kW2hpe"] = doConvert(value, 1.340482574);
            values["kW2ftlb/s"] = doConvert(value, 737.562149278);
            values["kW2GW"] = doConvert(value, 0.000001);
            values["kW2hpb"] = doConvert(value, 0.101941995);
            values["kW2hp"] = doConvert(value, 1.359621617);
            values["kW2MW"] = doConvert(value, 0.001);
            values["kW2TW"] = doConvert(value, 0.000000001);
            values["kW2W"] = doConvert(value, 1000);
            values["kW2dBm"] = QString::number(convertdBm(value * 1000 * 1e3));
            values["kW2dBW"] = QString::number(convertdBW(value * 1000));

            return values[from2to];

        case 7:
            values["hp2Btu/h"] = doConvert(value, 2509.625905989);
            values["hp2cal/s"] = doConvert(value, 175.670858412);
            values["hp2hpe"] = doConvert(value, 0.985923257);
            values["hp2ftlb/s"] = doConvert(value, 542.476038842);
            values["hp2GW"] = doConvert(value, 0.000000735);
            values["hp2kW"] = doConvert(value, 0.73549875);
            values["hp2hpb"] = doConvert(value, 0.07497821);
            values["hp2MW"] = doConvert(value, 0.000735499);
            values["hp2TW"] = doConvert(value, 7.3549875e-10);
            values["hp2W"] = doConvert(value, 735.49875);
            values["hp2dBm"] =
                QString::number(convertdBm(value * 735.49875 * 1e3));
            values["hp2dBW"] = QString::number(convertdBW(value * 735.49875));

            return values[from2to];

        case 8:
            values["MW2Btu/h"] = doConvert(value, 3412141.6331279);
            values["MW2cal/s"] = doConvert(value, 238845.8966275);
            values["MW2hpe"] = doConvert(value, 1340.482573727);
            values["MW2ftlb/s"] = doConvert(value, 737562.14927833);
            values["MW2GW"] = doConvert(value, 0.001);
            values["MW2kW"] = doConvert(value, 1000);
            values["MW2hp"] = doConvert(value, 1359.621617304);
            values["MW2hpb"] = doConvert(value, 101.941995005);
            values["MW2TW"] = doConvert(value, 0.000001);
            values["MW2W"] = doConvert(value, 1000000);
            values["MW2dBm"] =
                QString::number(convertdBm(value * 1000000 * 1e3));
            values["MW2dBW"] = QString::number(convertdBW(value * 1000000));

            return values[from2to];

        case 9:
            values["TW2Btu/h"] = doConvert(value, 3.412141633e12);
            values["TW2cal/s"] = doConvert(value, 2.388458966e11);
            values["TW2hpe"] = doConvert(value, 1340482573.7265);
            values["TW2ftlb/s"] = doConvert(value, 2.388458966e11);
            values["TW2GW"] = doConvert(value, 1000);
            values["TW2kW"] = doConvert(value, 1000000000);
            values["TW2hp"] = doConvert(value, 1359621617.3039);
            values["TW2MW"] = doConvert(value, 1000000);
            values["TW2hpb"] = doConvert(value, 101941995.00484);
            values["TW2W"] = doConvert(value, 1e12);
            values["TW2dBm"] = QString::number(convertdBm(value * 1e12 * 1e3));
            values["TW2dBW"] = QString::number(convertdBW(value * 1e12));

            return values[from2to];

        case 10:
            values["W2Btu/h"] = doConvert(value, 3.412141633);
            values["W2cal/s"] = doConvert(value, 0.238845897);
            values["W2hpe"] = doConvert(value, 0.001340483);
            values["W2ftlb/s"] = doConvert(value, 0.737562149);
            values["W2GW"] = doConvert(value, 0.000000001);
            values["W2kW"] = doConvert(value, 0.001);
            values["W2hp"] = doConvert(value, 0.001359622);
            values["W2MW"] = doConvert(value, 0.000001);
            values["W2hpb"] = doConvert(value, 0.000101942);
            values["W2TW"] = doConvert(value, 1e-12);
            values["W2dBm"] = QString::number(convertdBm(value * 1e3));
            values["W2dBW"] = QString::number(convertdBW(value));

            return values[from2to];

        case 11:

            values["dBm2Btu/h"] = QString::number(Pm * 3.412141633);
            values["dBm2cal/s"] = QString::number(Pm * 0.238845897);
            values["dBm2hpe"] = QString::number(Pm * 0.001340483);
            values["dBm2ftlb/s"] = QString::number(Pm * 0.737562149);
            values["dBm2GW"] = QString::number(Pm * 0.000000001);
            values["dBm2kW"] = QString::number(Pm * 0.001);
            values["dBm2hp"] = QString::number(Pm * 0.001359622);
            values["dBm2MW"] = QString::number(Pm * 0.000001);
            values["dBm2hpb"] = QString::number(Pm * 0.000101942);
            values["dBm2TW"] = QString::number(Pm * 1e-12);
            values["dBm2W"] = QString::number(Pm);
            values["dBm2dBW"] = QString::number(convertdBW(Pm));

            return values[from2to];

        case 12:

            values["dBW2Btu/h"] = QString::number(P * 3.412141633);
            values["dBW2cal/s"] = QString::number(P * 0.238845897);
            values["dBW2hpe"] = QString::number(P * 0.001340483);
            values["dBW2ftlb/s"] = QString::number(P * 0.737562149);
            values["dBW2GW"] = QString::number(P * 0.000000001);
            values["dBW2kW"] = QString::number(P * 0.001);
            values["dBW2hp"] = QString::number(P * 0.001359622);
            values["dBW2MW"] = QString::number(P * 0.000001);
            values["dBW2hpb"] = QString::number(P * 0.000101942);
            values["dBW2TW"] = QString::number(P * 1e-12);
            values["dBW2W"] = QString::number(P);
            values["dBW2dBm"] = QString::number(convertdBm(P * 1000));

            return values[from2to];
        }
        break;

    case PRESSURE:
        unitOptions = (QStringList() << "atm"
                                     << "bar"
                                     << "dyn/cm2"
                                     << "ftAgua"
                                     << "hPa"
                                     << "inAgua"
                                     << "MPa"
                                     << "kPa"
                                     << "mbar"
                                     << "mmHg"
                                     << "Pa"
                                     << "psi"
                                     << "Torr");

        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["atm2bar"] = doConvert(value, 1.01325);
            values["atm2dyn/cm2"] = doConvert(value, 1013250);
            values["atm2ftAgua"] = doConvert(value, 33.899524252);
            values["atm2hPa"] = doConvert(value, 1013.25);
            values["atm2inAgua"] = doConvert(value, 406.793746638);
            values["atm2MPa"] = doConvert(value, 0.101325);
            values["atm2kPa"] = doConvert(value, 101.325);
            values["atm2mbar"] = doConvert(value, 1013.25);
            values["atm2mmHg"] = doConvert(value, 760.002100179);
            values["atm2Pa"] = doConvert(value, 101325);
            values["atm2psi"] = doConvert(value, 14.695948775);
            values["atm2Torr"] = doConvert(value, 760);

            return values[from2to];

        case 1:
            values["bar2atm"] = doConvert(value, 0.986923267);
            values["bar2dyn/cm2"] = doConvert(value, 1000000);
            values["bar2ftAgua"] = doConvert(value, 33.456229215);
            values["bar2hPa"] = doConvert(value, 1000);
            values["bar2inAgua"] = doConvert(value, 401.474213311);
            values["bar2MPa"] = doConvert(value, 0.1);
            values["bar2kPa"] = doConvert(value, 100);
            values["bar2mbar"] = doConvert(value, 1000);
            values["bar2mmHg"] = doConvert(value, 750.063755419);
            values["bar2Pa"] = doConvert(value, 100000);
            values["bar2psi"] = doConvert(value, 14.503773773);
            values["bar2Torr"] = doConvert(value, 750.061682704);

            return values[from2to];

        case 2:
            values["dyn/cm22bar"] = doConvert(value, 0.000001);
            values["dyn/cm22atm"] = doConvert(value, 0.000000987);
            values["dyn/cm22ftAgua"] = doConvert(value, 0.000033456);
            values["dyn/cm22hPa"] = doConvert(value, 0.001);
            values["dyn/cm22inAgua"] = doConvert(value, 0.000401474);
            values["dyn/cm22MPa"] = doConvert(value, 0.0000001);
            values["dyn/cm22kPa"] = doConvert(value, 0.0001);
            values["dyn/cm22mbar"] = doConvert(value, 0.001);
            values["dyn/cm22mmHg"] = doConvert(value, 0.000750064);
            values["dyn/cm22Pa"] = doConvert(value, 0.1);
            values["dyn/cm22psi"] = doConvert(value, 0.000014504);
            values["dyn/cm22Torr"] = doConvert(value, 0.000750062);

            return values[from2to];

        case 3:
            values["ftAgua2bar"] = doConvert(value, 0.0298898);
            values["ftAgua2dyn/cm2"] = doConvert(value, 29889.8);
            values["ftAgua2atm"] = doConvert(value, 0.029498939);
            values["ftAgua2hPa"] = doConvert(value, 29.8898);
            values["ftAgua2inAgua"] = doConvert(value, 11.999983941);
            values["ftAgua2MPa"] = doConvert(value, 0.00298898);
            values["ftAgua2kPa"] = doConvert(value, 2.98898);
            values["ftAgua2mbar"] = doConvert(value, 29.8898);
            values["ftAgua2mmHg"] = doConvert(value, 22.419255637);
            values["ftAgua2Pa"] = doConvert(value, 2988.98);
            values["ftAgua2psi"] = doConvert(value, 0.433514897);
            values["ftAgua2Torr"] = doConvert(value, 22.419193684);

            return values[from2to];

        case 4:
            values["hPa2bar"] = doConvert(value, 0.001);
            values["hPa2dyn/cm2"] = doConvert(value, 1000);
            values["hPa2ftAgua"] = doConvert(value, 0.033456229);
            values["hPa2atm"] = doConvert(value, 0.000986923);
            values["hPa2inAgua"] = doConvert(value, 0.401474213);
            values["hPa2MPa"] = doConvert(value, 0.0001);
            values["hPa2kPa"] = doConvert(value, 0.1);
            values["hPa2mbar"] = doConvert(value, 1);
            values["hPa2mmHg"] = doConvert(value, 0.750063755);
            values["hPa2Pa"] = doConvert(value, 100);
            values["hPa2psi"] = doConvert(value, 0.014503774);
            values["hPa2Torr"] = doConvert(value, 0.750061683);

            return values[from2to];

        case 5:
            values["inAgua2bar"] = doConvert(value, 0.00249082);
            values["inAgua2dyn/cm2"] = doConvert(value, 2490.82);
            values["inAgua2ftAgua"] = doConvert(value, 0.083333445);
            values["inAgua2hPa"] = doConvert(value, 2.49082);
            values["inAgua2atm"] = doConvert(value, 0.002458248);
            values["inAgua2MPa"] = doConvert(value, 0.000249082);
            values["inAgua2kPa"] = doConvert(value, 0.249082);
            values["inAgua2mbar"] = doConvert(value, 2.49082);
            values["inAgua2mmHg"] = doConvert(value, 1.868273803);
            values["inAgua2Pa"] = doConvert(value, 249.082);
            values["inAgua2psi"] = doConvert(value, 0.03612629);
            values["inAgua2Torr"] = doConvert(value, 1.868268641);

            return values[from2to];

        case 6:
            values["MPa2bar"] = doConvert(value, 10);
            values["MPa2dyn/cm2"] = doConvert(value, 10000000);
            values["MPa2ftAgua"] = doConvert(value, 334.562292153);
            values["MPa2hPa"] = doConvert(value, 10000);
            values["MPa2inAgua"] = doConvert(value, 4014.742133113);
            values["MPa2atm"] = doConvert(value, 9.869232667);
            values["MPa2kPa"] = doConvert(value, 1000);
            values["MPa2mbar"] = doConvert(value, 10000);
            values["MPa2mmHg"] = doConvert(value, 7500.637554192);
            values["MPa2Pa"] = doConvert(value, 1000000);
            values["MPa2psi"] = doConvert(value, 145.03773773);
            values["MPa2Torr"] = doConvert(value, 7500.61682704);

            return values[from2to];

        case 7:
            values["kPa2bar"] = doConvert(value, 0.01);
            values["kPa2dyn/cm2"] = doConvert(value, 10000);
            values["kPa2ftAgua"] = doConvert(value, 0.334562292);
            values["kPa2hPa"] = doConvert(value, 10);
            values["kPa2inAgua"] = doConvert(value, 4.014742133);
            values["kPa2MPa"] = doConvert(value, 0.001);
            values["kPa2atm"] = doConvert(value, 0.009869233);
            values["kPa2mbar"] = doConvert(value, 10);
            values["kPa2mmHg"] = doConvert(value, 7.500637554);
            values["kPa2Pa"] = doConvert(value, 1000);
            values["kPa2psi"] = doConvert(value, 0.145037738);
            values["kPa2Torr"] = doConvert(value, 7.500616827);

            return values[from2to];

        case 8:
            values["mbar2bar"] = doConvert(value, 0.001);
            values["mbar2dyn/cm2"] = doConvert(value, 1000);
            values["mbar2ftAgua"] = doConvert(value, 0.033456229);
            values["mbar2hPa"] = doConvert(value, 1);
            values["mbar2inAgua"] = doConvert(value, 0.401474213);
            values["mbar2MPa"] = doConvert(value, 0.0001);
            values["mbar2kPa"] = doConvert(value, 0.1);
            values["mbar2atm"] = doConvert(value, 0.000986923);
            values["mbar2mmHg"] = doConvert(value, 0.750063755);
            values["mbar2Pa"] = doConvert(value, 100);
            values["mbar2psi"] = doConvert(value, 0.014503774);
            values["mbar2Torr"] = doConvert(value, 0.750061683);

            return values[from2to];

        case 9:
            values["mmHg2bar"] = doConvert(value, 0.00133322);
            values["mmHg2dyn/cm2"] = doConvert(value, 1333.22);
            values["mmHg2ftAgua"] = doConvert(value, 0.044604514);
            values["mmHg2hPa"] = doConvert(value, 1.33322);
            values["mmHg2inAgua"] = doConvert(value, 0.535253451);
            values["mmHg2MPa"] = doConvert(value, 0.000133322);
            values["mmHg2kPa"] = doConvert(value, 0.133322);
            values["mmHg2mbar"] = doConvert(value, 1.33322);
            values["mmHg2atm"] = doConvert(value, 0.001315786);
            values["mmHg2Pa"] = doConvert(value, 133.322);
            values["mmHg2psi"] = doConvert(value, 0.019336721);
            values["mmHg2Torr"] = doConvert(value, 0.999997237);

            return values[from2to];

        case 10:
            values["Pa2bar"] = doConvert(value, 0.00001);
            values["Pa2dyn/cm2"] = doConvert(value, 10);
            values["Pa2ftAgua"] = doConvert(value, 0.000334562);
            values["Pa2hPa"] = doConvert(value, 0.01);
            values["Pa2inAgua"] = doConvert(value, 0.004014742);
            values["Pa2MPa"] = doConvert(value, 0.000001);
            values["Pa2kPa"] = doConvert(value, 0.001);
            values["Pa2mbar"] = doConvert(value, 0.01);
            values["Pa2mmHg"] = doConvert(value, 0.007500638);
            values["Pa2atm"] = doConvert(value, 0.000009869);
            values["Pa2psi"] = doConvert(value, 0.000145038);
            values["Pa2Torr"] = doConvert(value, 0.007500617);

            return values[from2to];

        case 11:
            values["psi2bar"] = doConvert(value, 0.068947573);
            values["psi2dyn/cm2"] = doConvert(value, 68947.572931783);
            values["psi2ftAgua"] = doConvert(value, 2.306725804);
            values["psi2hPa"] = doConvert(value, 68.947572932);
            values["psi2inAgua"] = doConvert(value, 27.680672603);
            values["psi2MPa"] = doConvert(value, 0.006894757);
            values["psi2kPa"] = doConvert(value, 6.894757293);
            values["psi2mbar"] = doConvert(value, 68.947572932);
            values["psi2mmHg"] = doConvert(value, 51.71507548);
            values["psi2Pa"] = doConvert(value, 6894.757293178);
            values["psi2atm"] = doConvert(value, 0.068045964);
            values["psi2Torr"] = doConvert(value, 51.714932572);

            return values[from2to];

        case 12:
            values["Torr2bar"] = doConvert(value, 0.001333224);
            values["Torr2dyn/cm2"] = doConvert(value, 1333.223684211);
            values["Torr2ftAgua"] = doConvert(value, 0.044604637);
            values["Torr2hPa"] = doConvert(value, 1.333223684);
            values["Torr2inAgua"] = doConvert(value, 0.53525493);
            values["Torr2MPa"] = doConvert(value, 0.000133322);
            values["Torr2kPa"] = doConvert(value, 0.133322368);
            values["Torr2mbar"] = doConvert(value, 1.333223684);
            values["Torr2mmHg"] = doConvert(value, 1.000002763);
            values["Torr2Pa"] = doConvert(value, 133.322368421);
            values["Torr2psi"] = doConvert(value, 0.019336775);
            values["Torr2atm"] = doConvert(value, 0.001315789);

            return values[from2to];
        }
        break;

    case SPEED:
        unitOptions = (QStringList() << "ft/s"
                                     << "km/h"
                                     << "knot"
                                     << "mach"
                                     << "mph"
                                     << "m/s");

        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["ft/s2km/h"] = doConvert(value, 1.09728);
            values["ft/s2knot"] = doConvert(value, 0.5924838012959);
            values["ft/s2mach"] = doConvert(value, 0.000887078);
            values["ft/s2mph"] = doConvert(value, 0.68181818181818);
            values["ft/s2m/s"] = doConvert(value, 0.3048);

            return values[from2to];

        case 1:
            values["km/h2ft/s"] = doConvert(value, 0.91134441528142);
            values["km/h2knot"] = doConvert(value, 0.53995680345572);
            values["km/h2mach"] = doConvert(value, 0.000808434);
            values["km/h2mph"] = doConvert(value, 0.62137119223733);
            values["km/h2m/s"] = doConvert(value, 0.27777777777778);

            return values[from2to];

        case 2:
            values["knot2km/h"] = doConvert(value, 1.852);
            values["knot2ft/s"] = doConvert(value, 1.6878098571012);
            values["knot2mach"] = doConvert(value, 0.001497219);
            values["knot2mph"] = doConvert(value, 1.1507794480235);
            values["knot2m/s"] = doConvert(value, 0.51444444444444);

            return values[from2to];

        case 3:
            values["mach2km/h"] = doConvert(value, 1236.96);
            values["mach2knot"] = doConvert(value, 667.904967603);
            values["mach2ft/s"] = doConvert(value, 1127.296587927);
            values["mach2mph"] = doConvert(value, 768.61130995);
            values["mach2m/s"] = doConvert(value, 343.6);

            return values[from2to];

        case 4:
            values["mph2km/h"] = doConvert(value, 1.609344);
            values["mph2knot"] = doConvert(value, 0.868976242);
            values["mph2mach"] = doConvert(value, 0.001301048);
            values["mph2ft/s"] = doConvert(value, 1.466666667);
            values["mph2m/s"] = doConvert(value, 0.44704);

            return values[from2to];

        case 5:
            values["m/s2km/h"] = doConvert(value, 3.6);
            values["m/s2knot"] = doConvert(value, 1.943844492);
            values["m/s2mach"] = doConvert(value, 0.002910361);
            values["m/s2mph"] = doConvert(value, 2.2369362920544);
            values["m/s2ft/s"] = doConvert(value, 3.280839895);

            return values[from2to];
        }
        break;

    case TEMPERATURE:
        unitOptions = (QStringList() << "C"
                                     << "F"
                                     << "K"
                                     << "R");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["C2F"] = QString::number(value * 1.8 + 32);
            values["C2K"] = QString::number(value + 273.15);
            values["C2R"] = QString::number((value + 273.15) * 1.8);

            return values[from2to];
        case 1:
            values["F2C"] = QString::number((value - 32) * 0.5555555555555556);
            values["F2K"] =
                QString::number((value + 459.67) * 0.5555555555555556);
            values["F2R"] = QString::number(value + 459.67);

            return values[from2to];
        case 2:
            values["K2C"] = QString::number(value - 273.15);
            values["K2F"] = QString::number(value * 1.8 - 459.67);
            values["K2R"] = doConvert(value, 1.8);

            return values[from2to];
        case 3:
            values["R2C"] =
                QString::number((value - 491.67) * 0.5555555555555556);
            values["R2F"] = QString::number(value - 459.67);
            values["R2K"] = doConvert(value, 0.5555555555555556);

            return values[from2to];
        }
        break;

    case TIME:
        unitOptions = (QStringList() << "day"
                                     << "hr"
                                     << "us"
                                     << "min"
                                     << "ms"
                                     << "ns"
                                     << "s"
                                     << "yr"
                                     << "wk");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["day2hr"] = doConvert(value, 24);
            values["day2us"] = doConvert(value, 8.64e10);
            values["day2min"] = doConvert(value, 1440);
            values["day2ms"] = doConvert(value, 86400000);
            values["day2ns"] = doConvert(value, 8.64e+13);
            values["day2s"] = doConvert(value, 86400);
            values["day2yr"] = doConvert(value, 0.0027397260273973);
            values["day2wk"] = doConvert(value, 0.14285714285714);

            return values[from2to];

        case 1:
            values["hr2day"] = doConvert(value, 0.041666666666667);
            values["hr2us"] = doConvert(value, 3.6e9);
            values["hr2min"] = doConvert(value, 60);
            values["hr2ms"] = doConvert(value, 3600000);
            values["hr2ns"] = doConvert(value, 3.6e12);
            values["hr2s"] = doConvert(value, 3600);
            values["hr2yr"] = doConvert(value, 0.00011415525114155);
            values["hr2wk"] = doConvert(value, 0.005952380952381);

            return values[from2to];

        case 2:
            values["us2hr"] = doConvert(value, 2.777777778e-10);
            values["us2day"] = doConvert(value, 1.157407407e-11);
            values["us2min"] = doConvert(value, 0.000000017);
            values["us2ms"] = doConvert(value, 0.001);
            values["us2ns"] = doConvert(value, 1000);
            values["us2s"] = doConvert(value, 0.000001);
            values["us2yr"] = doConvert(value, 3.170979198e-14);
            values["us2wk"] = doConvert(value, 1.653439153e-12);

            return values[from2to];

        case 3:
            values["min2hr"] = doConvert(value, 0.016666667);
            values["min2us"] = doConvert(value, 60000000);
            values["min2day"] = doConvert(value, 0.000694444);
            values["min2ms"] = doConvert(value, 60000);
            values["min2ns"] = doConvert(value, 6e10);
            values["min2s"] = doConvert(value, 60);
            values["min2yr"] = doConvert(value, 0.000001903);
            values["min2wk"] = doConvert(value, 0.000099206);

            return values[from2to];

        case 4:
            values["ms2hr"] = doConvert(value, 0.000000278);
            values["ms2us"] = doConvert(value, 1000);
            values["ms2min"] = doConvert(value, 0.000016667);
            values["ms2day"] = doConvert(value, 0.000000012);
            values["ms2ns"] = doConvert(value, 1000000);
            values["ms2s"] = doConvert(value, 0.001);
            values["ms2yr"] = doConvert(value, 3.170979198e-11);
            values["ms2wk"] = doConvert(value, 0.000000002);

            return values[from2to];

        case 5:
            values["ns2hr"] = doConvert(value, 2.777777778e-13);
            values["ns2us"] = doConvert(value, 0.001);
            values["ns2min"] = doConvert(value, 1.666666667e-11);
            values["ns2ms"] = doConvert(value, 0.000001);
            values["ns2day"] = doConvert(value, 1.157407407e-14);
            values["ns2s"] = doConvert(value, 0.000000001);
            values["ns2yr"] = doConvert(value, 3.170979198e-17);
            values["ns2wk"] = doConvert(value, 1.653439153e-15);

            return values[from2to];

        case 6:
            values["s2hr"] = doConvert(value, 0.000277778);
            values["s2us"] = doConvert(value, 1000000);
            values["s2min"] = doConvert(value, 0.016666667);
            values["s2ms"] = doConvert(value, 1000);
            values["s2ns"] = doConvert(value, 1000000000);
            values["s2day"] = doConvert(value, 0.000011574);
            values["s2yr"] = doConvert(value, 0.000000032);
            values["s2wk"] = doConvert(value, 0.000001653);

            return values[from2to];

        case 7:
            values["yr2hr"] = doConvert(value, 8760);
            values["yr2us"] = doConvert(value, 3.1536e13);
            values["yr2min"] = doConvert(value, 525600);
            values["yr2ms"] = doConvert(value, 3.1536e13);
            values["yr2ns"] = doConvert(value, 3.1536e16);
            values["yr2s"] = doConvert(value, 31536000);
            values["yr2day"] = doConvert(value, 365);
            values["yr2wk"] = doConvert(value, 52.142857142857);

            return values[from2to];

        case 8:
            values["wk2hr"] = doConvert(value, 168);
            values["wk2us"] = doConvert(value, 6.048e11);
            values["wk2min"] = doConvert(value, 10080);
            values["wk2ms"] = doConvert(value, 604800000);
            values["wk2ns"] = doConvert(value, 6.048e14);
            values["wk2s"] = doConvert(value, 604800);
            values["wk2yr"] = doConvert(value, 0.019178082);
            values["wk2day"] = doConvert(value, 7);

            return values[from2to];
        }
        break;

    case TORQUE:
        unitOptions = (QStringList() << "dyn-cm"
                                     << "dyn-m"
                                     << "gf-m"
                                     << "kgf-m"
                                     << "N-cm"
                                     << "N-m"
                                     << "ozf-in"
                                     << "lbf-ft"
                                     << "lbf-in");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["dyn-cm2dyn-m"] = doConvert(value, 0.01);
            values["dyn-cm2gf-m"] = doConvert(value, 0.001019716);
            values["dyn-cm2kgf-m"] = doConvert(value, 0.00000001);
            values["dyn-cm2N-cm"] = doConvert(value, 0.00001);
            values["dyn-cm2N-m"] = doConvert(value, 0.0000001);
            values["dyn-cm2ozf-in"] = doConvert(value, 0.000014161);
            values["dyn-cm2lbf-ft"] = doConvert(value, 0.000000074);
            values["dyn-cm2lbf-in"] = doConvert(value, 0.000000885);

            return values[from2to];

        case 1:
            values["dyn-m2dyn-cm"] = doConvert(value, 100);
            values["dyn-m2gf-m"] = doConvert(value, 0.101971621);
            values["dyn-m2kgf-m"] = doConvert(value, 0.00000102);
            values["dyn-m2N-cm"] = doConvert(value, 0.001);
            values["dyn-m2N-m"] = doConvert(value, 0.00001);
            values["dyn-m2ozf-in"] = doConvert(value, 0.001416119);
            values["dyn-m2lbf-ft"] = doConvert(value, 0.000007376);
            values["dyn-m2lbf-in"] = doConvert(value, 0.000088507);

            return values[from2to];

        case 2:
            values["gf-m2dyn-m"] = doConvert(value, 980.665);
            values["gf-m2dyn-cm"] = doConvert(value, 98066.5);
            values["gf-m2kgf-m"] = doConvert(value, 0.001);
            values["gf-m2N-cm"] = doConvert(value, 0.980665);
            values["gf-m2N-m"] = doConvert(value, 0.00980665);
            values["gf-m2ozf-in"] = doConvert(value, 1.388738623);
            values["gf-m2lbf-ft"] = doConvert(value, 0.007233014);
            values["gf-m2lbf-in"] = doConvert(value, 0.086796163);

            return values[from2to];

        case 3:
            values["kgf-m2dyn-m"] = doConvert(value, 980665);
            values["kgf-m2gf-m"] = doConvert(value, 1000);
            values["kgf-m2dyn-cm"] = doConvert(value, 98066500);
            values["kgf-m2N-cm"] = doConvert(value, 980.665);
            values["kgf-m2N-m"] = doConvert(value, 9.80665);
            values["kgf-m2ozf-in"] = doConvert(value, 1388.738622898);
            values["kgf-m2lbf-ft"] = doConvert(value, 7.233013576);
            values["kgf-m2lbf-in"] = doConvert(value, 86.796162907);

            return values[from2to];

        case 4:
            values["N-cm2dyn-m"] = doConvert(value, 1000);
            values["N-cm2gf-m"] = doConvert(value, 1.019716213);
            values["N-cm2kgf-m"] = doConvert(value, 0.001019716);
            values["N-cm2dyn-cm"] = doConvert(value, 100000);
            values["N-cm2N-m"] = doConvert(value, 0.01);
            values["N-cm2ozf-in"] = doConvert(value, 1.416119289);
            values["N-cm2lbf-ft"] = doConvert(value, 0.007375621);
            values["N-cm2lbf-in"] = doConvert(value, 0.088507455);

            return values[from2to];

        case 5:
            values["N-m2dyn-m"] = doConvert(value, 100000);
            values["N-m2gf-m"] = doConvert(value, 101.971621298);
            values["N-m2kgf-m"] = doConvert(value, 0.101971621);
            values["N-m2N-cm"] = doConvert(value, 100);
            values["N-m2dyn-cm"] = doConvert(value, 10000000);
            values["N-m2ozf-in"] = doConvert(value, 141.611928936);
            values["N-m2lbf-ft"] = doConvert(value, 0.737562121);
            values["N-m2lbf-in"] = doConvert(value, 8.850745454);

            return values[from2to];

        case 6:
            values["ozf-in2dyn-m"] = doConvert(value, 706.1552);
            values["ozf-in2gf-m"] = doConvert(value, 0.720077906);
            values["ozf-in2kgf-m"] = doConvert(value, 0.000720078);
            values["ozf-in2N-cm"] = doConvert(value, 0.7061552);
            values["ozf-in2N-m"] = doConvert(value, 0.007061552);
            values["ozf-in2dyn-cm"] = doConvert(value, 70615.52);
            values["ozf-in2lbf-ft"] = doConvert(value, 0.005208333);
            values["ozf-in2lbf-in"] = doConvert(value, 0.062499999);

            return values[from2to];

        case 7:
            values["lbf-ft2dyn-m"] = doConvert(value, 135581.8);
            values["lbf-ft2gf-m"] = doConvert(value, 138.254959645);
            values["lbf-ft2kgf-m"] = doConvert(value, 0.13825496);
            values["lbf-ft2N-cm"] = doConvert(value, 135.5818);
            values["lbf-ft2N-m"] = doConvert(value, 1.355818);
            values["lbf-ft2ozf-in"] = doConvert(value, 192.000002266);
            values["lbf-ft2dyn-cm"] = doConvert(value, 13558180);
            values["lbf-ft2lbf-in"] = doConvert(value, 12);

            return values[from2to];

        case 8:
            values["lbf-in2dyn-m"] = doConvert(value, 11298.483333333);
            values["lbf-in2gf-m"] = doConvert(value, 11.521246637);
            values["lbf-in2kgf-m"] = doConvert(value, 0.011521247);
            values["lbf-in2N-cm"] = doConvert(value, 11.298483333);
            values["lbf-in2N-m"] = doConvert(value, 0.112984833);
            values["lbf-in2ozf-in"] = doConvert(value, 16.000000189);
            values["lbf-in2lbf-ft"] = doConvert(value, 0.083333333);
            values["lbf-in2dyn-cm"] = doConvert(value, 1129848.3333333);

            return values[from2to];
        }
        break;

    case VOLUME:
        unitOptions = (QStringList() << "cl"
                                     << "cm3"
                                     << "f3"
                                     << "in3"
                                     << "km3"
                                     << "m3"
                                     << "mi3"
                                     << "yd3"
                                     << "l"
                                     << "ml"
                                     << "galuk"
                                     << "gal"
                                     << "oz"
                                     << "qt"
                                     << "mm3");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["cl2cm3"] = doConvert(value, 10);
            values["cl2f3"] = doConvert(value, 0.000353147);
            values["cl2in3"] = doConvert(value, 0.610237441);
            values["cl2km3"] = doConvert(value, 1e-14);
            values["cl2m3"] = doConvert(value, 0.00001);
            values["cl2mi3"] = doConvert(value, 2.399127586e-15);
            values["cl2yd3"] = doConvert(value, 0.00001308);
            values["cl2l"] = doConvert(value, 0.01);
            values["cl2ml"] = doConvert(value, 10);
            values["cl2galuk"] = doConvert(value, 0.0021996923465436);
            values["cl2gal"] = doConvert(value, 0.002641721);
            values["cl2oz"] = doConvert(value, 0.338140227);
            values["cl2qt"] = doConvert(value, 0.010566882);
            values["cl2mm3"] = doConvert(value, 10000);

            return values[from2to];

        case 1:
            values["cm32cl"] = doConvert(value, 0.1);
            values["cm32f3"] = doConvert(value, 0.000035315);
            values["cm32in3"] = doConvert(value, 0.061023744);
            values["cm32km3"] = doConvert(value, 1e-15);
            values["cm32m3"] = doConvert(value, 0.000001);
            values["cm32mi3"] = doConvert(value, 2.399127586e-16);
            values["cm32yd3"] = doConvert(value, 0.000001308);
            values["cm32l"] = doConvert(value, 0.001);
            values["cm32ml"] = doConvert(value, 1);
            values["cm32galuk"] = doConvert(value, 0.00021996923465436);
            values["cm32gal"] = doConvert(value, 0.000264172);
            values["cm32oz"] = doConvert(value, 0.033814023);
            values["cm32qt"] = doConvert(value, 0.001056688);
            values["cm32mm3"] = doConvert(value, 1000);

            return values[from2to];

        case 2:
            values["f32cm3"] = doConvert(value, 28316.846592);
            values["f32cl"] = doConvert(value, 2831.6846592);
            values["f32in3"] = doConvert(value, 1728);
            values["f32km3"] = doConvert(value, 2.831684659e-11);
            values["f32m3"] = doConvert(value, 0.028316847);
            values["f32mi3"] = doConvert(value, 6.79357278e-12);
            values["f32yd3"] = doConvert(value, 0.037037037);
            values["f32l"] = doConvert(value, 28.316846592);
            values["f32ml"] = doConvert(value, 28316.846592);
            values["f32galuk"] = doConvert(value, 6.228835072667);
            values["f32gal"] = doConvert(value, 7.480519481);
            values["f32oz"] = doConvert(value, 957.506493506);
            values["f32qt"] = doConvert(value, 29.922077922);
            values["f32mm3"] = doConvert(value, 28316846.592);

            return values[from2to];

        case 3:
            values["in32cm3"] = doConvert(value, 16.387064);
            values["in32f3"] = doConvert(value, 0.000578704);
            values["in32cl"] = doConvert(value, 1.6387064);
            values["in32km3"] = doConvert(value, 1.6387064e-14);
            values["in32m3"] = doConvert(value, 0.000016387);
            values["in32mi3"] = doConvert(value, 3.931465729e-15);
            values["in32yd3"] = doConvert(value, 0.000021433);
            values["in32l"] = doConvert(value, 0.016387064);
            values["in32ml"] = doConvert(value, 16.387064);
            values["in32galuk"] = doConvert(value, 0.0036046499263119);
            values["in32gal"] = doConvert(value, 0.004329004);
            values["in32oz"] = doConvert(value, 0.554112554);
            values["in32qt"] = doConvert(value, 0.017316017);
            values["in32mm3"] = doConvert(value, 16387.064);

            return values[from2to];

        case 4:
            values["km32cm3"] = doConvert(value, 1e15);
            values["km32f3"] = doConvert(value, 3.531466672e10);
            values["km32in3"] = doConvert(value, 6.102374409e13);
            values["km32cl"] = doConvert(value, 1e14);
            values["km32m3"] = doConvert(value, 1000000000);
            values["km32mi3"] = doConvert(value, 0.239912759);
            values["km32yd3"] = doConvert(value, 1307950619.3144);
            values["km32l"] = doConvert(value, 1e12);
            values["km32ml"] = doConvert(value, 1e15);
            values["km32galuk"] = doConvert(value, 219969248299.09);
            values["km32gal"] = doConvert(value, 2.641720524e11);
            values["km32oz"] = doConvert(value, 3.38140227e13);
            values["km32qt"] = doConvert(value, 1.056688209e12);
            values["km32mm3"] = doConvert(value, 1e18);

            return values[from2to];

        case 5:
            values["m32cm3"] = doConvert(value, 1000000);
            values["m32f3"] = doConvert(value, 35.314666721);
            values["m32in3"] = doConvert(value, 61023.744094732);
            values["m32km3"] = doConvert(value, 0.000000001);
            values["m32cl"] = doConvert(value, 100000);
            values["m32mi3"] = doConvert(value, 2.399127586e-10);
            values["m32yd3"] = doConvert(value, 1.307950619);
            values["m32l"] = doConvert(value, 1000);
            values["m32ml"] = doConvert(value, 1000000);
            values["m32galuk"] = doConvert(value, 219.96923465436);
            values["m32gal"] = doConvert(value, 264.172052358);
            values["m32oz"] = doConvert(value, 33814.022701843);
            values["m32qt"] = doConvert(value, 1056.688209433);
            values["m32mm3"] = doConvert(value, 1000000000.0);

            return values[from2to];

        case 6:
            values["mi32cm3"] = doConvert(value, 4.168181825e15);
            values["mi32f3"] = doConvert(value, 1.47197952e11);
            values["mi32in3"] = doConvert(value, 2.543580611e14);
            values["mi32km3"] = doConvert(value, 4.168181825);
            values["mi32m3"] = doConvert(value, 4168181825.4406);
            values["mi32cl"] = doConvert(value, 4.168181825e14);
            values["mi32yd3"] = doConvert(value, 5451776000);
            values["mi32l"] = doConvert(value, 4.168181825e12);
            values["mi32ml"] = doConvert(value, 4.168181825e15);
            values["mi32galuk"] = doConvert(value, 916871826791.47);
            values["mi32gal"] = doConvert(value, 1.101117147e12);
            values["mi32oz"] = doConvert(value, 1.409429949e14);
            values["mi32qt"] = doConvert(value, 4.40446859e12);
            values["mi32mm3"] = doConvert(value, 4.168181825e18);

            return values[from2to];

        case 7:
            values["yd32cm3"] = doConvert(value, 764554.857984);
            values["yd32f3"] = doConvert(value, 27);
            values["yd32in3"] = doConvert(value, 46656);
            values["yd32km3"] = doConvert(value, 7.64554858e-10);
            values["yd32m3"] = doConvert(value, 0.764554858);
            values["yd32mi3"] = doConvert(value, 1.834264651e-10);
            values["yd32cl"] = doConvert(value, 76455.4857984);
            values["yd32l"] = doConvert(value, 764.554857984);
            values["yd32ml"] = doConvert(value, 764554.857984);
            values["yd32galuk"] = doConvert(value, 168.17854696201);
            values["yd32gal"] = doConvert(value, 201.974025974);
            values["yd32oz"] = doConvert(value, 25852.675324675);
            values["yd32qt"] = doConvert(value, 807.896103896);
            values["yd32mm3"] = doConvert(value, 764554857.984);

            return values[from2to];

        case 8:
            values["l2cm3"] = doConvert(value, 1000);
            values["l2f3"] = doConvert(value, 0.035314667);
            values["l2in3"] = doConvert(value, 61.023744095);
            values["l2km3"] = doConvert(value, 1e-12);
            values["l2m3"] = doConvert(value, 0.001);
            values["l2mi3"] = doConvert(value, 2.399127586e-13);
            values["l2yd3"] = doConvert(value, 0.001307951);
            values["l2cl"] = doConvert(value, 100);
            values["l2ml"] = doConvert(value, 1000);
            values["l2galuk"] = doConvert(value, 0.21996923465436);
            values["l2gal"] = doConvert(value, 0.264172052);
            values["l2oz"] = doConvert(value, 33.814022702);
            values["l2qt"] = doConvert(value, 1.056688209);
            values["l2mm3"] = doConvert(value, 1000000);

            return values[from2to];

        case 9:
            values["ml2cm3"] = doConvert(value, 1);
            values["ml2f3"] = doConvert(value, 0.000035315);
            values["ml2in3"] = doConvert(value, 0.061023744);
            values["ml2km3"] = doConvert(value, 1e-15);
            values["ml2m3"] = doConvert(value, 0.000001);
            values["ml2mi3"] = doConvert(value, 2.399127586e-16);
            values["ml2yd3"] = doConvert(value, 0.000001308);
            values["ml2l"] = doConvert(value, 0.001);
            values["ml2cl"] = doConvert(value, 0.1);
            values["ml2galuk"] = doConvert(value, 0.00021996923465436);
            values["ml2gal"] = doConvert(value, 0.000264172);
            values["ml2oz"] = doConvert(value, 0.033814023);
            values["ml2qt"] = doConvert(value, 0.001056688);
            values["ml2mm3"] = doConvert(value, 1000);

            return values[from2to];

        case 10:
            values["galuk2cm3"] = doConvert(value, 4546.0902819948);
            values["galuk2f3"] = doConvert(value, 0.16054366319444);
            values["galuk2in3"] = doConvert(value, 277.41945);
            values["galuk2km3"] = doConvert(value, 0.00000000000454609);
            values["galuk2m3"] = doConvert(value, 0.0045460902819948);
            values["galuk2mi3"] = doConvert(value, 1.0e-12);
            values["galuk2yd3"] = doConvert(value, 0.0059460615997942);
            values["galuk2l"] = doConvert(value, 4.5460902819948);
            values["galuk2ml"] = doConvert(value, 4546.0902819948);
            values["galuk2cl"] = doConvert(value, 454.60902819948);
            values["galuk2oz"] = doConvert(value, 153.7216);
            values["galuk2qt"] = doConvert(value, 4.8038);
            values["galuk2mm3"] = doConvert(value, 4546090.2819948);
            values["galuk2gal"] = doConvert(value, 1.20095);

            return values[from2to];

        case 11:
            values["gal2cm3"] = doConvert(value, 3785.411784);
            values["gal2f3"] = doConvert(value, 0.133680556);
            values["gal2in3"] = doConvert(value, 231);
            values["gal2km3"] = doConvert(value, 3.785411784e-12);
            values["gal2m3"] = doConvert(value, 0.003785412);
            values["gal2mi3"] = doConvert(value, 9.081685835e-13);
            values["gal2yd3"] = doConvert(value, 0.004951132);
            values["gal2l"] = doConvert(value, 3.785411784);
            values["gal2ml"] = doConvert(value, 3785.411784);
            values["gal2cl"] = doConvert(value, 378.5411784);
            values["gal2oz"] = doConvert(value, 128);
            values["gal2qt"] = doConvert(value, 4);
            values["gal2mm3"] = doConvert(value, 3785411.784);
            values["gal2galuk"] = doConvert(value, 0.83267413297806);

            return values[from2to];

        case 12:
            values["oz2cm3"] = doConvert(value, 29.573529563);
            values["oz2f3"] = doConvert(value, 0.001044379);
            values["oz2in3"] = doConvert(value, 1.8046875);
            values["oz2km3"] = doConvert(value, 2.957352956e-14);
            values["oz2m3"] = doConvert(value, 0.000029574);
            values["oz2mi3"] = doConvert(value, 7.095067058e-15);
            values["oz2yd3"] = doConvert(value, 0.000038681);
            values["oz2l"] = doConvert(value, 0.02957353);
            values["oz2ml"] = doConvert(value, 29.573529563);
            values["oz2galuk"] = doConvert(value, 0.0065052666638911);
            values["oz2gal"] = doConvert(value, 0.0078125);
            values["oz2cl"] = doConvert(value, 2.957352956);
            values["oz2qt"] = doConvert(value, 0.03125);
            values["oz2mm3"] = doConvert(value, 29573.5295625);

            return values[from2to];

        case 13:
            values["qt2cm3"] = doConvert(value, 946.352946);
            values["qt2f3"] = doConvert(value, 0.033420139);
            values["qt2in3"] = doConvert(value, 57.75);
            values["qt2km3"] = doConvert(value, 9.46352946e-13);
            values["qt2m3"] = doConvert(value, 0.000946353);
            values["qt2mi3"] = doConvert(value, 2.270421459e-13);
            values["qt2yd3"] = doConvert(value, 0.001237783);
            values["qt2l"] = doConvert(value, 0.946352946);
            values["qt2ml"] = doConvert(value, 946.352946);
            values["qt2galuk"] = doConvert(value, 0.20816853324452);
            values["qt2gal"] = doConvert(value, 0.25);
            values["qt2oz"] = doConvert(value, 32);
            values["qt2cl"] = doConvert(value, 94.6352946);
            values["qt2mm3"] = doConvert(value, 946352.946);

            return values[from2to];

        case 14:
            values["mm32cm3"] = doConvert(value, 0.001);
            values["mm32f3"] = doConvert(value, 0.000000035);
            values["mm32in3"] = doConvert(value, 0.000061024);
            values["mm32km3"] = doConvert(value, 1e-18);
            values["mm32m3"] = doConvert(value, 0.000000001);
            values["mm32mi3"] = doConvert(value, 2.399127586e-19);
            values["mm32yd3"] = doConvert(value, 0.000000001);
            values["mm32l"] = doConvert(value, 0.000001);
            values["mm32ml"] = doConvert(value, 0.001);
            values["mm32galuk"] = doConvert(value, 0.00000021996923465436);
            values["mm32gal"] = doConvert(value, 0.000000264);
            values["mm32oz"] = doConvert(value, 0.000033814);
            values["mm32cl"] = doConvert(value, 0.0001);
            values["mm32qt"] = doConvert(value, 0.000001057);

            return values[from2to];
        }
        break;
    default:
        break;
    }
    return QString::number(0.0);
}

QString Converter::convert2Numbers(QString from, QString to,
                                   QString value_) const
{
    QStringList unitOptions;
    QString unit = from;
    QString from2to = from + "2" + to;
    QMap<QString, QString> values;
    bool ok;
    int value;
    unitOptions = (QStringList() << "bin"
                                 << "dec"
                                 << "hex"
                                 << "oct");
    switch (unitOptions.indexOf(unit)) {
    case 0:
        value = value_.toLongLong(&ok, 2);
        if (!ok) {
            return QString("invalid input");
        } else {
            values["bin2dec"] = QString::number(value, 10);
            values["bin2hex"] = QString::number(value, 16);
            values["bin2oct"] = QString::number(value, 8);
        }

        return values[from2to];
    case 1:
        value = value_.toLongLong(&ok);
        if (!ok) {
            return QString("invalid input");
        } else {
            values["dec2bin"] = QString::number(value, 2);
            values["dec2hex"] = QString::number(value, 16);
            values["dec2oct"] = QString::number(value, 8);
        }

        return values[from2to];
    case 2:
        value = value_.toLongLong(&ok, 16);
        if (!ok) {
            return QString("invalid input");
        } else {
            values["hex2bin"] = QString::number(value, 2);
            values["hex2dec"] = QString::number(value, 10);
            values["hex2oct"] = QString::number(value, 8);
        }

        return values[from2to];

    case 3:
        value = value_.toLongLong(&ok, 8);
        if (!ok) {
            return QString("invalid input");
        } else {
            values["oct2bin"] = QString::number(value, 2);
            values["oct2dec"] = QString::number(value, 10);
            values["oct2hex"] = QString::number(value, 16);
        }

        return values[from2to];

    default:
        break;
    }
    return QString("");
}

void Converter::getCurrencies(QVariantMap cur)
{
    if (!cur.isEmpty()) {
        currency_rate = cur;
        currency_rate.insert("EUR", 1.0);
    }
}
