#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_DAYTIMER_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_DAYTIMER_HPP

#include "DayTimerEntry.hpp"

#include <vector>

namespace thermonator::eq3thermostat::types {

class DayTimer {
public:
    // case for we have not read yet any day times so return empty placeholder
    // Constructs object with isValid() == false
    DayTimer() = default;

    // vector size must be between 1 and 7
    // time in last entry must be 24:00
    // constructs object with isValid == true
    DayTimer(std::vector<DayTimerEntry> dayTimerEntries);

    std::vector<DayTimerEntry> dayTimerEntries() const;

    bool isValid() const;

private:
    static bool
    timeIsAscendingInEntries(const std::vector<DayTimerEntry> &dayTimerEntries);

    std::vector<DayTimerEntry> mDayTimerEntries;
};

inline bool operator==(const DayTimer &lhs, const DayTimer &rhs)
{
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

} // namespace thermonator::eq3thermostat::types
#endif
