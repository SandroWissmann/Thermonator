#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_SERIALNUMBERCOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_SERIALNUMBERCOMMAND_HPP

/*
Command:

0   Bytes

00  Values in hex


Byte 0: request command "00"

*/

#include <QByteArray>

namespace thermonator::eq3thermostat::types {

class RequestSerialNumberCommand {
public:
    RequestSerialNumberCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug, const RequestSerialNumberCommand &serialNumberCommand);

} // namespace thermonator::eq3thermostat::types

#endif
