#include "WeekTimer.hpp"

namespace thermonator::eq3thermostat::types {

WeekTimer::WeekTimer(const std::array<DayTimer, 7> &weekTimer)
    : mWeekTimer{weekTimer}
{
}

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

void WeekTimer::setDayTimer(DayOfWeek dayOfWeek, const DayTimer &dayTimer)
{
    auto index = toIndex(dayOfWeek);

    if (mWeekTimer[index] == dayTimer) {
        return;
    }
    mWeekTimer[index] = dayTimer;
}

DayTimer WeekTimer::dayTimer(DayOfWeek dayOfWeek) const
{
    auto index = toIndex(dayOfWeek);
    return mWeekTimer[index];
}

int WeekTimer::toIndex(DayOfWeek dayOfWeek) const
{
    return static_cast<int>(dayOfWeek);
}

} // namespace thermonator::eq3thermostat::types
