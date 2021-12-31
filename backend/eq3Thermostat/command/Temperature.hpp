#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_TEMPERATURE_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_TEMPERATURE_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

41 29 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 2 to 14: unused
Byte 1: target temperature * 2
Byte 0: request command "41"

For this example the bytes are decoded to this:

Byte 2 to 14: N/A
Byte 1: 0x29 -> 41/2.0 -> 20.5 °C
Byte 0: N/A

*/

#include <QObject>

namespace thermonator::eq3thermostat::command {

class Temperature : public QObject {
    Q_OBJECT
public:
    explicit Temperature(QObject *parent = nullptr);

    ~Temperature() = default;

    // Request encoding the command
    // triggers signal commandEncoded
    void encodeCommand(double temperature);

signals:
    void commandEncoded(const QByteArray &command);
};

} // namespace thermonator::eq3thermostat::command

#endif
