#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_TIME_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_TIME_HPP

#include <QDebug>

namespace thermonator::eq3thermostat::types {

class Time {
public:
    Time() = default;
    Time(int hour, int minute);

    static Time fromEncodedByte(unsigned char byte);

    int hour() const;
    int minute() const;

    // valid range 0:00 to 24:00
    bool isValid() const;

private:
    int mHour{0};
    int mMinute{0};
};

inline bool operator==(const Time &lhs, const Time &rhs)
{
    if (lhs.hour() != rhs.hour()) {
        return false;
    }
    if (lhs.minute() != rhs.minute()) {
        return false;
    }
    return true;
}

inline bool operator!=(const Time &lhs, const Time &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const Time &time);

} // namespace thermonator::eq3thermostat::types

#endif
