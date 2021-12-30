#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_BOOSTCONTROL_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_BOOSTCONTROL_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

45 ff 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 2 to 14: unused
Byte 1: boost control value == 0x00 -> off. Value > 0x00 -> on.
Byte 0: request command "45"

*/

#include <QObject>

namespace thermonator::eq3thermostat::command {

class BoostControl : public QObject {
    Q_OBJECT
public:
    explicit BoostControl(QObject *parent = nullptr);

    ~BoostControl() = default;

    enum class State { on, off };

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
