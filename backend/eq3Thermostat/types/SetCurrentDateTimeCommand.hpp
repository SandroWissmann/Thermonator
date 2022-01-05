#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_SETCURRENTDATETIMECOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_SETCURRENTDATETIMECOMMAND_HPP

/*
Command:

0  1  2  3  4  5  6  Bytes

03 11 02 08 15 1f 05 Values in hex

Byte 6: seconds
Byte 5: minutes
Byte 4: hour
Byte 3: day
Byte 2: month
Byte 1: year % 2000
Byte 0: request command "03"

For this example the bytes are decoded to this:

Byte 6: 05 -> 5 sec
Byte 5: 1f -> 31 min
Byte 4: 15 -> 21 hour
Byte 3: 08 -> 8 day
Byte 2: 02 -> february
Byte 1: 11 -> 2017 year
Byte 0: N/A

Complete date:  08/02/2017 21:31:05
*/

#include <QByteArray>

namespace thermonator::eq3thermostat::types {

class SetCurrentDateTimeCommand {
public:
    SetCurrentDateTimeCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug,
                  const SetCurrentDateTimeCommand &setCurrentDateTimeCommand);

} // namespace thermonator::eq3thermostat::types

#endif
