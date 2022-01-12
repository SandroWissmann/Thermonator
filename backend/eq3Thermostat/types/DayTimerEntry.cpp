#include "DayTimerEntry.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

DayTimerEntry::DayTimerEntry(const Time &time, const Temperature &temperature)
    : mTime{time}, mTemperature{temperature}
{
}

DayTimerEntry
DayTimerEntry::fromEncodedBytes(const std::vector<unsigned char> &bytes)
{
    constexpr auto expectdSize = 2;
    if (bytes.size() != expectdSize) {
        qWarning() << Q_FUNC_INFO << "Invalid count of bytes: " << bytes.size();
        return DayTimerEntry();
    }

    Temperature temperature{bytes[0]};
    if (!temperature.isValid()) {
        qWarning() << Q_FUNC_INFO << "Invalid Temperature:" << temperature;
        return DayTimerEntry();
    }

    auto time = Time::fromEncodedByte(bytes[1]);
    if (!time.isValid()) {
        qWarning() << Q_FUNC_INFO << "Invalid Time:" << time;
        return DayTimerEntry();
    }
    return DayTimerEntry{time, temperature};
}

Time DayTimerEntry::time() const
{
    return mTime;
}

Temperature DayTimerEntry::temperature() const
{
    return mTemperature;
}

bool DayTimerEntry::isValid() const
{
    if (!mTime.isValid()) {
        return false;
    }
    if (!mTemperature.isValid()) {
        return false;
    }
    return true;
}

QDebug operator<<(QDebug debug, const DayTimerEntry &dayTimerEntry)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << '(' << dayTimerEntry.time() << '/'
                    << dayTimerEntry.temperature();

    return debug;
}

} // namespace thermonator::eq3thermostat
