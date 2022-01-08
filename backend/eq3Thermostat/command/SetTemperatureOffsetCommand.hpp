#ifndef THERMONATOR_EQ3THERMOSTAT_SETTEMPERATUREOFFSETCOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_SETTEMPERATUREOFFSETCOMMAND_HPP

/*
Command:

0  1  Bytes

13 03 Values in hex

Byte 1: (offset temperature - 7) / 2.0
Byte 0: request command "13"

For this example the bytes are decoded to this:

Byte 1: 0x03 -> (3 - 7) / 2.0 -> -2.0°C
Byte 0: N/A

*/

#include <QByteArray>

namespace thermonator::eq3thermostat {

class TemperatureOffset;

class SetTemperatureOffsetCommand {
public:
    SetTemperatureOffsetCommand(const TemperatureOffset &temperatureOffset);

    QByteArray encoded() const;

private:
    static QByteArray encode(const TemperatureOffset &temperatureOffset);

    QByteArray mCommand{};
};

QDebug
operator<<(QDebug debug,
           const SetTemperatureOffsetCommand &setTemperatureOffsetCommand);

} // namespace thermonator::eq3thermostat

#endif
