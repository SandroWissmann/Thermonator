#ifndef THERMONATOR_EQ3THERMOSTAT_DATETIME_HPP
#define THERMONATOR_EQ3THERMOSTAT_DATETIME_HPP

#include "Date.hpp"
#include "Time.hpp"

namespace thermonator::eq3thermostat {

class DateTime {
public:
    DateTime() = default;
    DateTime(unsigned char yearByte, unsigned char yearMonth,
             unsigned char dayByte, unsigned char timeByte);

    int year() const;
    int month() const;
    int day() const;
    int hour() const;
    int minute() const;

    Date date() const;
    Time time() const;

    bool isValid() const;

private:
    Date mDate;
    Time mTime;
};

inline bool operator==(const DateTime &lhs, const DateTime &rhs)
{
    if (lhs.date() != rhs.date()) {
        return false;
    }
    if (lhs.time() != rhs.time()) {
        return false;
    }
    return true;
}

inline bool operator!=(const DateTime &lhs, const DateTime &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const DateTime &dateTime);

} // namespace thermonator::eq3thermostat

#endif
