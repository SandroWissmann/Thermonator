#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_COMFORTANDECOTEMPERATURE_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_COMFORTANDECOTEMPERATURE_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

11 2b 23 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 3 to 14: unused
Byte 2: eco temperature * 2
Byte 1: comfort temperature * 2
Byte 0: request command "11"

For this example the bytes are decoded to this:

Byte 3 to 14: N/A
Byte 2: 0x23 -> 41 -> 17.5 °C
Byte 1: 0x2b -> 41 -> 21.5 °C
Byte 0: N/A

*/

#include <QObject>

namespace thermonator::eq3thermostat::command {

class ComfortAndEcoTemperature : public QObject {
    Q_OBJECT
public:
    explicit ComfortAndEcoTemperature(QObject *parent = nullptr);

    ~ComfortAndEcoTemperature() = default;

    // Request encoding the command
    // triggers signal commandEncoded
    void encodeCommand(double comfortTemperature, double ecoTemperature);

signals:
    void commandEncoded(const QByteArray &command);
};

} // namespace thermonator::eq3thermostat::command

#endif
