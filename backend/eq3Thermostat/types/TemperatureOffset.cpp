#include "TemperatureOffset.hpp"

namespace thermonator::eq3thermostat::types {

TemperatureOffset::TemperatureOffset(unsigned char byte)
    : mValue(decodeByte(byte))
{
}

double TemperatureOffset::value() const
{
    return mValue;
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

QDebug operator<<(QDebug debug, const TemperatureOffset &temperatureOffset)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << temperatureOffset.value() << " °C";

    return debug;
}

} // namespace thermonator::eq3thermostat::types
