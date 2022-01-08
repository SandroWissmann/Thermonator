#include "DayTimerEntry.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

DayTimerEntry::DayTimerEntry(const Time &time, double temperature)
    : mTime{time}, mTemperature{temperature}
{
}

Time DayTimerEntry::time() const
{
    return mTime;
}

double DayTimerEntry::temperature() const
{
    return mTemperature;
}

bool DayTimerEntry::isValid() const
{
    // special case because QTime considers 24:00 invalid but we want that
    // time for convenience
    if ((mTime.hour() != 24 || mTime.minute() != 0) && !mTime.isValid()) {
        return false;
    }
    if (mTemperature < 5.0) {
        return false;
    }
    if (mTemperature > 29.5) {
        return false;
    }
    return true;
}

QDebug operator<<(QDebug debug, const DayTimerEntry &dayTimerEntry)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << '(' << dayTimerEntry.time() << '/'
                    << dayTimerEntry.temperature() << " °C)";

    return debug;
}

} // namespace thermonator::eq3thermostat
