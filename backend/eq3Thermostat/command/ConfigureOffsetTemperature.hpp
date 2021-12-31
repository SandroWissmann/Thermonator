#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_CONFIGUREOFFSETTEMPERATURE_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_CONFIGUREOFFSETTEMPERATURE_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

13 03 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 2 to 14: unused
Byte 1: (offset temperature - 7) / 2.0
Byte 0: request command "13"

For this example the bytes are decoded to this:

Byte 2 to 14: N/A
Byte 1: 0x03 -> (3 - 7) / 2.0 -> -2.0°C
Byte 0: N/A

*/

#include <QObject>

namespace thermonator::eq3thermostat::command {

class ConfigureOffsetTemperature : public QObject {
    Q_OBJECT
public:
    explicit ConfigureOffsetTemperature(QObject *parent = nullptr);

    ~ConfigureOffsetTemperature() = default;

    // Request encoding the command
    // triggers signal commandEncoded
    void encodeCommand(double offsetTemperature);

signals:
    void commandEncoded(const QByteArray &command);
};

} // namespace thermonator::eq3thermostat::command

#endif
