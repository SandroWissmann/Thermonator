#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_CONFIGUREOPENWINDOWMODE_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_CONFIGUREOPENWINDOWMODE_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

14 19 0c 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 3 to 14: unused
Byte 2: open window interval 1 = 5 mins
Byte 1: open window temperature * 2
Byte 0: request command "14"

For this example the bytes are decoded to this:

Byte 3 to 14: N/A
Byte 2: 0x0c -> 12*5 -> 60 Min
Byte 1: 0x19 -> 25/2.0 -> 12.5 °C
Byte 0: N/A

*/

#include <QObject>

namespace thermonator::eq3thermostat::command {

class ConfigureOpenWindowMode : public QObject {
    Q_OBJECT
public:
    explicit ConfigureOpenWindowMode(QObject *parent = nullptr);

    ~ConfigureOpenWindowMode() = default;

    // Request encoding the command
    // triggers signal commandEncoded
    void encodeCommand(double openWindowTemperature, int openWindowIntervall);

signals:
    void commandEncoded(const QByteArray &command);
};

} // namespace thermonator::eq3thermostat::command

#endif
