#ifndef THERMONATOR_EQ3THERMOSTAT_SERIALNUMBERNOTIFICATION_HPP
#define THERMONATOR_EQ3THERMOSTAT_SERIALNUMBERNOTIFICATION_HPP

/*
Answer:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

01 6e 00 00 7f 75 81 60 66 61 66 64 61 64 9b Values in hex
             |  |  |  |  |  |  |  |  |  |
             |  |  |  |  |  |  |  |  |  |
             O  E  Q  0  6  1  6  4  1  4

Byte 15: Unknown
Byte 4 to 13: Serial Number in ascii, calculate (hex - 0x30)
Byte 3: Empty / Unknown
Byte 2: Empty / Unknown
Byte 1: Unknown
Byte 0: Always 0x01 if this notification is serial number notification

For this example the bytes are decoded to this:

Byte 15: Unknown
Byte 4 to 13: 7f 75 81 60 66 61 66 64 61 64 -> OEQ0616414
Byte 3: Empty / Unknown
Byte 2: Empty / Unknown
Byte 1: Unknown
Byte 0: N/A

The serial number can be found behind the batteris of the thermostate.

*/

#include "../types/SerialNumber.hpp"

namespace thermonator::eq3thermostat {

class SerialNumberNotification {
public:
    SerialNumberNotification() = default;

    SerialNumberNotification(unsigned char unknownByte1,
                             const SerialNumber &serialNumber,
                             unsigned char unknownByte14);

    static SerialNumberNotification fromEncodedData(const QByteArray &data);

    bool isValid() const;

    SerialNumber serialNumber() const;

    // byte 1 value. currently we don't really know what it means
    unsigned char unknownByte1() const;

    // byte 14 value. currently we don't really know what it means
    unsigned char unknownByte14() const;

private:
    SerialNumber mSerialNumber;
    unsigned char mUnknownByte1;
    unsigned char mUnknownByte14;
};

} // namespace thermonator::eq3thermostat

#endif
