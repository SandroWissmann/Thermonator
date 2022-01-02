#include "OpenWindowInterval.hpp"

namespace thermonator::eq3thermostat::types {

OpenWindowInterval::OpenWindowInterval(unsigned char byte)
    : mValue(decodeByte(byte))
{
}

int OpenWindowInterval::value() const
{
    return mValue;
}

bool OpenWindowInterval::isValid() const
{
    if (mValue < 0) {
        return false;
    }
    if (mValue > 60) {
        return false;
    }
    return true;
}

int OpenWindowInterval::decodeByte(unsigned char byte)
{
    auto openWindowInterval = (static_cast<int>(byte) * 5);
    return openWindowInterval;
}

QDebug operator<<(QDebug debug, const OpenWindowInterval &openWindowInterval)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << openWindowInterval.value() << " min";

    return debug;
}

} // namespace thermonator::eq3thermostat::types
