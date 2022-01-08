#include "WeekTimer.hpp"

namespace thermonator::eq3thermostat {

bool WeekTimer::isValid()
{
    for (const auto &dayTimer : mWeekTimer) {
        if (!dayTimer.isValid()) {
            return false;
        }
    }
    return true;
}

bool WeekTimer::dayTimerIsValid(DayOfWeek dayOfWeek) const
{
    auto index = toIndex(dayOfWeek);
    return mWeekTimer[index].isValid();
}

void WeekTimer::setDayTimer(const DayTimerNotification &dayTimerNotification)
{
    auto dayOfWeek = dayTimerNotification.dayOfWeek();
    auto index = toIndex(dayOfWeek);

    if (mWeekTimer[index] == dayTimerNotification) {
        return;
    }
    mWeekTimer[index] = dayTimerNotification;
}

DayTimerNotification WeekTimer::dayTimer(DayOfWeek dayOfWeek) const
{
    auto index = toIndex(dayOfWeek);
    return mWeekTimer[index];
}

int WeekTimer::toIndex(DayOfWeek dayOfWeek) const
{
    return static_cast<int>(dayOfWeek);
}

} // namespace thermonator::eq3thermostat
