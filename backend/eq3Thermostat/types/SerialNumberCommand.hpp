#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_SERIALNUMBERCOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_SERIALNUMBERCOMMAND_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 1 to 14: unused
Byte 0: request command "00"

*/

#include <QByteArray>

namespace thermonator::eq3thermostat::types {

class SerialNumberCommand {
public:
    SerialNumberCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug, const SerialNumberCommand &serialNumberCommand);

} // namespace thermonator::eq3thermostat::types

#endif
