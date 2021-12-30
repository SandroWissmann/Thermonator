#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_HARDWAREBUTTONSUNLOCK_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_HARDWAREBUTTONSUNLOCK_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

80 01 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 2 to 14: unused
Byte 1: value 00 for unlock hardware buttons
Byte 0: request command "45"

*/

#include <QObject>

#include <memory>

namespace thermonator::eq3thermostat::command {

class HardwareButtonsControl;

class HardwareButtonsUnlock : public QObject {
    Q_OBJECT
public:
    explicit HardwareButtonsUnlock(QObject *parent = nullptr);

    ~HardwareButtonsUnlock();

    // Request encoding the command
    // triggers signal commandEncoded
    void encodeCommand();

signals:
    void commandEncoded(const QByteArray &command);

private:
    std::unique_ptr<HardwareButtonsControl> mHardwareButtonsControl;
};

} // namespace thermonator::eq3thermostat::command

#endif
