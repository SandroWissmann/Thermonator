#include "DayTimer.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

DayTimer::DayTimer(std::vector<DayTimerEntry> dayTimerEntries)
    : mDayTimerEntries{std::move(dayTimerEntries)}
{
    Q_ASSERT(isValid());
}

std::vector<DayTimerEntry> DayTimer::dayTimerEntries() const
{
    return mDayTimerEntries;
}

bool DayTimer::isValid() const
{
    if (mDayTimerEntries.size() <= 0) {
        return false;
    }
    if (mDayTimerEntries.size() > 7) {
        return false;
    }
    if (mDayTimerEntries.back().time().hour() != 24) {
        return false;
    }
    if (mDayTimerEntries.back().time().minute() != 0) {
        return false;
    }
    if (!timeIsAscendingInEntries(mDayTimerEntries)) {
        return false;
    }
    for (const auto &dayTimerEntry : mDayTimerEntries) {
        if (!dayTimerEntry.isValid()) {
            return false;
        }
    }
    return true;
}

bool DayTimer::timeIsAscendingInEntries(
    const std::vector<DayTimerEntry> &dayTimerEntries)
{
    int lastTimeInMinutes = 0;
    for (const auto &dayTimerEntry : dayTimerEntries) {
        auto timeInMinutes =
            dayTimerEntry.time().hour() * 60 + dayTimerEntry.time().minute();
        if (timeInMinutes < lastTimeInMinutes) {
            return false;
        }
        lastTimeInMinutes = timeInMinutes;
    }
    return true;
}

QDebug operator<<(QDebug debug, const DayTimer &dayTimer)
{
    QDebugStateSaver saver(debug);

    for (const auto &dayTimerEntry : dayTimer.dayTimerEntries()) {
        debug.nospace() << dayTimerEntry;
    }

    return debug;
}

} // namespace thermonator::eq3thermostat::types
