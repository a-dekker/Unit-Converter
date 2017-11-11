#include <QString>
#include <QMap>
#include <QVector>
#include <QSet>
#include <QRegExp>
#include <QMetaEnum>
#include <QtCore/QtMath>
#include <math.h>
#include "converter.h"

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

        values["m/s22cm/s2"] = QString::number(value * 100);
        values["m/s22mm/s2"] = QString::number(value * 1000);
        values["m/s22ft/s2"] = QString::number(value * 3.280839895);
        values["m/s22g"] = QString::number(value * 0.101971621);
        values["cm/s22m/s2"] = QString::number(value * 0.01);
        values["cm/s22mm/s2"] = QString::number(value * 10);
        values["cm/s22ft/s2"] = QString::number(value * 0.032808399);
        values["cm/s22g"] = QString::number(value * 0.001019716);
        values["mm/s22cm/s2"] = QString::number(value * 0.1);
        values["mm/s22m/s2"] = QString::number(value * 0.001);
        values["mm/s22ft/s2"] = QString::number(value * 0.00328084);
        values["mm/s22g"] = QString::number(value * 0.000101972);
        values["ft/s22m/s2"] = QString::number(value * 0.3048);
        values["ft/s22mm/s2"] = QString::number(value * 304.8);
        values["ft/s22cm/s2"] = QString::number(value * 30.48);
        values["ft/s22g"] = QString::number(value * 0.03108095);
        values["g2m/s2"] = QString::number(value * 9.80665);
        values["g2mm/s2"] = QString::number(value * 9806.65);
        values["g2ft/s2"] = QString::number(value * 32.174048556);
        values["g2cm/s2"] = QString::number(value * 980.665);

        return values[from2to];

    case ANGLE:
        values["deg2rad"] = QString::number(value * PI() / 180);
        values["deg2grad"] = QString::number(value * 1.111111111);
        values["rad2deg"] = QString::number(value * 180 / PI());
        values["rad2grad"] = QString::number(value * 200 / PI());
        values["grad2deg"] = QString::number(value * 0.9);
        values["grad2rad"] = QString::number(value * PI() / 200);

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
            values["acre2ha"] = QString::number(value * 0.40468564224);
            values["acre2cm2"] = QString::number(value * 40468564.224);
            values["acre2ft2"] = QString::number(value * 43560);
            values["acre2in2"] = QString::number(value * 6272640);
            values["acre2km2"] = QString::number(value * 0.0040468564224);
            values["acre2m2"] = QString::number(value * 4046.8564224);
            values["acre2mi2"] = QString::number(value * 0.0015625);
            values["acre2mm2"] = QString::number(value * 4046856422.4);
            values["acre2yd2"] = QString::number(value * 4840);

            return values[from2to];
        case 1:
            values["ha2acre"] = QString::number(value * 2.471053814672);
            values["ha2cm2"] = QString::number(value * 100000000);
            values["ha2ft2"] = QString::number(value * 107639.1041671);
            values["ha2in2"] = QString::number(value * 15500031.00006);
            values["ha2km2"] = QString::number(value * 0.01);
            values["ha2m2"] = QString::number(value * 10000);
            values["ha2mi2"] = QString::number(value * 0.003861021585424);
            values["ha2mm2"] = QString::number(value * 10000000000);
            values["ha2yd2"] = QString::number(value * 11959.90046301);

            return values[from2to];
        case 2:
            values["cm22acre"] = QString::number(value * 2.471053814672e-8);
            values["cm22ha"] = QString::number(value * 1e-8);
            values["cm22ft2"] = QString::number(value * 0.001076391041671);
            values["cm22in2"] = QString::number(value * 0.1550003100006);
            values["cm22km2"] = QString::number(value * 1e-10);
            values["cm22m2"] = QString::number(value * 0.0001);
            values["cm22mi2"] = QString::number(value * 3.861021585424e-11);
            values["cm22mm2"] = QString::number(value * 100);
            values["cm22yd2"] = QString::number(value * 0.0001195990046301);

            return values[from2to];
        case 3:
            values["ft22acre"] = QString::number(value * 0.00002295684113866);
            values["ft22ha"] = QString::number(value * 0.000009290304);
            values["ft22cm2"] = QString::number(value * 929.0304);
            values["ft22in2"] = QString::number(value * 144);
            values["ft22km2"] = QString::number(value * 9.290304e-8);
            values["ft22m2"] = QString::number(value * 0.09290304);
            values["ft22mi2"] = QString::number(value * 3.587006427915e-8);
            values["ft22mm2"] = QString::number(value * 92903.04);
            values["ft22yd2"] = QString::number(value * 0.1111111111111111);

            return values[from2to];
        case 4:
            values["in22acre"] = QString::number(value * 1.594225079074e-7);
            values["in22ha"] = QString::number(value * 6.4516e-8);
            values["in22cm2"] = QString::number(value * 6.4516);
            values["in22ft2"] = QString::number(value * 0.006944444444444444);
            values["in22km2"] = QString::number(value * 6.4516e-10);
            values["in22m2"] = QString::number(value * 0.00064516);
            values["in22mi2"] = QString::number(value * 2.490976686052e-10);
            values["in22mm2"] = QString::number(value * 645.16);
            values["in22yd2"] = QString::number(value * 0.0007716049382716);

            return values[from2to];
        case 5:
            values["km22acre"] = QString::number(value * 247.1053814672);
            values["km22ha"] = QString::number(value * 100);
            values["km22cm2"] = QString::number(value * 1e10);
            values["km22ft2"] = QString::number(value * 10763910.41671);
            values["km22in2"] = QString::number(value * 1550003100.006);
            values["km22m2"] = QString::number(value * 1000000);
            values["km22mi2"] = QString::number(value * 0.3861021585425);
            values["km22mm2"] = QString::number(value * 1000000000000.0);
            values["km22yd2"] = QString::number(value * 1195990.046301);

            return values[from2to];
        case 6:
            values["m22acre"] = QString::number(value * 0.000247105381467);
            values["m22ha"] = QString::number(value * 0.0001);
            values["m22cm2"] = QString::number(value * 10000);
            values["m22ft2"] = QString::number(value * 10.76391041671);
            values["m22in2"] = QString::number(value * 1550.003100006);
            values["m22km2"] = QString::number(value * 0.000001);
            values["m22mi2"] = QString::number(value * 3.8610215854252e-7);
            values["m22mm2"] = QString::number(value * 1000000);
            values["m22yd2"] = QString::number(value * 1.195990046301);

            return values[from2to];
        case 7:
            values["mi22acre"] = QString::number(value * 640);
            values["mi22ha"] = QString::number(value * 258.9988110336);
            values["mi22cm2"] = QString::number(value * 25899881103.3);
            values["mi22ft2"] = QString::number(value * 27878400);
            values["mi22in2"] = QString::number(value * 4014489600.0);
            values["mi22km2"] = QString::number(value * 2.589988110336);
            values["mi22m2"] = QString::number(value * 2589988.110336);
            values["mi22mm2"] = QString::number(value * 2589988110336.0);
            values["mi22yd2"] = QString::number(value * 3097600);

            return values[from2to];
        case 8:
            values["mm22acre"] = QString::number(value * 2.471053814672e-10);
            values["mm22ha"] = QString::number(value * 1e-10);
            values["mm22cm2"] = QString::number(value * 0.01);
            values["mm22ft2"] = QString::number(value * 0.00001076391041671);
            values["mm22in2"] = QString::number(value * 0.001550003100006);
            values["mm22km2"] = QString::number(value * 1e-12);
            values["mm22m2"] = QString::number(value * 0.000001);
            values["mm22mi2"] = QString::number(value * 3.861021585425e-13);
            values["mm22yd2"] = QString::number(value * 0.000001195990046301);

            return values[from2to];
        case 9:
            values["yd22acre"] = QString::number(value * 0.0002066115702479);
            values["yd22ha"] = QString::number(value * 0.000083612736);
            values["yd22cm2"] = QString::number(value * 8361.2736);
            values["yd22ft2"] = QString::number(value * 9);
            values["yd22in2"] = QString::number(value * 1296);
            values["yd22km2"] = QString::number(value * 8.3612736e-7);
            values["yd22m2"] = QString::number(value * 0.83612736);
            values["yd22mi2"] = QString::number(value * 3.228305785124e-7);
            values["yd22mm2"] = QString::number(value * 836127.36);

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
                                     << "kB"
                                     << "Mb"
                                     << "MB"
                                     << "Gb"
                                     << "GB");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["b2B"] = QString::number(value * 0.125);
            values["b2word"] = QString::number(value * 0.0625);
            values["b2kb"] = QString::number(value * 0.000976563);
            values["b2kB"] = QString::number(value * 0.00012207);
            values["b2Mb"] = QString::number(value * 0.000000954);
            values["b2MB"] = QString::number(value * 0.000000119);
            values["b2Gb"] = QString::number(value * 9.313225746e-10);
            values["b2GB"] = QString::number(value * 1.164153218e-10);

            return values[from2to];
        case 1:
            values["B2b"] = QString::number(value * 8);
            values["B2word"] = QString::number(value * 0.5);
            values["B2kb"] = QString::number(value * 0.0078125);
            values["B2kB"] = QString::number(value * 0.000976563);
            values["B2Mb"] = QString::number(value * 0.000007629);
            values["B2MB"] = QString::number(value * 0.000000954);
            values["B2Gb"] = QString::number(value * 0.000000007);
            values["B2GB"] = QString::number(value * 9.313225746e-10);

            return values[from2to];
        case 2:
            values["word2b"] = QString::number(value * 16);
            values["word2B"] = QString::number(value * 2);
            values["word2kb"] = QString::number(value * 0.015625);
            values["word2kB"] = QString::number(value * 0.001953125);
            values["word2Mb"] = QString::number(value * 0.000015259);
            values["word2MB"] = QString::number(value * 0.000001907);
            values["word2Gb"] = QString::number(value * 0.000000015);
            values["word2GB"] = QString::number(value * 0.000000002);

            return values[from2to];
        case 3:
            values["kb2B"] = QString::number(value * 128);
            values["kb2word"] = QString::number(value * 64);
            values["kb2b"] = QString::number(value * 1024);
            values["kb2kB"] = QString::number(value * 0.125);
            values["kb2Mb"] = QString::number(value * 0.000976563);
            values["kb2MB"] = QString::number(value * 0.00012207);
            values["kb2Gb"] = QString::number(value * 0.000000954);
            values["kb2GB"] = QString::number(value * 0.000000119);

            return values[from2to];
        case 4:
            values["kB2B"] = QString::number(value * 1024);
            values["kB2word"] = QString::number(value * 512);
            values["kB2kb"] = QString::number(value * 8);
            values["kB2b"] = QString::number(value * 8192);
            values["kB2Mb"] = QString::number(value * 0.0078125);
            values["kB2MB"] = QString::number(value * 0.000976562);
            values["kB2Gb"] = QString::number(value * 0.000007629);
            values["kB2GB"] = QString::number(value * 0.000000954);

            return values[from2to];
        case 5:
            values["Mb2B"] = QString::number(value * 131072);
            values["Mb2word"] = QString::number(value * 65536);
            values["Mb2kb"] = QString::number(value * 1024);
            values["Mb2kB"] = QString::number(value * 128);
            values["Mb2b"] = QString::number(value * 1048576);
            values["Mb2MB"] = QString::number(value * 0.125);
            values["Mb2Gb"] = QString::number(value * 0.000976562);
            values["Mb2GB"] = QString::number(value * 0.00012207);

            return values[from2to];
        case 6:
            values["MB2B"] = QString::number(value * 1048576);
            values["MB2word"] = QString::number(value * 524288);
            values["MB2kb"] = QString::number(value * 8192);
            values["MB2kB"] = QString::number(value * 1024);
            values["MB2Mb"] = QString::number(value * 8);
            values["MB2b"] = QString::number(value * 8388608);
            values["MB2Gb"] = QString::number(value * 0.0078125);
            values["MB2GB"] = QString::number(value * 0.000976563);

            return values[from2to];
        case 7:
            values["Gb2B"] = QString::number(value * 134217728);
            values["Gb2word"] = QString::number(value * 67108864);
            values["Gb2kb"] = QString::number(value * 1048576);
            values["Gb2kB"] = QString::number(value * 131072);
            values["Gb2Mb"] = QString::number(value * 1024);
            values["Gb2MB"] = QString::number(value * 128);
            values["Gb2b"] = QString::number(value * 1073741824);
            values["Gb2GB"] = QString::number(value * 0.125);

            return values[from2to];
        case 8:
            values["GB2B"] = QString::number(value * 1073741824);
            values["GB2word"] = QString::number(value * 536870912);
            values["GB2kb"] = QString::number(value * 8388608);
            values["GB2kB"] = QString::number(value * 1048576);
            values["GB2Mb"] = QString::number(value * 8192);
            values["GB2MB"] = QString::number(value * 1024);
            values["GB2Gb"] = QString::number(value * 8);
            values["GB2b"] = QString::number(value * 8589934592);

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
            values["Al2Cu"] = QString::number(value * 0.296766);
            values["Al2Au"] = QString::number(value * 0.136943);
            values["Al2g/cm3"] = QString::number(value * 2.699);
            values["Al2Fe"] = QString::number(value * 0.345129);
            values["Al2kg/m3"] = QString::number(value * 2699);
            values["Al2Pb"] = QString::number(value * 0.232454);
            values["Al2Ag"] = QString::number(value * 0.251475);

            return values[from2to];
        case 1:
            values["Cu2Al"] = QString::number(value * 3.369656);
            values["Cu2g/cm3"] = QString::number(value * 8.906);
            values["Cu2Fe"] = QString::number(value * 1.162967);
            values["Cu2kg/m3"] = QString::number(value * 8906);
            values["Cu2Pb"] = QString::number(value * 0.783289);
            values["Cu2Ag"] = QString::number(value * 0.847383);
            values["Cu2Au"] = QString::number(value * 0.461451);

            return values[from2to];
        case 2:
            values["Au2Cu"] = QString::number(value * 2.167078);
            values["Au2Al"] = QString::number(value * 7.302308);
            values["Au2g/cm3"] = QString::number(value * 19.3);
            values["Au2Fe"] = QString::number(value * 2.52024);
            values["Au2kg/m3"] = QString::number(value * 19300);
            values["Au2Pb"] = QString::number(value * 1.697449);
            values["Au2Ag"] = QString::number(value * 1.836346);

            return values[from2to];
        case 3:
            values["g/cm32Cu"] = QString::number(value * 0.112284);
            values["g/cm32Au"] = QString::number(value * 0.051813);
            values["g/cm32Al"] = QString::number(value * 0.378358);
            values["g/cm32Fe"] = QString::number(value * 0.130582);
            values["g/cm32kg/m3"] = QString::number(value * 1000);
            values["g/cm32Pb"] = QString::number(value * 0.087951);
            values["g/cm32Ag"] = QString::number(value * 0.095147);

            return values[from2to];
        case 4:
            values["Fe2Cu"] = QString::number(value * 0.85987);
            values["Fe2Au"] = QString::number(value * 0.396788);
            values["Fe2g/cm3"] = QString::number(value * 7.658);
            values["Fe2Al"] = QString::number(value * 2.897465);
            values["Fe2kg/m3"] = QString::number(value * 7658);
            values["Fe2Pb"] = QString::number(value * 0.673527);
            values["Fe2Ag"] = QString::number(value * 0.728639);

            return values[from2to];
        case 5:
            values["kg/m32Cu"] = QString::number(value * 0.000112);
            values["kg/m32Au"] = QString::number(value * 5.18134715025907e-5);
            values["kg/m32g/cm3"] = QString::number(value * 0.001);
            values["kg/m32Fe"] = QString::number(value * 0.000131);
            values["kg/m32Al"] = QString::number(value * 0.000378);
            values["kg/m32Pb"] = QString::number(value * 8.79507475813544e-5);
            values["kg/m32Ag"] = QString::number(value * 9.51474785918173e-5);

            return values[from2to];
        case 6:
            values["Pb2Cu"] = QString::number(value * 1.276667);
            values["Pb2Au"] = QString::number(value * 0.589119);
            values["Pb2g/cm3"] = QString::number(value * 11.37);
            values["Pb2Fe"] = QString::number(value * 1.484722);
            values["Pb2kg/m3"] = QString::number(value * 11370);
            values["Pb2Al"] = QString::number(value * 4.30193);
            values["Pb2Ag"] = QString::number(value * 1.081827);

            return values[from2to];
        case 7:
            values["Ag2Cu"] = QString::number(value * 1.180103);
            values["Ag2Au"] = QString::number(value * 0.54456);
            values["Ag2g/cm3"] = QString::number(value * 10.51);
            values["Ag2Fe"] = QString::number(value * 1.372421);
            values["Ag2kg/m3"] = QString::number(value * 10510);
            values["Ag2Pb"] = QString::number(value * 0.924362);
            values["Ag2Al"] = QString::number(value * 3.976542);

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
            values["Btu2cal"] = QString::number(value * 251.99577243);
            values["Btu2eV"] = QString::number(value * 6.5851382366e21);
            values["Btu2erg"] = QString::number(value * 10550559000);
            values["Btu2ftlb"] = QString::number(value * 778.16932495);
            values["Btu2J"] = QString::number(value * 1055.0559);
            values["Btu2kcal"] = QString::number(value * 0.25199577243);
            values["Btu2kJ"] = QString::number(value * 1.0550559);
            values["Btu2kWh"] = QString::number(value * 0.00029307108333);
            values["Btu2Nm"] = QString::number(value * 1055.0559);

            return values[from2to];
        case 1:
            values["cal2Btu"] = QString::number(value * 0.0039683205411);
            values["cal2eV"] = QString::number(value * 2613193933e10);
            values["cal2erg"] = QString::number(value * 41868000);
            values["cal2ftlb"] = QString::number(value * 3.0880253167);
            values["cal2J"] = QString::number(value * 4.1868);
            values["cal2kcal"] = QString::number(value * 0.001);
            values["cal2kJ"] = QString::number(value * 0.0041868);
            values["cal2kWh"] = QString::number(value * 0.000001163);
            values["cal2Nm"] = QString::number(value * 4.1868);

            return values[from2to];
        case 2:
            values["eV2Btu"] = QString::number(value * 1.5185710065e-22);
            values["eV2cal"] = QString::number(value * 3.8267347377e-20);
            values["eV2erg"] = QString::number(value * 1.6021773e-12);
            values["eV2ftlb"] = QString::number(value * 1.181705375e-19);
            values["eV2J"] = QString::number(value * 1.6021773e-19);
            values["eV2kcal"] = QString::number(value * 3.8267347377e-23);
            values["eV2kJ"] = QString::number(value * 1.6021773e-22);
            values["eV2kWh"] = QString::number(value * 4.4504925e-26);
            values["eV2Nm"] = QString::number(value * 1.6021773e-19);

            return values[from2to];
        case 3:
            values["erg2Btu"] = QString::number(value * 9.4781707775e-11);
            values["erg2cal"] = QString::number(value * 2.3884589663e-8);
            values["erg2eV"] = QString::number(value * 624150648000);
            values["erg2ftlb"] = QString::number(value * 7.3756217557e-8);
            values["erg2J"] = QString::number(value * 1e-7);
            values["erg2kcal"] = QString::number(value * 2.3884589663e-11);
            values["erg2kJ"] = QString::number(value * 1e-10);
            values["erg2kWh"] = QString::number(value * 2.7777777778e-14);
            values["erg2Nm"] = QString::number(value * 1e-7);

            return values[from2to];
        case 4:
            values["ftlb2Btu"] = QString::number(value * 0.0012850673599);
            values["ftlb2cal"] = QString::number(value * 0.32383154199);
            values["ftlb2eV"] = QString::number(value * 8462346208500000000);
            values["ftlb2erg"] = QString::number(value * 13558179);
            values["ftlb2J"] = QString::number(value * 1.3558179);
            values["ftlb2kcal"] = QString::number(value * 0.00032383154199);
            values["ftlb2kJ"] = QString::number(value * 0.0013558179);
            values["ftlb2kWh"] = QString::number(value * 3.7661608333e-7);
            values["ftlb2Nm"] = QString::number(value * 1.3558179);

            return values[from2to];
        case 5:
            values["J2Btu"] = QString::number(value * 0.00094781707775);
            values["J2cal"] = QString::number(value * 0.23884589663);
            values["J2eV"] = QString::number(value * 6241506480000000000);
            values["J2erg"] = QString::number(value * 10000000);
            values["J2ftlb"] = QString::number(value * 0.73756217557);
            values["J2kcal"] = QString::number(value * 0.00023884589663);
            values["J2kJ"] = QString::number(value * 0.001);
            values["J2kWh"] = QString::number(value * 2.7777777778e-7);
            values["J2Nm"] = QString::number(value);

            return values[from2to];
        case 6:
            values["kcal2Btu"] = QString::number(value * 0.0041868);
            values["kcal2cal"] = QString::number(value * 1000);
            values["kcal2eV"] = QString::number(value * 2.613193933e+22);
            values["kcal2erg"] = QString::number(value * 41868000000);
            values["kcal2ftlb"] = QString::number(value * 3088.0253167);
            values["kcal2J"] = QString::number(value * 4186.8);
            values["kcal2kJ"] = QString::number(value * 4.1868);
            values["kcal2kWh"] = QString::number(value * 0.001163);
            values["kcal2Nm"] = QString::number(value * 4186.8);

            return values[from2to];
        case 7:
            values["kJ2Btu"] = QString::number(value * 0.94781707775);
            values["kJ2cal"] = QString::number(value * 238.84589663);
            values["kJ2eV"] = QString::number(value * 6.24150648e+21);
            values["kJ2erg"] = QString::number(value * 10000000000);
            values["kJ2ftlb"] = QString::number(value * 737.56217557);
            values["kJ2J"] = QString::number(value * 1000);
            values["kJ2kcal"] = QString::number(value * 0.23884589663);
            values["kJ2kWh"] = QString::number(value * 0.00027777777778);
            values["kJ2Nm"] = QString::number(value * 1000);

            return values[from2to];
        case 8:
            values["kWh2Btu"] = QString::number(value * 3412.1414799);
            values["kWh2cal"] = QString::number(value * 859845.22786);
            values["kWh2eV"] = QString::number(value * 2.2469423328e+25);
            values["kWh2erg"] = QString::number(value * 36000000000000);
            values["kWh2ftlb"] = QString::number(value * 2655223.8321);
            values["kWh2J"] = QString::number(value * 3600000);
            values["kWh2kcal"] = QString::number(value * 859.84522786);
            values["kWh2kJ"] = QString::number(value * 3600);
            values["kWh2Nm"] = QString::number(value * 3600000);

            return values[from2to];
        case 9:
            values["Nm2Btu"] = QString::number(value * 0.00094781707775);
            values["Nm2cal"] = QString::number(value * 0.23884589663);
            values["Nm2eV"] = QString::number(value * 6241506480000000000);
            values["Nm2erg"] = QString::number(value * 10000000);
            values["Nm2ftlb"] = QString::number(value * 0.73756217557);
            values["Nm2J"] = QString::number(value);
            values["Nm2kcal"] = QString::number(value * 0.00023884589663);
            values["Nm2kJ"] = QString::number(value * 0.001);
            values["Nm2kWh"] = QString::number(value * 2.7777777778e-7);

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
            values["m3/h2m3/s"] = QString::number(value * 0.000277778);
            values["m3/h2cfm"] = QString::number(value * 0.588577779);
            values["m3/h2L/min"] = QString::number(value * 16.666666667);
            return values[from2to];
        case 1:
            values["m3/s2m3/h"] = QString::number(value * 3600);
            values["m3/s2cfm"] = QString::number(value * 2118.880003185);
            values["m3/s2L/min"] = QString::number(value * 60000);
            return values[from2to];
        case 2:
            values["cfm2m3/s"] = QString::number(value * 0.000471947);
            values["cfm2m3/h"] = QString::number(value * 1.699010796);
            values["cfm2L/min"] = QString::number(value * 28.316846593);
            return values[from2to];
        case 3:
            values["L/min2m3/s"] = QString::number(value * 0.000016667);
            values["L/min2cfm"] = QString::number(value * 0.035314667);
            values["L/min2m3/h"] = QString::number(value * 0.06);
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
            values["dyn2kip"] = QString::number(value * 2.2480894387e-9);
            values["dyn2kN"] = QString::number(value * 1e-8);
            values["dyn2lbf"] = QString::number(value * 0.0000022480894387);
            values["dyn2N"] = QString::number(value * 0.00001);
            values["dyn2ozf"] = QString::number(value * 0.000035969431019);

            return values[from2to];
        case 1:
            values["kip2dyn"] = QString::number(value * 444822160);
            values["kip2kN"] = QString::number(value * 4.4482216);
            values["kip2lbf"] = QString::number(value * 1e3);
            values["kip2N"] = QString::number(value * 4448.2216);
            values["kip2ozf"] = QString::number(value * 16000);

            return values[from2to];
        case 2:
            values["kN2dyn"] = QString::number(value * 100000000);
            values["kN2kip"] = QString::number(value * 0.22480894387);
            values["kN2lbf"] = QString::number(value * 224.80894309971052);
            values["kN2N"] = QString::number(value * 1000);
            values["kN2ozf"] = QString::number(value * 3596.9431019);

            return values[from2to];
        case 3:
            values["lbf2dyn"] = QString::number(value * 444822.16);
            values["lbf2kip"] = QString::number(value * 0.001);
            values["lbf2kN"] = QString::number(value * 0.004448221615260499);
            values["lbf2N"] = QString::number(value * 4.4482216152605);
            values["lbf2ozf"] = QString::number(value * 16);

            return values[from2to];
        case 4:
            values["N2dyn"] = QString::number(value * 100000);
            values["N2kip"] = QString::number(value * 0.00022480894387);
            values["N2kN"] = QString::number(value * 0.001);
            values["N2lbf"] = QString::number(value * 0.2248089430997105);
            values["N2ozf"] = QString::number(value * 3.5969431019);

            return values[from2to];
        case 5:
            values["ozf2dyn"] = QString::number(value * 27801.385);
            values["ozf2kip"] = QString::number(value * 0.0000625);
            values["ozf2kN"] = QString::number(value * 0.00027801385);
            values["ozf2lbf"] = QString::number(value * 0.0625);
            values["ozf2N"] = QString::number(value * 0.27801385);

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
            values["GHz2Hz"] = QString::number(value * 1e9);
            values["GHz2kHz"] = QString::number(value * 1e6);
            values["GHz2MHz"] = QString::number(value * 1e3);
            values["GHz2rad/s"] = QString::number(value * 2 * PI() * 1e9);
            values["GHz2rpm"] = QString::number(value * 60 * 1e9);
            values["GHz2THz"] = QString::number(value * 1e-3);

            return values[from2to];
        case 1:
            values["Hz2GHz"] = QString::number(value * 1e-9);
            values["Hz2kHz"] = QString::number(value * 1e-3);
            values["Hz2MHz"] = QString::number(value * 1e-6);
            values["Hz2rad/s"] = QString::number(value * 2 * PI());
            values["Hz2rpm"] = QString::number(value * 60);
            values["Hz2THz"] = QString::number(value * 1e-12);

            return values[from2to];
        case 2:
            values["kHz2GHz"] = QString::number(value * 1e-6);
            values["kHz2Hz"] = QString::number(value * 1e3);
            values["kHz2MHz"] = QString::number(value * 1e-3);
            values["kHz2rad/s"] = QString::number(value * 2 * PI() * 1e3);
            values["kHz2rpm"] = QString::number(value * 60 * 1e3);
            values["kHz2THz"] = QString::number(value * 1e-9);

            return values[from2to];
        case 3:
            values["MHz2GHz"] = QString::number(value * 1e-3);
            values["MHz2Hz"] = QString::number(value * 1e6);
            values["MHz2kHz"] = QString::number(value * 1e3);
            values["MHz2rad/s"] = QString::number(value * 2 * PI() * 1e6);
            values["MHz2rpm"] = QString::number(value * 60 * 1e6);
            values["MHz2THz"] = QString::number(value * 1e-6);

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
            values["rpm2rad/s"] = QString::number(value * (2 * PI()) / 60);
            values["rpm2THz"] = QString::number(value / 60 * 1e-12);

            return values[from2to];
        case 6:
            values["THz2GHz"] = QString::number(value * 1e3);
            values["THz2Hz"] = QString::number(value * 1e12);
            values["THz2kHz"] = QString::number(value * 1e9);
            values["THz2MHz"] = QString::number(value * 1e6);
            values["THz2rad/s"] = QString::number(value * (2 * PI()) * 1e12);
            values["THz2rmp"] = QString::number(value * 60 * 1e12);

            return values[from2to];
        }
        break;
    case FUELCONSUMPTION:
        unitOptions = (QStringList() << "km/L"
                                     << "L/100km"
                                     << "mpg");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["km/L2L/100km"] = QString::number(100/value);
            values["km/L2mpg"] = QString::number(value * 2.352145833);

            return values[from2to];
        case 1:
            values["L/100km2km/L"] = QString::number(100/value);
            values["L/100km2mpg"] = QString::number(235.214583295/value);
            return values[from2to];
        case 2:
            values["mpg2km/L"] = QString::number(value * 0.425143707);
            values["mpg2L/100km"] = QString::number(235.214583295/value);
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
            values["A2au"] = QString::number(value * 6.684587122671e-22);
            values["A2cm"] = QString::number(value * 1e-8);
            values["A2dm"] = QString::number(value * 1e-9);
            values["A2ft"] = QString::number(value * 3.280839895013e-10);
            values["A2in"] = QString::number(value * 3.937007874016e-9);
            values["A2km"] = QString::number(value * 1e-13);
            values["A2ly"] = QString::number(value * 1.057000834025e-26);
            values["A2m"] = QString::number(value * 1e-10);
            values["A2um"] = QString::number(value * 0.0001);
            values["A2mi"] = QString::number(value * 6.213711922373e-14);
            values["A2mm"] = QString::number(value * 1e-7);
            values["A2mil"] = QString::number(value * 3.937007874015748e-06);
            values["A2nautmi"] = QString::number(value * 5.399568034557e-14);
            values["A2nm"] = QString::number(value * 0.1);
            values["A2pm"] = QString::number(value * 100);
            values["A2yd"] = QString::number(value * 1.093613298338e-10);

            return values[from2to];
        case 1:
            values["au2A"] = QString::number(value * 1.49597870691e21);
            values["au2cm"] = QString::number(value * 1.49597870691e13);
            values["au2dm"] = QString::number(value * 1.49597870691e12);
            values["au2ft"] = QString::number(value * 490806662372);
            values["au2in"] = QString::number(value * 5889679948464);
            values["au2km"] = QString::number(value * 1.49597870691e8);
            values["au2ly"] = QString::number(value * 0.00001581250740887);
            values["au2m"] = QString::number(value * 1.49597870691e11);
            values["au2um"] = QString::number(value * 1.49597870691e17);
            values["au2mi"] = QString::number(value * 92955807.26743);
            values["au2mm"] = QString::number(value * 1.49597870691e14);
            values["au2mil"] = QString::number(value * 5889679948818897.0);
            values["au2nautmi"] = QString::number(value * 80776388.06695464);
            values["au2nm"] = QString::number(value * 1.49597870691e20);
            values["au2pm"] = QString::number(value * 1.49597870691e23);
            values["au2yd"] = QString::number(value * 163602220790.7);

            return values[from2to];
        case 2:
            values["cm2A"] = QString::number(value * 100000000);
            values["cm2au"] = QString::number(value * 6.684587122268446e-14);
            values["cm2dm"] = QString::number(value * 0.1);
            values["cm2ft"] = QString::number(value * 0.03280839895013);
            values["cm2in"] = QString::number(value * 0.39370078740157477);
            values["cm2km"] = QString::number(value * 0.00001);
            values["cm2ly"] = QString::number(value * 1.0570008340246155e-18);
            values["cm2m"] = QString::number(value * 0.01);
            values["cm2um"] = QString::number(value * 10000);
            values["cm2mi"] = QString::number(value * 0.000006213711922373);
            values["cm2mm"] = QString::number(value * 10);
            values["cm2mil"] = QString::number(value * 393.7007874015748);
            values["cm2nautmi"] =
                QString::number(value * 5.399568034557236e-06);
            values["cm2nm"] = QString::number(value * 10000000);
            values["cm2pm"] = QString::number(value * 10000000000);
            values["cm2yd"] = QString::number(value * 0.01093613298338);

            return values[from2to];
        case 3:
            values["dm2A"] = QString::number(value * 10000000);
            values["dm2au"] = QString::number(value * 6.684587122268446e-13);
            values["dm2cm"] = QString::number(value * 10);
            values["dm2ft"] = QString::number(value * 0.3280839895013);
            values["dm2in"] = QString::number(value * 3.9370078740157477);
            values["dm2km"] = QString::number(value * 0.0001);
            values["dm2ly"] = QString::number(value * 1.0570008340246155e-17);
            values["dm2m"] = QString::number(value * 0.1);
            values["dm2um"] = QString::number(value * 100000);
            values["dm2mi"] = QString::number(value * 0.00006213711922373);
            values["dm2mm"] = QString::number(value * 100);
            values["dm2mil"] = QString::number(value * 3937.007874015748);
            values["dm2nautmi"] =
                QString::number(value * 5.399568034557236e-05);
            values["dm2nm"] = QString::number(value * 100000000);
            values["dm2pm"] = QString::number(value * 100000000000);
            values["dm2yd"] = QString::number(value * 0.1093613298338);

            return values[from2to];
        case 4:
            values["ft2A"] = QString::number(value * 3.048e9);
            values["ft2au"] = QString::number(value * 2.03746215499e-12);
            values["ft2cm"] = QString::number(value * 30.48);
            values["ft2dm"] = QString::number(value * 3.048);
            values["ft2in"] = QString::number(value * 12);
            values["ft2km"] = QString::number(value * 0.0003048);
            values["ft2ly"] = QString::number(value * 3.221738542107e-17);
            values["ft2m"] = QString::number(value * 0.3048);
            values["ft2um"] = QString::number(value * 304800);
            values["ft2mi"] = QString::number(value / 5280);
            values["ft2mm"] = QString::number(value * 304.8);
            values["ft2mil"] = QString::number(value * 12000);
            values["ft2nautmi"] = QString::number(value * 0.0001645788336933);
            values["ft2nm"] = QString::number(value * 304800000);
            values["ft2pm"] = QString::number(value * 304800000000);
            values["ft2yd"] = QString::number(value / 3);

            return values[from2to];
        case 5:
            values["in2A"] = QString::number(value * 254000000);
            values["in2au"] = QString::number(value * 1.697885129158e-13);
            values["in2cm"] = QString::number(value * 2.54);
            values["in2dm"] = QString::number(value * 0.254);
            values["in2ft"] = QString::number(value / 12);
            values["in2km"] = QString::number(value * 0.0000254);
            values["in2ly"] = QString::number(value * 2.684782118423e-18);
            values["in2m"] = QString::number(value * 2.684782118423e-18);
            values["in2um"] = QString::number(value * 0.0254);
            values["in2mi"] = QString::number(value * 0.00001578282828283);
            values["in2mm"] = QString::number(value * 25.4);
            values["in2mil"] = QString::number(value * 1000);
            values["in2nautmi"] = QString::number(value * 0.00001371490280778);
            values["in2nm"] = QString::number(value * 25400000);
            values["in2pm"] = QString::number(value * 2.54e10);
            values["in2yd"] = QString::number(value / 36);

            return values[from2to];
        case 6:
            values["km2A"] = QString::number(value * 1e13);
            values["km2au"] = QString::number(value * 6.684587122671e-9);
            values["km2cm"] = QString::number(value * 100000);
            values["km2dm"] = QString::number(value * 10000);
            values["km2ft"] = QString::number(value * 3280.839895013);
            values["km2in"] = QString::number(value / 0.0000254);
            values["km2ly"] = QString::number(value * 1.057000834025e-13);
            values["km2m"] = QString::number(value * 1e3);
            values["km2um"] = QString::number(value * 1000000000);
            values["km2mi"] = QString::number(value / 1.609344);
            values["km2mm"] = QString::number(value * 1000000);
            values["km2mil"] = QString::number(value * 39370078.740158);
            values["km2nautmi"] = QString::number(value * 0.5399568034557);
            values["km2nm"] = QString::number(value * 1e12);
            values["km2pm"] = QString::number(value * 1e15);
            values["km2yd"] = QString::number(value * 1093.613298338);

            return values[from2to];
        case 7:
            values["ly2A"] = QString::number(value * 9.460730473e25);
            values["ly2au"] = QString::number(value * 63241.07708807);
            values["ly2cm"] = QString::number(value * 9.46073047258100000e17);
            values["ly2dm"] = QString::number(value * 9.460730473e+16);
            values["ly2ft"] = QString::number(value * 3.1039141970410000e16);
            values["ly2in"] = QString::number(value * 3.72469703644900000e17);
            values["ly2km"] = QString::number(value * 9.460730473e+12);
            values["ly2m"] = QString::number(value * 9.460730473e+15);
            values["ly2um"] = QString::number(value * 9.460730473e+21);
            values["ly2mi"] = QString::number(value * 5878625373184);
            values["ly2mm"] = QString::number(value * 9.460730473e+21);
            values["ly2mil"] = QString::number(value * 3.724697036e+20);
            values["ly2nautmi"] = QString::number(value * 5108385784331);
            values["ly2nm"] = QString::number(value * 9.460730473e+24);
            values["ly2pm"] = QString::number(value * 9.460730473e+27);
            values["ly2yd"] = QString::number(value * 1.034638066e+16);

            return values[from2to];
        case 8:
            values["m2A"] = QString::number(value * 1e+10);
            values["m2au"] = QString::number(value * 6.684587122671e-12);
            values["m2cm"] = QString::number(value * 100);
            values["m2dm"] = QString::number(value * 10);
            values["m2ft"] = QString::number(value * 3.280839895013);
            values["m2in"] = QString::number(value / 0.0254);
            values["m2ly"] = QString::number(value * 1.057000834025e-16);
            values["m2km"] = QString::number(value / 1000);
            values["m2um"] = QString::number(value * 1000000);
            values["m2mi"] = QString::number(value * 0.0006213711922373);
            values["m2mm"] = QString::number(value * 1000);
            values["m2mil"] = QString::number(value * 39370.078740158);
            values["m2nautmi"] = QString::number(value * 0.0005399568034557);
            values["m2nm"] = QString::number(value * 1e9);
            values["m2pm"] = QString::number(value * 1e12);
            values["m2yd"] = QString::number(value * 1.093613298338);

            return values[from2to];
        case 9:
            values["um2A"] = QString::number(value * 10000);
            values["um2au"] = QString::number(value * 6.684587123e-18);
            values["um2cm"] = QString::number(value * 0.0001);
            values["um2dm"] = QString::number(value * 0.00001);
            values["um2ft"] = QString::number(value * 0.000003281);
            values["um2in"] = QString::number(value / 25400);
            values["um2ly"] = QString::number(value * 1.057000834e-22);
            values["um2km"] = QString::number(value * 0.000000001);
            values["um2m"] = QString::number(value * 1e-6);
            values["um2mi"] = QString::number(value * 6.213711922e-10);
            values["um2mm"] = QString::number(value * 0.001);
            values["um2mil"] = QString::number(value * 0.039370079);
            values["um2nautmi"] = QString::number(value * 5.399568035e-10);
            values["um2nm"] = QString::number(value * 1e3);
            values["um2pm"] = QString::number(value * 1e6);
            values["um2yd"] = QString::number(value * 0.000001094);

            return values[from2to];
        case 10:
            values["mi2A"] = QString::number(value * 1.609344e+13);
            values["mi2au"] = QString::number(value * 0.000000011);
            values["mi2cm"] = QString::number(value * 160934.4);
            values["mi2dm"] = QString::number(value * 16093.44);
            values["mi2ft"] = QString::number(value * 5280);
            values["mi2in"] = QString::number(value * 63360);
            values["mi2ly"] = QString::number(value * 1.701077950232e-13);
            values["mi2km"] = QString::number(value * 1.609344);
            values["mi2m"] = QString::number(value * 1609.344);
            values["mi2um"] = QString::number(value * 1609344000);
            values["mi2mm"] = QString::number(value * 1609344);
            values["mi2mil"] = QString::number(value * 63360000);
            values["mi2nautmi"] = QString::number(value * 0.8689762419006);
            values["mi2nm"] = QString::number(value * 1.609344e+12);
            values["mi2pm"] = QString::number(value * 1.609344e+15);
            values["mi2yd"] = QString::number(value * 1760);

            return values[from2to];
        case 11:
            values["mm2A"] = QString::number(value * 10000000);
            values["mm2au"] = QString::number(value * 6.684587123e-15);
            values["mm2cm"] = QString::number(value * 0.1);
            values["mm2dm"] = QString::number(value * 0.01);
            values["mm2ft"] = QString::number(value * 0.00328084);
            values["mm2in"] = QString::number(value * 0.039370079);
            values["mm2ly"] = QString::number(value * 1.057000834e-19);
            values["mm2km"] = QString::number(value * 0.000001);
            values["mm2m"] = QString::number(value * 0.001);
            values["mm2um"] = QString::number(value * 1e3);
            values["mm2mi"] = QString::number(value * 6.213711922373e-7);
            values["mm2mil"] = QString::number(value * 39.37007874);
            values["mm2nautmi"] = QString::number(value * 0.00000054);
            values["mm2nm"] = QString::number(value * 1000000);
            values["mm2pm"] = QString::number(value * 1000000000);
            values["mm2yd"] = QString::number(value * 0.001093613298338);

            return values[from2to];
        case 12:
            values["mil2A"] = QString::number(value * 254000);
            values["mil2au"] = QString::number(value * 1.697885129e-16);
            values["mil2cm"] = QString::number(value * 0.00254);
            values["mil2dm"] = QString::number(value * 0.000254);
            values["mil2ft"] = QString::number(value * 0.000083333);
            values["mil2in"] = QString::number(value * 0.001);
            values["mil2ly"] = QString::number(value * 2.684782118e-21);
            values["mil2km"] = QString::number(value * 0.000000025);
            values["mil2m"] = QString::number(value * 0.0000254);
            values["mil2um"] = QString::number(value * 25.4);
            values["mil2mi"] = QString::number(value * 0.000000016);
            values["mil2mm"] = QString::number(value * 0.0254);
            values["mil2nautmi"] = QString::number(value * 0.000000014);
            values["mil2nm"] = QString::number(value * 25400);
            values["mil2pm"] = QString::number(value * 25400000);
            values["mil2yd"] = QString::number(value * 0.000027778);

            return values[from2to];
        case 13:
            values["nautmi2A"] = QString::number(value * 1.852e13);
            values["nautmi2au"] = QString::number(value * 0.000000012);
            values["nautmi2cm"] = QString::number(value * 185200);
            values["nautmi2dm"] = QString::number(value * 18520);
            values["nautmi2ft"] = QString::number(value * 6076.115485564);
            values["nautmi2in"] = QString::number(value * 72913.385826772);
            values["nautmi2ly"] = QString::number(value * 1.957565545e-13);
            values["nautmi2km"] = QString::number(value * 1.852);
            values["nautmi2m"] = QString::number(value * 1852);
            values["nautmi2um"] = QString::number(value * 1852000000);
            values["nautmi2mi"] = QString::number(value * 1.150779448);
            values["nautmi2mm"] = QString::number(value * 1852000);
            values["nautmi2mil"] = QString::number(value * 72913385.826772);
            values["nautmi2nm"] = QString::number(value * 1.852e12);
            values["nautmi2pm"] = QString::number(value * 1.852e15);
            values["nautmi2yd"] = QString::number(value * 2025.371828521);

            return values[from2to];
        case 14:
            values["nm2A"] = QString::number(value * 10);
            values["nm2au"] = QString::number(value * 6.684587123e-21);
            values["nm2cm"] = QString::number(value * 0.0000001);
            values["nm2dm"] = QString::number(value * 0.00000001);
            values["nm2ft"] = QString::number(value * 0.000000003);
            values["nm2in"] = QString::number(value * 0.000000039);
            values["nm2ly"] = QString::number(value * 1.057000834e-25);
            values["nm2km"] = QString::number(value * 1e-12);
            values["nm2m"] = QString::number(value * 1e-9);
            values["nm2um"] = QString::number(value * 0.001);
            values["nm2mi"] = QString::number(value * 6.213711922e-13);
            values["nm2mm"] = QString::number(value * 0.000001);
            values["nm2mil"] = QString::number(value * 0.00003937);
            values["nm2nautmi"] = QString::number(value * 5.399568035e-13);
            values["nm2pm"] = QString::number(value * 1000);
            values["nm2yd"] = QString::number(value * 0.000000001);

            return values[from2to];
        case 15:
            values["pm2A"] = QString::number(value * 6.684587123e-24);
            values["pm2au"] = QString::number(value * 6.684587123e-24);
            values["pm2cm"] = QString::number(value * 0.01);
            values["pm2dm"] = QString::number(value * 1e-11);
            values["pm2ft"] = QString::number(value * 3.280839895e-12);
            values["pm2in"] = QString::number(value * 3.937007874e-11);
            values["pm2ly"] = QString::number(value * 1.057000834e-28);
            values["pm2km"] = QString::number(value * 1e-15);
            values["pm2m"] = QString::number(value * 1e-12);
            values["pm2um"] = QString::number(value * 0.000001);
            values["pm2mi"] = QString::number(value * 6.213711922e-16);
            values["pm2mm"] = QString::number(value * 1e-9);
            values["pm2mil"] = QString::number(value * 0.000000039);
            values["pm2nautmi"] = QString::number(value * 5.399568035e-16);
            values["pm2nm"] = QString::number(value * 0.001);
            values["pm2yd"] = QString::number(value * 1.093613298e-12);

            return values[from2to];
        case 16:
            values["yd2A"] = QString::number(value * 9144000000);
            values["yd2au"] = QString::number(value * 6.112386465e-12);
            values["yd2cm"] = QString::number(value * 91.44);
            values["yd2dm"] = QString::number(value * 9.144);
            values["yd2ft"] = QString::number(value * 3);
            values["yd2in"] = QString::number(value * 36);
            values["yd2ly"] = QString::number(value * 9.665215626e-17);
            values["yd2km"] = QString::number(value * 0.0009144);
            values["yd2m"] = QString::number(value * 0.9144);
            values["yd2um"] = QString::number(value * 914400);
            values["yd2mi"] = QString::number(value * 0.000568182);
            values["yd2mm"] = QString::number(value * 914.4);
            values["yd2mil"] = QString::number(value * 36000);
            values["yd2nautmi"] = QString::number(value * 0.000493737);
            values["yd2nm"] = QString::number(value * 914400000);
            values["yd2pm"] = QString::number(value * 9.144e11);

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
            values["amu2g"] = QString::number(value * 1.6605402e-24);
            values["amu2gr"] = QString::number(value * 2.562605143e-23);
            values["amu2kg"] = QString::number(value * 1.6605402e-27);
            values["amu2lbm"] = QString::number(value * 3.660864489409e-27);
            values["amu2ug"] = QString::number(value * 1.6605402e-18);
            values["amu2mg"] = QString::number(value * 1.6605402e-21);
            values["amu2oz"] = QString::number(value * 5.857383183e-26);
            values["amu2slug"] =
                QString::number(value * (3.660864489409 * 1e-27) / 32.17405);

            return values[from2to];
        case 1:
            values["g2amu"] = QString::number(value * 6.022136651675 * 1e23);
            values["g2gr"] = QString::number(value * 15.432358353);
            values["g2kg"] = QString::number(value * 1e-3);
            values["g2lbm"] = QString::number(value * 0.002204622621849);
            values["g2ug"] = QString::number(value * 1e6);
            values["g2mg"] = QString::number(value * 1e3);
            values["g2oz"] = QString::number(value * 0.035273962);
            values["g2slug"] =
                QString::number(value * 0.002204622621849 / 32.17405);

            return values[from2to];

        case 2:
            values["gr2amu"] = QString::number(value * 3.902278909e22);
            values["gr2g"] = QString::number(value * 0.06479891);
            values["gr2kg"] = QString::number(value * 0.000064799);
            values["gr2lbm"] = QString::number(value * 0.000142857);
            values["gr2ug"] = QString::number(value * 64798.910000174);
            values["gr2mg"] = QString::number(value * 64.79891);
            values["gr2oz"] = QString::number(value * 0.002285714);
            values["gr2slug"] = QString::number(value * 0.00000444);

            return values[from2to];

        case 3:
            values["kg2amu"] = QString::number(value * 6.022136651675e26);
            values["kg2g"] = QString::number(value * 1000);
            values["kg2gr"] = QString::number(value * 15432.3583529);
            values["kg2lbm"] = QString::number(value / 0.45359237);
            values["kg2ug"] = QString::number(value * 1000000000);
            values["kg2mg"] = QString::number(value * 1000000);
            values["kg2oz"] = QString::number(value * 35.27396195);
            values["kg2slug"] = QString::number(value / 14.5939);

            return values[from2to];
        case 4:
            values["lbm2amu"] = QString::number(value * 2.731595236297e26);
            values["lbm2g"] = QString::number(value * 453.59237);
            values["lbm2gr"] = QString::number(value * 6999.999999981);
            values["lbm2kg"] = QString::number(value * 0.45359237);
            values["lbm2ug"] = QString::number(value * 453592370);
            values["lbm2mg"] = QString::number(value * 453592.37);
            values["lbm2oz"] = QString::number(value * 16);
            values["lbm2slug"] = QString::number(value / 32.17405);

            return values[from2to];
        case 5:
            values["ug2amu"] = QString::number(value * 602213665167500000);
            values["ug2g"] = QString::number(value * 0.000001);
            values["ug2gr"] = QString::number(value * 0.000015432);
            values["ug2kg"] = QString::number(value * 1e-9);
            values["ug2lbm"] = QString::number(value * 2.204622621849e-9);
            values["ug2mg"] = QString::number(value * 0.001);
            values["ug2oz"] = QString::number(value * 0.000000035);
            values["ug2slug"] =
                QString::number(value * 2.204622621849e-9 / 32.17405);

            return values[from2to];

        case 6:
            values["mg2g"] = QString::number(value * 0.001);
            values["mg2gr"] = QString::number(value * 0.015432358);
            values["mg2kg"] = QString::number(value * 0.000001);
            values["mg2lbm"] = QString::number(value * 0.000002204622621849);
            values["mg2ug"] = QString::number(value * 1e3);
            values["mg2amu"] = QString::number(value * 6.022136651675e20);
            values["mg2oz"] = QString::number(value * 0.000035274);
            values["mg2slug"] =
                QString::number(value * 0.000002204622621849 / 32.17405);

            return values[from2to];

        case 7:
            values["oz2g"] = QString::number(value * 28.349523125);
            values["oz2gr"] = QString::number(value * 437.499999999);
            values["oz2kg"] = QString::number(value * 0.028349523);
            values["oz2lbm"] = QString::number(value * 0.0625);
            values["oz2ug"] = QString::number(value * 28349523.125);
            values["oz2amu"] = QString::number(value * 1.707247023e25);
            values["oz2slug"] = QString::number(value * 0.001942559);
            values["oz2mg"] = QString::number(value * 28349.523125);

            return values[from2to];

        case 8:
            values["slug2amu"] = QString::number(value * 8.78865485e+27);
            values["slug2g"] = QString::number(value * 14.5939 * 1000);
            values["slug2gr"] = QString::number(value * 225218.33989438);
            values["slug2kg"] = QString::number(value * 14.5939);
            values["slug2lbm"] = QString::number(value * 32.17405);
            values["slug2mg"] = QString::number(value * 14.5939 * 1000000);
            values["slug2ug"] = QString::number(value * 14.5939 * 1000000000);
            values["slug2oz"] = QString::number(value * 514.784776903);

            return values[from2to];
        }
        break;
    case MAGNETICFIELDSTRENGTH:
        unitOptions = (QStringList() << "A/m"
                                     << "Oe");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["A/m2Oe"] = QString::number(value * 0.012566371);
            return values[from2to];
        case 1:
            values["Oe2A/m"] = QString::number(value * 79.577471546);
            return values[from2to];
        }
        break;
    case MAGNETICFLUXDENSITY:
        unitOptions = (QStringList() << "gamma"
                                     << "Gs"
                                     << "T");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["gamma2Gs"] = QString::number(value * 0.00001);
            values["gamma2T"] = QString::number(value * 0.000000001);
            return values[from2to];
        case 1:
            values["Gs2gamma"] = QString::number(value * 100000);
            values["Gs2T"] = QString::number(value * 0.0001);
            return values[from2to];
        case 2:
            values["T2Gs"] = QString::number(value * 10000);
            values["T2gamma"] = QString::number(value * 1e9);
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
            values["hpb2Btu/h"] = QString::number(value * 33471.403350169);
            values["hpb2cal/s"] = QString::number(value * 2342.958822967);
            values["hpb2hpe"] = QString::number(value * 13.149463807);
            values["hpb2ftlb/s"] = QString::number(value * 7235.115903346);
            values["hpb2GW"] = QString::number(value * 0.00000981);
            values["hpb2kW"] = QString::number(value * 9.8095);
            values["hpb2hp"] = QString::number(value * 13.337208255);
            values["hpb2MW"] = QString::number(value * 0.0098095);
            values["hpb2TW"] = QString::number(value * 0.00000001);
            values["hpb2W"] = QString::number(value * 9809.5);
            values["hpb2dBm"] =
                QString::number(convertdBm(value * 9809.5 * 1e3));
            values["hpb2dBW"] = QString::number(convertdBW(value * 9809.5));

            return values[from2to];

        case 1:
            values["Btu/h2hpb"] = QString::number(value * 0.000029876);
            values["Btu/h2cal/s"] = QString::number(value * 0.069998823);
            values["Btu/h2hpe"] = QString::number(value * 0.000392857);
            values["Btu/h2ftlb/s"] = QString::number(value * 0.216158128);
            values["Btu/h2GW"] = QString::number(value * 2.930710702e-10);
            values["Btu/h2kW"] = QString::number(value * 0.000293071);
            values["Btu/h2hp"] = QString::number(value * 0.000398466);
            values["Btu/h2MW"] = QString::number(value * 0.000038392);
            values["Btu/h2TW"] = QString::number(value * 2.930710702e-13);
            values["Btu/h2W"] = QString::number(value * 0.29307107);
            values["Btu/h2dBm"] =
                QString::number(convertdBm(value * 0.29307107 * 1e3));
            values["Btu/h2dBW"] =
                QString::number(convertdBW(value * 0.29307107));

            return values[from2to];

        case 2:
            values["cal/s2hpb"] = QString::number(value * 0.000426811);
            values["cal/s2Btu/h"] = QString::number(value * 14.28595459);
            values["cal/s2hpe"] = QString::number(value * 0.005612332);
            values["cal/s2ftlb/s"] = QString::number(value * 3.088025207);
            values["cal/s2GW"] = QString::number(value * 0.000000004);
            values["cal/s2kW"] = QString::number(value * 0.0041868);
            values["cal/s2hp"] = QString::number(value * 0.005692464);
            values["cal/s2MW"] = QString::number(value * 0.000004187);
            values["cal/s2TW"] = QString::number(value * 4.1868e-12);
            values["cal/s2W"] = QString::number(value * 4.1868);
            values["cal/s2dBm"] =
                QString::number(convertdBm(value * 4.1868 * 1e3));
            values["cal/s2dBW"] = QString::number(convertdBW(value * 4.1868));

            return values[from2to];

        case 3:
            values["hpe2Btu/h"] = QString::number(value * 2545.457658313);
            values["hpe2cal/s"] = QString::number(value * 178.179038884);
            values["hpe2hpb"] = QString::number(value * 0.076048728);
            values["hpe2ftlb/s"] = QString::number(value * 550.221363362);
            values["hpe2GW"] = QString::number(value * 0.000000746);
            values["hpe2kW"] = QString::number(value * 0.746);
            values["hpe2hp"] = QString::number(value * 1.014277727);
            values["hpe2MW"] = QString::number(value * 0.000746);
            values["hpe2TW"] = QString::number(value * 7.46e-10);
            values["hpe2W"] = QString::number(value * 746);
            values["hpe2dBm"] = QString::number(convertdBm(value * 746 * 1e3));
            values["hpe2dBW"] = QString::number(convertdBW(value * 746));

            return values[from2to];

        case 4:
            values["ftlb/s2Btu/h"] = QString::number(value * 4.626242868);
            values["ftlb/s2cal/s"] = QString::number(value * 0.323831554);
            values["ftlb/s2hpe"] = QString::number(value * 0.00181745);
            values["ftlb/s2hpb"] = QString::number(value * 0.000138215);
            values["ftlb/s2GW"] = QString::number(value * 0.000000001);
            values["ftlb/s2kW"] = QString::number(value * 0.001355818);
            values["ftlb/s2hp"] = QString::number(value * 0.001843399);
            values["ftlb/s2MW"] = QString::number(value * 0.000001356);
            values["ftlb/s2TW"] = QString::number(value * 1.355817948e-12);
            values["ftlb/s2W"] = QString::number(value * 1.355817948);
            values["ftlb/s2dBm"] =
                QString::number(convertdBm(value * 1.355817948 * 1e3));
            values["ftlb/s2dBW"] =
                QString::number(convertdBW(value * 1.355817948));

            return values[from2to];

        case 5:
            values["GW2Btu/h"] = QString::number(value * 3412141633.1279);
            values["GW2cal/s"] = QString::number(value * 238845896.6275);
            values["GW2hpe"] = QString::number(value * 1340482.5737265);
            values["GW2ftlb/s"] = QString::number(value * 737562149.27833);
            values["GW2hpb"] = QString::number(value * 101941.99500484);
            values["GW2kW"] = QString::number(value * 1000000);
            values["GW2hp"] = QString::number(value * 1359621.6173039);
            values["GW2MW"] = QString::number(value * 1000);
            values["GW2TW"] = QString::number(value * 0.001);
            values["GW2W"] = QString::number(value * 1000000000);
            values["GW2dBm"] = QString::number(convertdBm(value * 1e9 * 1e3));
            values["GW2dBW"] = QString::number(convertdBW(value * 1e9));

            return values[from2to];

        case 6:
            values["kW2Btu/h"] = QString::number(value * 3412.141633128);
            values["kW2cal/s"] = QString::number(value * 238.845896627);
            values["kW2hpe"] = QString::number(value * 1.340482574);
            values["kW2ftlb/s"] = QString::number(value * 737.562149278);
            values["kW2GW"] = QString::number(value * 0.000001);
            values["kW2hpb"] = QString::number(value * 0.101941995);
            values["kW2hp"] = QString::number(value * 1.359621617);
            values["kW2MW"] = QString::number(value * 0.001);
            values["kW2TW"] = QString::number(value * 0.000000001);
            values["kW2W"] = QString::number(value * 1000);
            values["kW2dBm"] = QString::number(convertdBm(value * 1000 * 1e3));
            values["kW2dBW"] = QString::number(convertdBW(value * 1000));

            return values[from2to];

        case 7:
            values["hp2Btu/h"] = QString::number(value * 2509.625905989);
            values["hp2cal/s"] = QString::number(value * 175.670858412);
            values["hp2hpe"] = QString::number(value * 0.985923257);
            values["hp2ftlb/s"] = QString::number(value * 542.476038842);
            values["hp2GW"] = QString::number(value * 0.000000735);
            values["hp2kW"] = QString::number(value * 0.73549875);
            values["hp2hpb"] = QString::number(value * 0.07497821);
            values["hp2MW"] = QString::number(value * 0.000735499);
            values["hp2TW"] = QString::number(value * 7.3549875e-10);
            values["hp2W"] = QString::number(value * 735.49875);
            values["hp2dBm"] =
                QString::number(convertdBm(value * 735.49875 * 1e3));
            values["hp2dBW"] = QString::number(convertdBW(value * 735.49875));

            return values[from2to];

        case 8:
            values["MW2Btu/h"] = QString::number(value * 3412141.6331279);
            values["MW2cal/s"] = QString::number(value * 238845.8966275);
            values["MW2hpe"] = QString::number(value * 1340.482573727);
            values["MW2ftlb/s"] = QString::number(value * 737562.14927833);
            values["MW2GW"] = QString::number(value * 0.001);
            values["MW2kW"] = QString::number(value * 1000);
            values["MW2hp"] = QString::number(value * 1359.621617304);
            values["MW2hpb"] = QString::number(value * 101.941995005);
            values["MW2TW"] = QString::number(value * 0.000001);
            values["MW2W"] = QString::number(value * 1000000);
            values["MW2dBm"] =
                QString::number(convertdBm(value * 1000000 * 1e3));
            values["MW2dBW"] = QString::number(convertdBW(value * 1000000));

            return values[from2to];

        case 9:
            values["TW2Btu/h"] = QString::number(value * 3.412141633e12);
            values["TW2cal/s"] = QString::number(value * 2.388458966e11);
            values["TW2hpe"] = QString::number(value * 1340482573.7265);
            values["TW2ftlb/s"] = QString::number(value * 2.388458966e11);
            values["TW2GW"] = QString::number(value * 1000);
            values["TW2kW"] = QString::number(value * 1000000000);
            values["TW2hp"] = QString::number(value * 1359621617.3039);
            values["TW2MW"] = QString::number(value * 1000000);
            values["TW2hpb"] = QString::number(value * 101941995.00484);
            values["TW2W"] = QString::number(value * 1e12);
            values["TW2dBm"] = QString::number(convertdBm(value * 1e12 * 1e3));
            values["TW2dBW"] = QString::number(convertdBW(value * 1e12));

            return values[from2to];

        case 10:
            values["W2Btu/h"] = QString::number(value * 3.412141633);
            values["W2cal/s"] = QString::number(value * 0.238845897);
            values["W2hpe"] = QString::number(value * 0.001340483);
            values["W2ftlb/s"] = QString::number(value * 0.737562149);
            values["W2GW"] = QString::number(value * 0.000000001);
            values["W2kW"] = QString::number(value * 0.001);
            values["W2hp"] = QString::number(value * 0.001359622);
            values["W2MW"] = QString::number(value * 0.000001);
            values["W2hpb"] = QString::number(value * 0.000101942);
            values["W2TW"] = QString::number(value * 1e-12);
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
            values["atm2bar"] = QString::number(value * 1.01325);
            values["atm2dyn/cm2"] = QString::number(value * 1013250);
            values["atm2ftAgua"] = QString::number(value * 33.899524252);
            values["atm2hPa"] = QString::number(value * 1013.25);
            values["atm2inAgua"] = QString::number(value * 406.793746638);
            values["atm2MPa"] = QString::number(value * 0.101325);
            values["atm2kPa"] = QString::number(value * 101.325);
            values["atm2mbar"] = QString::number(value * 1013.25);
            values["atm2mmHg"] = QString::number(value * 760.002100179);
            values["atm2Pa"] = QString::number(value * 101325);
            values["atm2psi"] = QString::number(value * 14.695948775);
            values["atm2Torr"] = QString::number(value * 760);

            return values[from2to];

        case 1:
            values["bar2atm"] = QString::number(value * 0.986923267);
            values["bar2dyn/cm2"] = QString::number(value * 1000000);
            values["bar2ftAgua"] = QString::number(value * 33.456229215);
            values["bar2hPa"] = QString::number(value * 1000);
            values["bar2inAgua"] = QString::number(value * 401.474213311);
            values["bar2MPa"] = QString::number(value * 0.1);
            values["bar2kPa"] = QString::number(value * 100);
            values["bar2mbar"] = QString::number(value * 1000);
            values["bar2mmHg"] = QString::number(value * 750.063755419);
            values["bar2Pa"] = QString::number(value * 100000);
            values["bar2psi"] = QString::number(value * 14.503773773);
            values["bar2Torr"] = QString::number(value * 750.061682704);

            return values[from2to];

        case 2:
            values["dyn/cm22bar"] = QString::number(value * 0.000001);
            values["dyn/cm22atm"] = QString::number(value * 0.000000987);
            values["dyn/cm22ftAgua"] = QString::number(value * 0.000033456);
            values["dyn/cm22hPa"] = QString::number(value * 0.001);
            values["dyn/cm22inAgua"] = QString::number(value * 0.000401474);
            values["dyn/cm22MPa"] = QString::number(value * 0.0000001);
            values["dyn/cm22kPa"] = QString::number(value * 0.0001);
            values["dyn/cm22mbar"] = QString::number(value * 0.001);
            values["dyn/cm22mmHg"] = QString::number(value * 0.000750064);
            values["dyn/cm22Pa"] = QString::number(value * 0.1);
            values["dyn/cm22psi"] = QString::number(value * 0.000014504);
            values["dyn/cm22Torr"] = QString::number(value * 0.000750062);

            return values[from2to];

        case 3:
            values["ftAgua2bar"] = QString::number(value * 0.0298898);
            values["ftAgua2dyn/cm2"] = QString::number(value * 29889.8);
            values["ftAgua2atm"] = QString::number(value * 0.029498939);
            values["ftAgua2hPa"] = QString::number(value * 29.8898);
            values["ftAgua2inAgua"] = QString::number(value * 11.999983941);
            values["ftAgua2MPa"] = QString::number(value * 0.00298898);
            values["ftAgua2kPa"] = QString::number(value * 2.98898);
            values["ftAgua2mbar"] = QString::number(value * 29.8898);
            values["ftAgua2mmHg"] = QString::number(value * 22.419255637);
            values["ftAgua2Pa"] = QString::number(value * 2988.98);
            values["ftAgua2psi"] = QString::number(value * 0.433514897);
            values["ftAgua2Torr"] = QString::number(value * 22.419193684);

            return values[from2to];

        case 4:
            values["hPa2bar"] = QString::number(value * 0.001);
            values["hPa2dyn/cm2"] = QString::number(value * 1000);
            values["hPa2ftAgua"] = QString::number(value * 0.033456229);
            values["hPa2atm"] = QString::number(value * 0.000986923);
            values["hPa2inAgua"] = QString::number(value * 0.401474213);
            values["hPa2MPa"] = QString::number(value * 0.0001);
            values["hPa2kPa"] = QString::number(value * 0.1);
            values["hPa2mbar"] = QString::number(value * 1);
            values["hPa2mmHg"] = QString::number(value * 0.750063755);
            values["hPa2Pa"] = QString::number(value * 100);
            values["hPa2psi"] = QString::number(value * 0.014503774);
            values["hPa2Torr"] = QString::number(value * 0.750061683);

            return values[from2to];

        case 5:
            values["inAgua2bar"] = QString::number(value * 0.00249082);
            values["inAgua2dyn/cm2"] = QString::number(value * 2490.82);
            values["inAgua2ftAgua"] = QString::number(value * 0.083333445);
            values["inAgua2hPa"] = QString::number(value * 2.49082);
            values["inAgua2atm"] = QString::number(value * 0.002458248);
            values["inAgua2MPa"] = QString::number(value * 0.000249082);
            values["inAgua2kPa"] = QString::number(value * 0.249082);
            values["inAgua2mbar"] = QString::number(value * 2.49082);
            values["inAgua2mmHg"] = QString::number(value * 1.868273803);
            values["inAgua2Pa"] = QString::number(value * 249.082);
            values["inAgua2psi"] = QString::number(value * 0.03612629);
            values["inAgua2Torr"] = QString::number(value * 1.868268641);

            return values[from2to];

        case 6:
            values["MPa2bar"] = QString::number(value * 10);
            values["MPa2dyn/cm2"] = QString::number(value * 10000000);
            values["MPa2ftAgua"] = QString::number(value * 334.562292153);
            values["MPa2hPa"] = QString::number(value * 10000);
            values["MPa2inAgua"] = QString::number(value * 4014.742133113);
            values["MPa2atm"] = QString::number(value * 9.869232667);
            values["MPa2kPa"] = QString::number(value * 1000);
            values["MPa2mbar"] = QString::number(value * 10000);
            values["MPa2mmHg"] = QString::number(value * 7500.637554192);
            values["MPa2Pa"] = QString::number(value * 1000000);
            values["MPa2psi"] = QString::number(value * 145.03773773);
            values["MPa2Torr"] = QString::number(value * 7500.61682704);

            return values[from2to];

        case 7:
            values["kPa2bar"] = QString::number(value * 0.01);
            values["kPa2dyn/cm2"] = QString::number(value * 10000);
            values["kPa2ftAgua"] = QString::number(value * 0.334562292);
            values["kPa2hPa"] = QString::number(value * 10);
            values["kPa2inAgua"] = QString::number(value * 4.014742133);
            values["kPa2MPa"] = QString::number(value * 0.001);
            values["kPa2atm"] = QString::number(value * 0.009869233);
            values["kPa2mbar"] = QString::number(value * 10);
            values["kPa2mmHg"] = QString::number(value * 7.500637554);
            values["kPa2Pa"] = QString::number(value * 1000);
            values["kPa2psi"] = QString::number(value * 0.145037738);
            values["kPa2Torr"] = QString::number(value * 7.500616827);

            return values[from2to];

        case 8:
            values["mbar2bar"] = QString::number(value * 0.001);
            values["mbar2dyn/cm2"] = QString::number(value * 1000);
            values["mbar2ftAgua"] = QString::number(value * 0.033456229);
            values["mbar2hPa"] = QString::number(value * 1);
            values["mbar2inAgua"] = QString::number(value * 0.401474213);
            values["mbar2MPa"] = QString::number(value * 0.0001);
            values["mbar2kPa"] = QString::number(value * 0.1);
            values["mbar2atm"] = QString::number(value * 0.000986923);
            values["mbar2mmHg"] = QString::number(value * 0.750063755);
            values["mbar2Pa"] = QString::number(value * 100);
            values["mbar2psi"] = QString::number(value * 0.014503774);
            values["mbar2Torr"] = QString::number(value * 0.750061683);

            return values[from2to];

        case 9:
            values["mmHg2bar"] = QString::number(value * 0.00133322);
            values["mmHg2dyn/cm2"] = QString::number(value * 1333.22);
            values["mmHg2ftAgua"] = QString::number(value * 0.044604514);
            values["mmHg2hPa"] = QString::number(value * 1.33322);
            values["mmHg2inAgua"] = QString::number(value * 0.535253451);
            values["mmHg2MPa"] = QString::number(value * 0.000133322);
            values["mmHg2kPa"] = QString::number(value * 0.133322);
            values["mmHg2mbar"] = QString::number(value * 1.33322);
            values["mmHg2atm"] = QString::number(value * 0.001315786);
            values["mmHg2Pa"] = QString::number(value * 133.322);
            values["mmHg2psi"] = QString::number(value * 0.019336721);
            values["mmHg2Torr"] = QString::number(value * 0.999997237);

            return values[from2to];

        case 10:
            values["Pa2bar"] = QString::number(value * 0.00001);
            values["Pa2dyn/cm2"] = QString::number(value * 10);
            values["Pa2ftAgua"] = QString::number(value * 0.000334562);
            values["Pa2hPa"] = QString::number(value * 0.01);
            values["Pa2inAgua"] = QString::number(value * 0.004014742);
            values["Pa2MPa"] = QString::number(value * 0.000001);
            values["Pa2kPa"] = QString::number(value * 0.001);
            values["Pa2mbar"] = QString::number(value * 0.01);
            values["Pa2mmHg"] = QString::number(value * 0.007500638);
            values["Pa2atm"] = QString::number(value * 0.000009869);
            values["Pa2psi"] = QString::number(value * 0.000145038);
            values["Pa2Torr"] = QString::number(value * 0.007500617);

            return values[from2to];

        case 11:
            values["psi2bar"] = QString::number(value * 0.068947573);
            values["psi2dyn/cm2"] = QString::number(value * 68947.572931783);
            values["psi2ftAgua"] = QString::number(value * 2.306725804);
            values["psi2hPa"] = QString::number(value * 68.947572932);
            values["psi2inAgua"] = QString::number(value * 27.680672603);
            values["psi2MPa"] = QString::number(value * 0.006894757);
            values["psi2kPa"] = QString::number(value * 6.894757293);
            values["psi2mbar"] = QString::number(value * 68.947572932);
            values["psi2mmHg"] = QString::number(value * 51.71507548);
            values["psi2Pa"] = QString::number(value * 6894.757293178);
            values["psi2atm"] = QString::number(value * 0.068045964);
            values["psi2Torr"] = QString::number(value * 51.714932572);

            return values[from2to];

        case 12:
            values["Torr2bar"] = QString::number(value * 0.001333224);
            values["Torr2dyn/cm2"] = QString::number(value * 1333.223684211);
            values["Torr2ftAgua"] = QString::number(value * 0.044604637);
            values["Torr2hPa"] = QString::number(value * 1.333223684);
            values["Torr2inAgua"] = QString::number(value * 0.53525493);
            values["Torr2MPa"] = QString::number(value * 0.000133322);
            values["Torr2kPa"] = QString::number(value * 0.133322368);
            values["Torr2mbar"] = QString::number(value * 1.333223684);
            values["Torr2mmHg"] = QString::number(value * 1.000002763);
            values["Torr2Pa"] = QString::number(value * 133.322368421);
            values["Torr2psi"] = QString::number(value * 0.019336775);
            values["Torr2atm"] = QString::number(value * 0.001315789);

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
            values["ft/s2km/h"] = QString::number(value * 1.09728);
            values["ft/s2knot"] = QString::number(value * 1.184967603);
            values["ft/s2mach"] = QString::number(value * 0.000887078);
            values["ft/s2mph"] = QString::number(value * 0.681818182);
            values["ft/s2m/s"] = QString::number(value * 0.3048);

            return values[from2to];

        case 1:
            values["km/h2ft/s"] = QString::number(value * 0.911344415);
            values["km/h2knot"] = QString::number(value * 0.539956803);
            values["km/h2mach"] = QString::number(value * 0.000808434);
            values["km/h2mph"] = QString::number(value * 0.621371192);
            values["km/h2m/s"] = QString::number(value * 0.277777778);

            return values[from2to];

        case 2:
            values["knot2km/h"] = QString::number(value * 1.852);
            values["knot2ft/s"] = QString::number(value * 1.687809857);
            values["knot2mach"] = QString::number(value * 0.001497219);
            values["knot2mph"] = QString::number(value * 1.150779448);
            values["knot2m/s"] = QString::number(value * 0.514444444);

            return values[from2to];

        case 3:
            values["mach2km/h"] = QString::number(value * 1236.96);
            values["mach2knot"] = QString::number(value * 667.904967603);
            values["mach2ft/s"] = QString::number(value * 1127.296587927);
            values["mach2mph"] = QString::number(value * 768.61130995);
            values["mach2m/s"] = QString::number(value * 343.6);

            return values[from2to];

        case 4:
            values["mph2km/h"] = QString::number(value * 1.609344);
            values["mph2knot"] = QString::number(value * 0.868976242);
            values["mph2mach"] = QString::number(value * 0.001301048);
            values["mph2ft/s"] = QString::number(value * 1.466666667);
            values["mph2m/s"] = QString::number(value * 0.44704);

            return values[from2to];

        case 5:
            values["m/s2km/h"] = QString::number(value * 3.6);
            values["m/s2knot"] = QString::number(value * 1.943844492);
            values["m/s2mach"] = QString::number(value * 0.002910361);
            values["m/s2mph"] = QString::number(value * 2.236936292);
            values["m/s2ft/s"] = QString::number(value * 3.280839895);

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
            values["K2R"] = QString::number(value * 1.8);

            return values[from2to];
        case 3:
            values["R2C"] =
                QString::number((value - 491.67) * 0.5555555555555556);
            values["R2F"] = QString::number(value - 459.67);
            values["R2K"] = QString::number(value * 0.5555555555555556);

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
            values["day2hr"] = QString::number(value * 24);
            values["day2us"] = QString::number(value * 8.64e10);
            values["day2min"] = QString::number(value * 1440);
            values["day2ms"] = QString::number(value * 86400000);
            values["day2ns"] = QString::number(value * 8.64e+13);
            values["day2s"] = QString::number(value * 86400);
            values["day2yr"] = QString::number(value * 0.002739726);
            values["day2wk"] = QString::number(value * 0.142857143);

            return values[from2to];

        case 1:
            values["hr2day"] = QString::number(value * 0.041666667);
            values["hr2us"] = QString::number(value * 3.6e9);
            values["hr2min"] = QString::number(value * 60);
            values["hr2ms"] = QString::number(value * 3600000);
            values["hr2ns"] = QString::number(value * 3.6e12);
            values["hr2s"] = QString::number(value * 3600);
            values["hr2yr"] = QString::number(value * 0.000114155);
            values["hr2wk"] = QString::number(value * 0.005952381);

            return values[from2to];

        case 2:
            values["us2hr"] = QString::number(value * 2.777777778e-10);
            values["us2day"] = QString::number(value * 1.157407407e-11);
            values["us2min"] = QString::number(value * 0.000000017);
            values["us2ms"] = QString::number(value * 0.001);
            values["us2ns"] = QString::number(value * 1000);
            values["us2s"] = QString::number(value * 0.000001);
            values["us2yr"] = QString::number(value * 3.170979198e-14);
            values["us2wk"] = QString::number(value * 1.653439153e-12);

            return values[from2to];

        case 3:
            values["min2hr"] = QString::number(value * 0.016666667);
            values["min2us"] = QString::number(value * 60000000);
            values["min2day"] = QString::number(value * 0.000694444);
            values["min2ms"] = QString::number(value * 60000);
            values["min2ns"] = QString::number(value * 6e10);
            values["min2s"] = QString::number(value * 60);
            values["min2yr"] = QString::number(value * 0.000001903);
            values["min2wk"] = QString::number(value * 0.000099206);

            return values[from2to];

        case 4:
            values["ms2hr"] = QString::number(value * 0.000000278);
            values["ms2us"] = QString::number(value * 1000);
            values["ms2min"] = QString::number(value * 0.000016667);
            values["ms2day"] = QString::number(value * 0.000000012);
            values["ms2ns"] = QString::number(value * 1000000);
            values["ms2s"] = QString::number(value * 0.001);
            values["ms2yr"] = QString::number(value * 3.170979198e-11);
            values["ms2wk"] = QString::number(value * 0.000000002);

            return values[from2to];

        case 5:
            values["ns2hr"] = QString::number(value * 2.777777778e-13);
            values["ns2us"] = QString::number(value * 0.001);
            values["ns2min"] = QString::number(value * 1.666666667e-11);
            values["ns2ms"] = QString::number(value * 0.000001);
            values["ns2day"] = QString::number(value * 1.157407407e-14);
            values["ns2s"] = QString::number(value * 0.000000001);
            values["ns2yr"] = QString::number(value * 3.170979198e-17);
            values["ns2wk"] = QString::number(value * 1.653439153e-15);

            return values[from2to];

        case 6:
            values["s2hr"] = QString::number(value * 0.000277778);
            values["s2us"] = QString::number(value * 1000000);
            values["s2min"] = QString::number(value * 0.016666667);
            values["s2ms"] = QString::number(value * 1000);
            values["s2ns"] = QString::number(value * 1000000000);
            values["s2day"] = QString::number(value * 0.000011574);
            values["s2yr"] = QString::number(value * 0.000000032);
            values["s2wk"] = QString::number(value * 0.000001653);

            return values[from2to];

        case 7:
            values["yr2hr"] = QString::number(value * 8760);
            values["yr2us"] = QString::number(value * 3.1536e13);
            values["yr2min"] = QString::number(value * 525600);
            values["yr2ms"] = QString::number(value * 3.1536e13);
            values["yr2ns"] = QString::number(value * 3.1536e16);
            values["yr2s"] = QString::number(value * 31536000);
            values["yr2day"] = QString::number(value * 365);
            values["yr2wk"] = QString::number(value * 52.142857143);

            return values[from2to];

        case 8:
            values["wk2hr"] = QString::number(value * 168);
            values["wk2us"] = QString::number(value * 6.048e11);
            values["wk2min"] = QString::number(value * 10080);
            values["wk2ms"] = QString::number(value * 604800000);
            values["wk2ns"] = QString::number(value * 6.048e14);
            values["wk2s"] = QString::number(value * 604800);
            values["wk2yr"] = QString::number(value * 0.019178082);
            values["wk2day"] = QString::number(value * 7);

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
            values["dyn-cm2dyn-m"] = QString::number(value * 0.01);
            values["dyn-cm2gf-m"] = QString::number(value * 0.001019716);
            values["dyn-cm2kgf-m"] = QString::number(value * 0.00000001);
            values["dyn-cm2N-cm"] = QString::number(value * 0.00001);
            values["dyn-cm2N-m"] = QString::number(value * 0.0000001);
            values["dyn-cm2ozf-in"] = QString::number(value * 0.000014161);
            values["dyn-cm2lbf-ft"] = QString::number(value * 0.000000074);
            values["dyn-cm2lbf-in"] = QString::number(value * 0.000000885);

            return values[from2to];

        case 1:
            values["dyn-m2dyn-cm"] = QString::number(value * 100);
            values["dyn-m2gf-m"] = QString::number(value * 0.101971621);
            values["dyn-m2kgf-m"] = QString::number(value * 0.00000102);
            values["dyn-m2N-cm"] = QString::number(value * 0.001);
            values["dyn-m2N-m"] = QString::number(value * 0.00001);
            values["dyn-m2ozf-in"] = QString::number(value * 0.001416119);
            values["dyn-m2lbf-ft"] = QString::number(value * 0.000007376);
            values["dyn-m2lbf-in"] = QString::number(value * 0.000088507);

            return values[from2to];

        case 2:
            values["gf-m2dyn-m"] = QString::number(value * 980.665);
            values["gf-m2dyn-cm"] = QString::number(value * 98066.5);
            values["gf-m2kgf-m"] = QString::number(value * 0.001);
            values["gf-m2N-cm"] = QString::number(value * 0.980665);
            values["gf-m2N-m"] = QString::number(value * 0.00980665);
            values["gf-m2ozf-in"] = QString::number(value * 1.388738623);
            values["gf-m2lbf-ft"] = QString::number(value * 0.007233014);
            values["gf-m2lbf-in"] = QString::number(value * 0.086796163);

            return values[from2to];

        case 3:
            values["kgf-m2dyn-m"] = QString::number(value * 980665);
            values["kgf-m2gf-m"] = QString::number(value * 1000);
            values["kgf-m2dyn-cm"] = QString::number(value * 98066500);
            values["kgf-m2N-cm"] = QString::number(value * 980.665);
            values["kgf-m2N-m"] = QString::number(value * 9.80665);
            values["kgf-m2ozf-in"] = QString::number(value * 1388.738622898);
            values["kgf-m2lbf-ft"] = QString::number(value * 7.233013576);
            values["kgf-m2lbf-in"] = QString::number(value * 86.796162907);

            return values[from2to];

        case 4:
            values["N-cm2dyn-m"] = QString::number(value * 1000);
            values["N-cm2gf-m"] = QString::number(value * 1.019716213);
            values["N-cm2kgf-m"] = QString::number(value * 0.001019716);
            values["N-cm2dyn-cm"] = QString::number(value * 100000);
            values["N-cm2N-m"] = QString::number(value * 0.01);
            values["N-cm2ozf-in"] = QString::number(value * 1.416119289);
            values["N-cm2lbf-ft"] = QString::number(value * 0.007375621);
            values["N-cm2lbf-in"] = QString::number(value * 0.088507455);

            return values[from2to];

        case 5:
            values["N-m2dyn-m"] = QString::number(value * 100000);
            values["N-m2gf-m"] = QString::number(value * 101.971621298);
            values["N-m2kgf-m"] = QString::number(value * 0.101971621);
            values["N-m2N-cm"] = QString::number(value * 100);
            values["N-m2dyn-cm"] = QString::number(value * 10000000);
            values["N-m2ozf-in"] = QString::number(value * 141.611928936);
            values["N-m2lbf-ft"] = QString::number(value * 0.737562121);
            values["N-m2lbf-in"] = QString::number(value * 8.850745454);

            return values[from2to];

        case 6:
            values["ozf-in2dyn-m"] = QString::number(value * 706.1552);
            values["ozf-in2gf-m"] = QString::number(value * 0.720077906);
            values["ozf-in2kgf-m"] = QString::number(value * 0.000720078);
            values["ozf-in2N-cm"] = QString::number(value * 0.7061552);
            values["ozf-in2N-m"] = QString::number(value * 0.007061552);
            values["ozf-in2dyn-cm"] = QString::number(value * 70615.52);
            values["ozf-in2lbf-ft"] = QString::number(value * 0.005208333);
            values["ozf-in2lbf-in"] = QString::number(value * 0.062499999);

            return values[from2to];

        case 7:
            values["lbf-ft2dyn-m"] = QString::number(value * 135581.8);
            values["lbf-ft2gf-m"] = QString::number(value * 138.254959645);
            values["lbf-ft2kgf-m"] = QString::number(value * 0.13825496);
            values["lbf-ft2N-cm"] = QString::number(value * 135.5818);
            values["lbf-ft2N-m"] = QString::number(value * 1.355818);
            values["lbf-ft2ozf-in"] = QString::number(value * 192.000002266);
            values["lbf-ft2dyn-cm"] = QString::number(value * 13558180);
            values["lbf-ft2lbf-in"] = QString::number(value * 12);

            return values[from2to];

        case 8:
            values["lbf-in2dyn-m"] = QString::number(value * 11298.483333333);
            values["lbf-in2gf-m"] = QString::number(value * 11.521246637);
            values["lbf-in2kgf-m"] = QString::number(value * 0.011521247);
            values["lbf-in2N-cm"] = QString::number(value * 11.298483333);
            values["lbf-in2N-m"] = QString::number(value * 0.112984833);
            values["lbf-in2ozf-in"] = QString::number(value * 16.000000189);
            values["lbf-in2lbf-ft"] = QString::number(value * 0.083333333);
            values["lbf-in2dyn-cm"] = QString::number(value * 1129848.3333333);

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
                                     << "gal"
                                     << "oz"
                                     << "qt"
                                     << "mm3");
        switch (unitOptions.indexOf(unit)) {
        case 0:
            values["cl2cm3"] = QString::number(value * 10);
            values["cl2f3"] = QString::number(value * 0.000353147);
            values["cl2in3"] = QString::number(value * 0.610237441);
            values["cl2km3"] = QString::number(value * 1e-14);
            values["cl2m3"] = QString::number(value * 0.00001);
            values["cl2mi3"] = QString::number(value * 2.399127586e-15);
            values["cl2yd3"] = QString::number(value * 0.00001308);
            values["cl2l"] = QString::number(value * 0.01);
            values["cl2ml"] = QString::number(value * 10);
            values["cl2gal"] = QString::number(value * 0.002641721);
            values["cl2oz"] = QString::number(value * 0.338140227);
            values["cl2qt"] = QString::number(value * 0.010566882);
            values["cl2mm3"] = QString::number(value * 10000);

            return values[from2to];

        case 1:
            values["cm32cl"] = QString::number(value * 0.1);
            values["cm32f3"] = QString::number(value * 0.000035315);
            values["cm32in3"] = QString::number(value * 0.061023744);
            values["cm32km3"] = QString::number(value * 1e-15);
            values["cm32m3"] = QString::number(value * 0.000001);
            values["cm32mi3"] = QString::number(value * 2.399127586e-16);
            values["cm32yd3"] = QString::number(value * 0.000001308);
            values["cm32l"] = QString::number(value * 0.001);
            values["cm32ml"] = QString::number(value * 1);
            values["cm32gal"] = QString::number(value * 0.000264172);
            values["cm32oz"] = QString::number(value * 0.033814023);
            values["cm32qt"] = QString::number(value * 0.001056688);
            values["cm32mm3"] = QString::number(value * 1000);

            return values[from2to];

        case 2:
            values["f32cm3"] = QString::number(value * 28316.846592);
            values["f32cl"] = QString::number(value * 2831.6846592);
            values["f32in3"] = QString::number(value * 1728);
            values["f32km3"] = QString::number(value * 2.831684659e-11);
            values["f32m3"] = QString::number(value * 0.028316847);
            values["f32mi3"] = QString::number(value * 6.79357278e-12);
            values["f32yd3"] = QString::number(value * 0.037037037);
            values["f32l"] = QString::number(value * 28.316846592);
            values["f32ml"] = QString::number(value * 28316.846592);
            values["f32gal"] = QString::number(value * 7.480519481);
            values["f32oz"] = QString::number(value * 957.506493506);
            values["f32qt"] = QString::number(value * 29.922077922);
            values["f32mm3"] = QString::number(value * 28316846.592);

            return values[from2to];

        case 3:
            values["in32cm3"] = QString::number(value * 16.387064);
            values["in32f3"] = QString::number(value * 0.000578704);
            values["in32cl"] = QString::number(value * 1.6387064);
            values["in32km3"] = QString::number(value * 1.6387064e-14);
            values["in32m3"] = QString::number(value * 0.000016387);
            values["in32mi3"] = QString::number(value * 3.931465729e-15);
            values["in32yd3"] = QString::number(value * 0.000021433);
            values["in32l"] = QString::number(value * 0.016387064);
            values["in32ml"] = QString::number(value * 16.387064);
            values["in32gal"] = QString::number(value * 0.004329004);
            values["in32oz"] = QString::number(value * 0.554112554);
            values["in32qt"] = QString::number(value * 0.017316017);
            values["in32mm3"] = QString::number(value * 16387.064);

            return values[from2to];

        case 4:
            values["km32cm3"] = QString::number(value * 1e15);
            values["km32f3"] = QString::number(value * 3.531466672e10);
            values["km32in3"] = QString::number(value * 6.102374409e13);
            values["km32cl"] = QString::number(value * 1e14);
            values["km32m3"] = QString::number(value * 1000000000);
            values["km32mi3"] = QString::number(value * 0.239912759);
            values["km32yd3"] = QString::number(value * 1307950619.3144);
            values["km32l"] = QString::number(value * 1e12);
            values["km32ml"] = QString::number(value * 1e15);
            values["km32gal"] = QString::number(value * 2.641720524e11);
            values["km32oz"] = QString::number(value * 3.38140227e13);
            values["km32qt"] = QString::number(value * 1.056688209e12);
            values["km32mm3"] = QString::number(value * 1e18);

            return values[from2to];

        case 5:
            values["m32cm3"] = QString::number(value * 1000000);
            values["m32f3"] = QString::number(value * 35.314666721);
            values["m32in3"] = QString::number(value * 61023.744094732);
            values["m32km3"] = QString::number(value * 0.000000001);
            values["m32cl"] = QString::number(value * 100000);
            values["m32mi3"] = QString::number(value * 2.399127586e-10);
            values["m32yd3"] = QString::number(value * 1.307950619);
            values["m32l"] = QString::number(value * 1000);
            values["m32ml"] = QString::number(value * 1000000);
            values["m32gal"] = QString::number(value * 264.172052358);
            values["m32oz"] = QString::number(value * 33814.022701843);
            values["m32qt"] = QString::number(value * 1056.688209433);
            values["m32mm3"] = QString::number(value * 1000000000.0);

            return values[from2to];

        case 6:
            values["mi32cm3"] = QString::number(value * 4.168181825e15);
            values["mi32f3"] = QString::number(value * 1.47197952e11);
            values["mi32in3"] = QString::number(value * 2.543580611e14);
            values["mi32km3"] = QString::number(value * 4.168181825);
            values["mi32m3"] = QString::number(value * 4168181825.4406);
            values["mi32cl"] = QString::number(value * 4.168181825e14);
            values["mi32yd3"] = QString::number(value * 5451776000);
            values["mi32l"] = QString::number(value * 4.168181825e12);
            values["mi32ml"] = QString::number(value * 4.168181825e15);
            values["mi32gal"] = QString::number(value * 1.101117147e12);
            values["mi32oz"] = QString::number(value * 1.409429949e14);
            values["mi32qt"] = QString::number(value * 4.40446859e12);
            values["mi32mm3"] = QString::number(value * 4.168181825e18);

            return values[from2to];

        case 7:
            values["yd32cm3"] = QString::number(value * 764554.857984);
            values["yd32f3"] = QString::number(value * 27);
            values["yd32in3"] = QString::number(value * 46656);
            values["yd32km3"] = QString::number(value * 7.64554858e-10);
            values["yd32m3"] = QString::number(value * 0.764554858);
            values["yd32mi3"] = QString::number(value * 1.834264651e-10);
            values["yd32cl"] = QString::number(value * 76455.4857984);
            values["yd32l"] = QString::number(value * 764.554857984);
            values["yd32ml"] = QString::number(value * 764554.857984);
            values["yd32gal"] = QString::number(value * 201.974025974);
            values["yd32oz"] = QString::number(value * 25852.675324675);
            values["yd32qt"] = QString::number(value * 807.896103896);
            values["yd32mm3"] = QString::number(value * 764554857.984);

            return values[from2to];

        case 8:
            values["l2cm3"] = QString::number(value * 1000);
            values["l2f3"] = QString::number(value * 0.035314667);
            values["l2in3"] = QString::number(value * 61.023744095);
            values["l2km3"] = QString::number(value * 1e-12);
            values["l2m3"] = QString::number(value * 0.001);
            values["l2mi3"] = QString::number(value * 2.399127586e-13);
            values["l2yd3"] = QString::number(value * 0.001307951);
            values["l2cl"] = QString::number(value * 100);
            values["l2ml"] = QString::number(value * 1000);
            values["l2gal"] = QString::number(value * 0.264172052);
            values["l2oz"] = QString::number(value * 33.814022702);
            values["l2qt"] = QString::number(value * 1.056688209);
            values["l2mm3"] = QString::number(value * 1000000);

            return values[from2to];

        case 9:
            values["ml2cm3"] = QString::number(value * 1);
            values["ml2f3"] = QString::number(value * 0.000035315);
            values["ml2in3"] = QString::number(value * 0.061023744);
            values["ml2km3"] = QString::number(value * 1e-15);
            values["ml2m3"] = QString::number(value * 0.000001);
            values["ml2mi3"] = QString::number(value * 2.399127586e-16);
            values["ml2yd3"] = QString::number(value * 0.000001308);
            values["ml2l"] = QString::number(value * 0.001);
            values["ml2cl"] = QString::number(value * 0.1);
            values["ml2gal"] = QString::number(value * 0.000264172);
            values["ml2oz"] = QString::number(value * 0.033814023);
            values["ml2qt"] = QString::number(value * 0.001056688);
            values["ml2mm3"] = QString::number(value * 1000);

            return values[from2to];

        case 10:
            values["gal2cm3"] = QString::number(value * 3785.411784);
            values["gal2f3"] = QString::number(value * 0.133680556);
            values["gal2in3"] = QString::number(value * 231);
            values["gal2km3"] = QString::number(value * 3.785411784e-12);
            values["gal2m3"] = QString::number(value * 0.003785412);
            values["gal2mi3"] = QString::number(value * 9.081685835e-13);
            values["gal2yd3"] = QString::number(value * 0.004951132);
            values["gal2l"] = QString::number(value * 3.785411784);
            values["gal2ml"] = QString::number(value * 3785.411784);
            values["gal2cl"] = QString::number(value * 378.5411784);
            values["gal2oz"] = QString::number(value * 128);
            values["gal2qt"] = QString::number(value * 4);
            values["gal2mm3"] = QString::number(value * 3785411.784);

            return values[from2to];

        case 11:
            values["oz2cm3"] = QString::number(value * 29.573529563);
            values["oz2f3"] = QString::number(value * 0.001044379);
            values["oz2in3"] = QString::number(value * 1.8046875);
            values["oz2km3"] = QString::number(value * 2.957352956e-14);
            values["oz2m3"] = QString::number(value * 0.000029574);
            values["oz2mi3"] = QString::number(value * 7.095067058e-15);
            values["oz2yd3"] = QString::number(value * 0.000038681);
            values["oz2l"] = QString::number(value * 0.02957353);
            values["oz2ml"] = QString::number(value * 29.573529563);
            values["oz2gal"] = QString::number(value * 0.0078125);
            values["oz2cl"] = QString::number(value * 2.957352956);
            values["oz2qt"] = QString::number(value * 0.03125);
            values["oz2mm3"] = QString::number(value * 29573.5295625);

            return values[from2to];

        case 12:
            values["qt2cm3"] = QString::number(value * 946.352946);
            values["qt2f3"] = QString::number(value * 0.033420139);
            values["qt2in3"] = QString::number(value * 57.75);
            values["qt2km3"] = QString::number(value * 9.46352946e-13);
            values["qt2m3"] = QString::number(value * 0.000946353);
            values["qt2mi3"] = QString::number(value * 2.270421459e-13);
            values["qt2yd3"] = QString::number(value * 0.001237783);
            values["qt2l"] = QString::number(value * 0.946352946);
            values["qt2ml"] = QString::number(value * 946.352946);
            values["qt2gal"] = QString::number(value * 0.25);
            values["qt2oz"] = QString::number(value * 32);
            values["qt2cl"] = QString::number(value * 94.6352946);
            values["qt2mm3"] = QString::number(value * 946352.946);

            return values[from2to];

        case 13:
            values["mm32cm3"] = QString::number(value * 0.001);
            values["mm32f3"] = QString::number(value * 0.000000035);
            values["mm32in3"] = QString::number(value * 0.000061024);
            values["mm32km3"] = QString::number(value * 1e-18);
            values["mm32m3"] = QString::number(value * 0.000000001);
            values["mm32mi3"] = QString::number(value * 2.399127586e-19);
            values["mm32yd3"] = QString::number(value * 0.000000001);
            values["mm32l"] = QString::number(value * 0.000001);
            values["mm32ml"] = QString::number(value * 0.001);
            values["mm32gal"] = QString::number(value * 0.000000264);
            values["mm32oz"] = QString::number(value * 0.000033814);
            values["mm32cl"] = QString::number(value * 0.0001);
            values["mm32qt"] = QString::number(value * 0.000001057);

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
