#ifndef THERMONATOR_EQ3THERMOSTAT_DAYTIMERENTRY_HPP
#define THERMONATOR_EQ3THERMOSTAT_DAYTIMERENTRY_HPP

#include "Time.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

class DayTimerEntry {
public:
    DayTimerEntry(const Time &time, double temperature);

    Time time() const;
    double temperature() const;

    bool isValid() const;

private:
    Time mTime{};
    double mTemperature{0.0};
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
