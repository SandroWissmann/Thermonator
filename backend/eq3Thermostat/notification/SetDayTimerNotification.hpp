#ifndef THERMONATOR_EQ3THERMOSTAT_SETDAYTIMERNOTIFICATION_HPP
#define THERMONATOR_EQ3THERMOSTAT_SETDAYTIMERNOTIFICATION_HPP

/*
Answer:

0  1  2  Bytes

02 02 06 Values in hex

Byte 2: Day that has been programmed with set day timer
Byte 1: Always 0x02 if is set day timer notification
Byte 0: Always 0x02 if is set day timer notification

For this example the bytes are decoded to this:

Byte 2: 0x06 -> friday
Byte 1: n/a
Byte 0: n/a
*/

#include "../types/DayOfWeek.hpp"

namespace thermonator::eq3thermostat {

class SetDayTimerNotification {
public:
    // case for we have not read yet any day times so return empty placeholder
    // Constructs object with isValid() == false
    SetDayTimerNotification() = default;

    SetDayTimerNotification(const DayOfWeek &dayOfWeek);

    static SetDayTimerNotification fromEncodedData(const QByteArray &data);

    DayOfWeek dayOfWeek() const;

    // vector size must be 3
    // values in byte 0 and 1 must be right values
    // byte 2 must be in range of day of week
    bool isValid() const;

private:
    static bool dataIsValid(const QByteArray &data);

    DayOfWeek mDayOfWeek{DayOfWeek::invalid};
};

} // namespace thermonator::eq3thermostat
#endif
