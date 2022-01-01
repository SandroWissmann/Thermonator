#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_WEEKTIMER_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_WEEKTIMER_HPP

#include "DayOfWeek.hpp"
#include "DayTimer.hpp"

#include <array>

namespace thermonator::eq3thermostat::types {

class WeekTimer {
public:
    // case we have not read yet all days of week timer. Constructs object with
    // isValid() == false
    WeekTimer() = default;

    // constructs object with isValid == true
    // week days are ordered 0 = saturday to 6  = friday
    WeekTimer(const std::array<DayTimer, 7> &weekTimer);

    bool isValid();

    bool dayTimerIsValid(DayOfWeek dayOfWeek) const;

    void setDayTimer(DayOfWeek dayOfWeek, const DayTimer &dayTimer);

    DayTimer dayTimer(DayOfWeek dayOfWeek) const;

private:
    int toIndex(DayOfWeek dayOfWeek) const;

    std::array<DayTimer, 7> mWeekTimer;
};

} // namespace thermonator::eq3thermostat::types
#endif
