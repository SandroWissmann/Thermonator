#include "OpenWindowInterval.hpp"

namespace thermonator::eq3thermostat {

OpenWindowInterval::OpenWindowInterval(unsigned char byte)
    : mValue(decodeByte(byte))
{
}

OpenWindowInterval::OpenWindowInterval(int value) : mValue{makeValid(value)}
{
}

int OpenWindowInterval::value() const
{
    return mValue;
}

unsigned char OpenWindowInterval::encoded() const
{
    if (isValid()) {
        return static_cast<unsigned char>(mValue / 5);
    }
    // this is the factory value = 15 min
    return static_cast<unsigned char>(15 / 5);
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

int OpenWindowInterval::makeValid(int value)
{
    qDebug() << Q_FUNC_INFO << "interval" << value;

    constexpr auto minInterval = 0;
    constexpr auto maxInterval = 60;
    value = std::clamp(value, minInterval, maxInterval);

    int tmp = static_cast<int>((value / 5));
    value = static_cast<int>(tmp * 5);

    qDebug() << Q_FUNC_INFO << "valid interval" << value;
    return value;
}

QDebug operator<<(QDebug debug, const OpenWindowInterval &openWindowInterval)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << openWindowInterval.value() << " min";

    return debug;
}

} // namespace thermonator::eq3thermostat
