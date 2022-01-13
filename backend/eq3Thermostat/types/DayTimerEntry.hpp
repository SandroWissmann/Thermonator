#ifndef THERMONATOR_EQ3THERMOSTAT_DAYTIMERENTRY_HPP
#define THERMONATOR_EQ3THERMOSTAT_DAYTIMERENTRY_HPP

#include "Temperature.hpp"
#include "Time.hpp"

#include <QDebug>

#include <array>

namespace thermonator::eq3thermostat {

class DayTimerEntry {
public:
    // constructs object which is !isValid
    DayTimerEntry() = default;

    DayTimerEntry(const Time &time, const Temperature &temperature);

    static DayTimerEntry
    fromEncodedBytes(const std::vector<unsigned char> &bytes);

    std::array<unsigned char, 2> encoded() const;

    Time time() const;
    Temperature temperature() const;

    bool isValid() const;

private:
    Time mTime{};
    Temperature mTemperature;
};

inline bool operator==(const DayTimerEntry &lhs, const DayTimerEntry &rhs)
{
    if (lhs.time() != rhs.time()) {
        return false;
    }
    if (lhs.temperature() != rhs.temperature()) {
        return false;
    }
    return true;
}

inline bool operator!=(const DayTimerEntry &lhs, const DayTimerEntry &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const DayTimerEntry &dayTimerEntry);

} // namespace thermonator::eq3thermostat
#endif
