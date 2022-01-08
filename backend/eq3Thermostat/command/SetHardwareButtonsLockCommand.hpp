#ifndef THERMONATOR_EQ3THERMOSTAT_SETHARDWAREBUTTONSLOCKCOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_SETHARDWAREBUTTONSLOCKCOMMAND_HPP

/*
Command:

0  1  Bytes

80 01 Values in hex

Byte 1: value 01 for lock hardware buttons
Byte 0: request command "80"

*/

#include <QByteArray>

namespace thermonator::eq3thermostat {

class SetHardwareButtonsLockCommand {
public:
    SetHardwareButtonsLockCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug
operator<<(QDebug debug,
           const SetHardwareButtonsLockCommand &setHardwareButtonsLockCommand);

} // namespace thermonator::eq3thermostat

#endif
