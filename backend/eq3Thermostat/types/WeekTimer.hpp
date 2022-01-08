#ifndef THERMONATOR_EQ3THERMOSTAT_WEEKTIMER_HPP
#define THERMONATOR_EQ3THERMOSTAT_WEEKTIMER_HPP

#include "../notification/DayTimerNotification.hpp"
#include "DayOfWeek.hpp"

#include <array>

namespace thermonator::eq3thermostat {

class WeekTimer {
public:
    // case we have not read yet all days of week timer. Constructs object with
    // isValid() == false
    WeekTimer() = default;

    bool isValid();

    bool dayTimerIsValid(DayOfWeek dayOfWeek) const;

    void setDayTimer(const DayTimerNotification &dayTimerNotification);

    DayTimerNotification dayTimer(DayOfWeek dayOfWeek) const;

private:
    int toIndex(DayOfWeek dayOfWeek) const;

    std::array<DayTimerNotification, 7> mWeekTimer;
};

} // namespace thermonator::eq3thermostat
#endif
