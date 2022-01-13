#ifndef THERMONATOR_EQ3THERMOSTAT_DAYTIMER_HPP
#define THERMONATOR_EQ3THERMOSTAT_DAYTIMER_HPP

#include "DayOfWeek.hpp"
#include "DayTimerEntries.hpp"

namespace thermonator::eq3thermostat {

class DayTimer {
public:
    DayTimer() = default;

    explicit DayTimer(DayOfWeek dayOfWeek,
                      const DayTimerEntries &dayTimerEntries);

    bool isValid() const;

    DayOfWeek dayOfWeek() const;

    DayTimerEntries dayTimerEntries() const;

private:
    DayOfWeek mDayOfWeek{DayOfWeek::invalid};
    DayTimerEntries mDayTimerEntries;
};

inline bool operator==(const DayTimer &lhs, const DayTimer &rhs)
{
    if (lhs.dayOfWeek() != rhs.dayOfWeek()) {
        return false;
    }
    if (lhs.dayTimerEntries() != rhs.dayTimerEntries()) {
        return false;
    }
    return true;
}

inline bool operator!=(const DayTimer &lhs, const DayTimer &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const DayTimer &dayTimer);

} // namespace thermonator::eq3thermostat

#endif
