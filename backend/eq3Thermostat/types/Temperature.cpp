#include "Temperature.hpp"

namespace thermonator::eq3thermostat::types {

Temperature::Temperature(unsigned char byte) : mValue(decodeByte(byte))
{
}

double Temperature::value() const
{
    return mValue;
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

double Temperature::decodeByte(unsigned char byte)
{
    auto temperature = (static_cast<int>(byte) / 2.0);
    return temperature;
}

QDebug operator<<(QDebug debug, const Temperature &temperature)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << temperature.value() << " °C";

    return debug;
}

} // namespace thermonator::eq3thermostat::types
