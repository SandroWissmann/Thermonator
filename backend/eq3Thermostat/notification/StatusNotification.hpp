#ifndef THERMONATOR_EQ3THERMOSTAT_STATUSNOTIFICATION_HPP
#define THERMONATOR_EQ3THERMOSTAT_STATUSNOTIFICATION_HPP

/*
Answer:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

02 01 09 50 04 1e 00 00 00 00 18 03 2a 22 07 Values in hex

Byte 14: temperature offset, calculate (value -  7) / 2
Byte 13: eco temperature, calculate value / 2
Byte 12: comfort temperature, calculate value / 2
Byte 11: open windows interval, calculate value * 5 minutes
Byte 10: temperature in open windows mode, calculate value / 2
Byte 9: if vacation mode: time, calculate value * 30 minutes
Byte 8: if vacation mode: month (January = 0, February = 1, etc.)
Byte 7: if vacation mode: year, callculate value + 2000
Byte 6: if vacation mode: day in month
Byte 5: target temperature, calculate value / 2
Byte 4: (unknown)
Byte 3: valve in percent
Byte 2: flags see below
Byte 1: 0x01 if this notification is device status notification
Byte 0: Always 0x02 if this notification is device status notification

For this example the bytes are decoded to this:

Byte 14: 07 -> 0.0°C
Byte 13: 22 -> 17.0°C
Byte 12: 2a -> 21.0°C
Byte 11: 03 -> 15 min
Byte 10: 18 -> 12.0°C
Byte 9: 0 min
Byte 8: 0 month
Byte 7: 2000 year
Byte 6: 0 day
Byte 5: 15.0°C
Byte 4: ??? functionality unknown
Byte 3: 50 %
Byte 2: 1001 -> manual mode + boost on
Byte 1: n/a
Byte 0: n/a


Newer devices (firmwares > 1.1) always return all details of the device. Older
devices only return bytes 7 to 10 if vacation mode is active. Bytes 11 to 15 are
not available at all.

Byte 2 flags:

Bit 0 is not set (mask 0x00) -> auto mode on
Bit 0 is set (mask 0x01) -> manual mode on
Bit 1 is set (mask 0x02) -> vacation mode on
Bit 2 is set (mask 0x04) -> boost on
Bit 3 is set (mask 0x08) -> daylightSummerTime (dst) on
Bit 4 is set (mask 0x10) -> open window detected
Bit 5 is set (mask 0x20) -> hardware buttons locked
Bit 6 is set (mask 0x40) -> unknown or unused?
Bit 7 is set (mask 0x80) -> indicates low battery

*/

#include "../types/Status.hpp"

namespace thermonator::eq3thermostat {

class StatusNotification {
public:
    StatusNotification() = default;

    StatusNotification(const Status &status);

    static StatusNotification fromEncodedData(const QByteArray &data);

    bool isValid() const;

    Status status() const;

private:
    Status mStatus;
};

} // namespace thermonator::eq3thermostat

#endif
