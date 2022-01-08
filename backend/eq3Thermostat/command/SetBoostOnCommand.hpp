#ifndef THERMONATOR_EQ3THERMOSTAT_SETBOOSTONCOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_SETBOOSTONCOMMAND_HPP

/*
Command:

0  1  Bytes

45 ff Values in hex

Byte 1: value > 0 turns on the boost. So we send ff for Boost on
Byte 0: request command "45"

*/

#include <QByteArray>

namespace thermonator::eq3thermostat {

class SetBoostOnCommand {
public:
    SetBoostOnCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug, const SetBoostOnCommand &setBoostOnCommand);

} // namespace thermonator::eq3thermostat

#endif
