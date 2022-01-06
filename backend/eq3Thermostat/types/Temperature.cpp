#include "Temperature.hpp"

#include <algorithm> // std::clamp

namespace thermonator::eq3thermostat::types {

Temperature::Temperature(unsigned char byte) : mValue(decodeByte(byte))
{
}

Temperature::Temperature(double value) : mValue{makeValid(value)}
{
}

double Temperature::value() const
{
    return mValue;
}

unsigned char Temperature::encoded() const
{
    if (isValid() || isThermostatOnTemperature() ||
        isThermostatOffTemperature()) {
        return static_cast<unsigned char>(mValue * 2);
    }
    return 0;
}

bool Temperature::isValid() const
{
    if (mValue < 5.0) {
        return false;
    }
    if (mValue > 29.5) {
        return false;
    }
    return true;
}

bool Temperature::isThermostatOnTemperature() const
{
    if (mValue != 30.0) {
        return false;
    }
    return true;
}

bool Temperature::isThermostatOffTemperature() const
{
    if (mValue != 4.5) {
        return false;
    }
    return true;
}

double Temperature::decodeByte(unsigned char byte)
{
    auto temperature = (static_cast<int>(byte) / 2.0);
    return temperature;
}

double Temperature::makeValid(double value)
{
    qDebug() << Q_FUNC_INFO << "temperature" << value;

    constexpr auto minTemperature = 5.0;
    constexpr auto maxTemperature = 29.5;
    value = std::clamp(value, minTemperature, maxTemperature);

    int tmp = static_cast<int>((value * 2));
    value = static_cast<double>(tmp / 2.0);

    qDebug() << Q_FUNC_INFO << "valid temperature" << value;
    return value;
}

QDebug operator<<(QDebug debug, const Temperature &temperature)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << temperature.value() << " °C";

    return debug;
}

} // namespace thermonator::eq3thermostat::types
