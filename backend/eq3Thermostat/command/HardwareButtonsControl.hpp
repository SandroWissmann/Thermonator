#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_HARDWAREBUTTONSCONTROL_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_HARDWAREBUTTONSCONTROL_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

80 ff 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 2 to 14: unused
Byte 1: hardware buttonS control == 0x00 -> unlock. Value == 0x01 -> lock.
Byte 0: request command "80"

*/

#include <QObject>

namespace thermonator::eq3thermostat::command {

class HardwareButtonsControl : public QObject {
    Q_OBJECT
public:
    explicit HardwareButtonsControl(QObject *parent = nullptr);

    ~HardwareButtonsControl() = default;

    enum class State { lock, unlock };

    // Request encoding the command
    // triggers signal commandEncoded
    void encodeCommand(State state);
signals:
    void commandEncoded(const QByteArray &command);

private:
    char stateToByte(State state);
};

} // namespace thermonator::eq3thermostat::command

#endif
