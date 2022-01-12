#ifndef THERMONATOR_EQ3THERMOSTAT_DAYTIMERENTRIES_HPP
#define THERMONATOR_EQ3THERMOSTAT_DAYTIMERENTRIES_HPP

#include "DayTimerEntry.hpp"

#include <vector>

namespace thermonator::eq3thermostat {

class DayTimerEntries {
public:
    DayTimerEntries() = default;

    // vector must be in size 0 to 7 otherwise it gets invalid
    explicit DayTimerEntries(std::vector<DayTimerEntry> entries);

    // return invalid DayTimerEntries if decoding fails
    static DayTimerEntries
    fromEncodedBytes(const std::vector<unsigned char> &bytes);

    std::vector<DayTimerEntry> entries() const;

    // valid size 0 to 7
    bool isValid() const;

private:
    static bool
    timeIsAscendingInEntries(const std::vector<DayTimerEntry> &entries);

    std::vector<DayTimerEntry> mEntries;
};

inline bool operator==(const DayTimerEntries &lhs, const DayTimerEntries &rhs)
{
    if (lhs.entries() != rhs.entries()) {
        return false;
    }
    return true;
}

inline bool operator!=(const DayTimerEntries &lhs, const DayTimerEntries &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const DayTimerEntries &dayTimerEntries);

} // namespace thermonator::eq3thermostat

#endif
