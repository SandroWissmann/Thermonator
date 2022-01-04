#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_DAYTIMER_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_DAYTIMER_HPP

/*
Answer:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 Bytes

21 03 22 3C 28 4B 26 54 22 5A 28 66 22 90 00 00 Values in hex

Byte 15: Encoded final time of seventh event in 10 minutes steps
Byte 14: Temperature between sixth and seventh event
Byte 13: Encoded time of sixth event in 10 minutes steps
Byte 12: Temperature between fifth and sixth event
Byte 11: Encoded time of fifth event in 10 minutes steps
Byte 10: Temperature between forth and fifth event
Byte 9: Encoded time of forth event in 10 minutes steps
Byte 8: Temperature between third and forth event
Byte 7: Encoded time of third event in 10 minutes steps
Byte 6: Temperature between second event and third event
Byte 5: Encoded time of second event in 10 minutes steps
Byte 4: Temperature between first event and second event
Byte 3: Encoded time of first event in 10 minutes steps
Byte 2: Temperature between midnight and first event
Byte 1: day of the week from 00 = saturday to 06 = friday
Byte 0: Always 0x21 if is day timer notification

For this example the bytes are decoded to this:

Byte 14+15: 0x00 -> Unused, could be also seventh entry with temp. and time
Byte 13: 0x90 -> 144* 10 = 1440min -> 24:00
Byte 12: 0x22 -> 34/2.0 = 17°C
Byte 11: 0x66 -> 102*10 = 1020min -> 17:00
Byte 10: 0x28 -> 40/2.0 = 20°C
Byte 9: 0x5A -> 90*10 = 900min -> 15:00
Byte 8: 0x22 -> 34/2.0 = 17°C
Byte 7: 0x54 -> 84*10 = 840min -> 14:00
Byte 6: 0x26 -> 38/2.0 = 19°C
Byte 5: 0x4B -> 75*10 = 750min -> 12:30
Byte 4: 0x28 -> 40/2.0 = 20°C
Byte 3: 0x3c -> 60*10 = 600min -> 10:00
Byte 2: 0x22 -> 34/2.0 = 17°C
Byte 1: 0x03 -> tuesday
Byte 0: n/a

So in conclusion the time plan for the day is as following

17°C from 0:00 to 10:00 -> DayTimerEntry 1
20°C from 10:00 to 12:30 -> DayTimerEntry 2
19°C from 12:30 to 14:00 -> DayTimerEntry 3
17°C from 14:00 to 15:00 -> DayTimerEntry 4
20°C from 15:00 to 17:00 -> DayTimerEntry 5
17°C from 17:00 to 24:00 -> DayTimerEntry 6

There could be in total 7 DayTimer entries.
Important is that the last  DayTimer Entry always ends on 24:00
*/

#include "DayOfWeek.hpp"
#include "DayTimerEntry.hpp"

#include <optional>
#include <vector>

namespace thermonator::eq3thermostat::types {

class DayTimer {
public:
    // case for we have not read yet any day times so return empty placeholder
    // Constructs object with isValid() == false
    DayTimer() = default;

    DayTimer(DayOfWeek dayOfWeek, std::vector<DayTimerEntry> dayTimerEntries);

    static DayTimer fromEncodedData(const QByteArray &data);

    std::vector<DayTimerEntry> dayTimerEntries() const;

    DayOfWeek dayOfWeek() const;

    // vector size must be between 1 and 7
    // time in last entry must be 24:00
    bool isValid() const;

private:
    static bool dataIsValid(const QByteArray &data);
    static DayOfWeek optDecodeDayOfWeek(unsigned char byte);
    static std::optional<std::vector<DayTimerEntry>>
    optDecodeDayTimerEntries(const std::vector<unsigned char> &bytes);
    static double decodeTemperature(unsigned char byte);
    static Time decodeTime(unsigned char byte);

    static bool
    timeIsAscendingInEntries(const std::vector<DayTimerEntry> &dayTimerEntries);

    DayOfWeek mDayOfWeek{DayOfWeek::invalid};
    std::vector<DayTimerEntry> mDayTimerEntries;
};

inline bool operator==(const DayTimer &lhs, const DayTimer &rhs)
{
    if (lhs.dayTimerEntries() != rhs.dayTimerEntries()) {
        return false;
    }
    if (lhs.dayOfWeek() != rhs.dayOfWeek()) {
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
