#include "ValvePosition.hpp"

namespace thermonator::eq3thermostat::types {

ValvePosition::ValvePosition(unsigned char byte) : mValue(decodeByte(byte))
{
}

double ValvePosition::value() const
{
    return mValue;
}

bool ValvePosition::isValid() const
{
    if (mValue < 0) {
        return false;
    }
    if (mValue > 100) {
        return false;
    }
    return true;
}

int ValvePosition::decodeByte(unsigned char byte)
{
    auto value = static_cast<int>(byte);
    return value;
}

QDebug operator<<(QDebug debug, const ValvePosition &valvePosition)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << valvePosition.value() << " %";

    return debug;
}

} // namespace thermonator::eq3thermostat::types
