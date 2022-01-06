#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_SETBOOSTOFFCOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_SETBOOSTOFFCOMMAND_HPP

/*
Command:

0  1 Bytes

45 0 Values in hex

Byte 2 to 14: unused
Byte 1: value == 0 turns on the boost. So we send 00 for Boost off
Byte 0: request command "45"

*/

#include <QByteArray>

namespace thermonator::eq3thermostat::types {

class SetBoostOffCommand {
public:
    SetBoostOffCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug, const SetBoostOffCommand &setBoostOffCommand);

} // namespace thermonator::eq3thermostat::types

#endif
