#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_SETHARDWAREBUTTONSUNLOCKCOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_SETHARDWAREBUTTONSUNLOCKCOMMAND_HPP

/*
Command:

0  1  Bytes

80 01 Values in hex

Byte 1: value 00 for unlock hardware buttons
Byte 0: request command "80"

*/

#include <QByteArray>

namespace thermonator::eq3thermostat::types {

class SetHardwareButtonsUnlockCommand {
public:
    SetHardwareButtonsUnlockCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug operator<<(
    QDebug debug,
    const SetHardwareButtonsUnlockCommand &setHardwareButtonsUnlockCommand);

} // namespace thermonator::eq3thermostat::types

#endif
