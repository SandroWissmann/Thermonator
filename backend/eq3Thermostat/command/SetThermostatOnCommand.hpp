#ifndef THERMONATOR_EQ3THERMOSTAT_SETTERMOSTATONCOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_SETTERMOSTATONCOMMAND_HPP

/*
Command:

0  1  Bytes

41 3c Values in hex

Byte 1: temperature * 2 = 30.0°C. This is the signal for the thermostate
firmware to turn the thermostate on
Byte 0: request command "41"

*/

#include <QByteArray>
#include <QDebug>

namespace thermonator::eq3thermostat {

class SetThermostatOnCommand {
public:
    SetThermostatOnCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug,
                  const SetThermostatOnCommand &setThermostatOnCommand);

} // namespace thermonator::eq3thermostat

#endif
