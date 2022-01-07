#include "TemperatureOffset.hpp"

namespace thermonator::eq3thermostat::types {

TemperatureOffset::TemperatureOffset(unsigned char byte)
    : mValue(decodeByte(byte))
{
}

TemperatureOffset::TemperatureOffset(double value) : mValue{makeValid(value)}
{
}

double TemperatureOffset::value() const
{
    return mValue;
}

unsigned char TemperatureOffset::encoded() const
{
    if (isValid()) {
        return static_cast<unsigned char>(mValue * 2) + 7;
    }
    // factory value = 0.0°C
    return 7;
}

bool TemperatureOffset::isValid() const
{
    if (mValue < -3.5) {
        return false;
    }
    if (mValue > 3.5) {
        return false;
    }
    return true;
}

double TemperatureOffset::decodeByte(unsigned char byte)
{
    auto temperatureOffset = (static_cast<int>(byte) - 7) / 2.0;
    return temperatureOffset;
}

double TemperatureOffset::makeValid(double value)
{
    qDebug() << Q_FUNC_INFO << "temperatureOffset" << value;

    constexpr auto minTemperatureOffset = -3.5;
    constexpr auto maxTemperatureOffset = 3.5;
    value = std::clamp(value, minTemperatureOffset, maxTemperatureOffset);

    int tmp = static_cast<int>((value * 2));
    value = static_cast<double>(tmp / 2.0);

    qDebug() << Q_FUNC_INFO << "valid temperatureOffset" << value;
    return value;
}

QDebug operator<<(QDebug debug, const TemperatureOffset &temperatureOffset)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << temperatureOffset.value() << " °C";

    return debug;
}

} // namespace thermonator::eq3thermostat::types
