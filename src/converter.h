#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>
#include <QStringList>
#include <QVariantMap>
#include <QtGlobal>
#include <math.h>

class QString;

constexpr double PI() { return 3.14159265358979323846; }

inline bool is_integer(const double val)
{
    return qFuzzyCompare(1 + std::floor(std::abs(val)), 1 + std::abs(val));
}
template <typename T> auto getType(T t) -> decltype(t)
{
    if (is_integer((t))) {
        return static_cast<qint64>(t);
    } else {
        return t;
    }
}

template <typename T> double convertdBm(T value)
{
    if (value == 0 || value < 0) {
        value = 0;
        return value;
    } else {
        return 10 * log10(static_cast<double>(value));
    }
}

template <typename T> double convertdBW(T value)
{
    if (value == 0 || value < 0) {
        return 0.0;
    } else {
        return 10 * log10(static_cast<double>(value));
    }
}

class Converter : public QObject
{

    Q_OBJECT
    Q_ENUMS(Units)

public:
    explicit Converter(QObject *parent = 0);

    enum Units {
        ACCELERATION,
        ANGLE,
        AREA,
        CURRENCY,
        DATASTORAGE,
        DENSITY,
        ENERGYANDWORK,
        FLOW,
        FORCE,
        FREQUENCY,
        FUELCONSUMPTION,
        LENGTH,
        MAGNETICFIELDSTRENGTH,
        MAGNETICFLUXDENSITY,
        MASS,
        POWER,
        PRESSURE,
        SPEED,
        TEMPERATURE,
        TIME,
        TORQUE,
        VOLUME
    };

    Q_INVOKABLE QString convert2(QString, QString, QString, QString) const;

    Q_INVOKABLE QString convert2Numbers(QString, QString, QString) const;

    Q_INVOKABLE void getCurrencies(QVariantMap);

protected:
    QStringList convOptions;
    QVariantMap currency_rate;
};

#endif // CONVERTER_H
