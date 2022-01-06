#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_SETTEMPERATURECOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_SETTEMPERATURECOMMAND_HPP

/*
Command:

0  1  Bytes

41 29 Values in hex

Byte 1: target temperature * 2
Byte 0: request command "41"

For this example the bytes are decoded to this:

Byte 1: 0x29 -> 41/2.0 -> 20.5 °C
Byte 0: N/A

*/

#include <QByteArray>

namespace thermonator::eq3thermostat::types {

class Temperature;

class SetTemperatureCommand {
public:
    SetTemperatureCommand(const Temperature &temperature);

    QByteArray encoded() const;

private:
    static QByteArray encode(const Temperature &temperature);

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug,
                  const SetTemperatureCommand &setTemperatureCommand);

} // namespace thermonator::eq3thermostat::types

#endif
