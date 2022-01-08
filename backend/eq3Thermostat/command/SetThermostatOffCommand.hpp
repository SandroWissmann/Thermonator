#ifndef THERMONATOR_EQ3THERMOSTAT_SETTERMOSTATOFFCOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_SETTERMOSTATOFFCOMMAND_HPP

/*
Command:

0  1  Bytes

41 09 Values in hex

Byte 1: temperature * 2 = 4.5°C. This is the signal for the thermostate
firmware to turn the thermostate on
Byte 0: request command "41"

*/

#include <QByteArray>
#include <QDebug>

namespace thermonator::eq3thermostat {

class SetThermostatOffCommand {
public:
    SetThermostatOffCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug,
                  const SetThermostatOffCommand &setThermostatOffCommand);

} // namespace thermonator::eq3thermostat

#endif
