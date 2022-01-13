#include "DayTimer.hpp"

#include <QDebug>

#include "../../utility/EnumToString.hpp"

namespace thermonator::eq3thermostat {

DayTimer::DayTimer(DayOfWeek dayOfWeek, const DayTimerEntries &dayTimerEntries)
    : mDayOfWeek{dayOfWeek}, mDayTimerEntries{dayTimerEntries}
{
}

DayOfWeek DayTimer::dayOfWeek() const
{
    return mDayOfWeek;
}

DayTimerEntries DayTimer::dayTimerEntries() const
{
    return mDayTimerEntries;
}

bool DayTimer::isValid() const
{
    if (mDayOfWeek == DayOfWeek::invalid) {
        return false;
    }
    if (mDayTimerEntries.isValid()) {
        return false;
    }
    return true;
}

QDebug operator<<(QDebug debug, const DayTimer &dayTimer)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "dayOfWeek: "
                    << utility::enumToString(dayTimer.dayOfWeek()) << '\n';
    debug.nospace() << dayTimer.dayTimerEntries();

    return debug;
}

} // namespace thermonator::eq3thermostat
