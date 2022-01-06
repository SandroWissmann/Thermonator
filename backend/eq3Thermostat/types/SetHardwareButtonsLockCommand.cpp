#include "SetHardwareButtonsLockCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

SetHardwareButtonsLockCommand::SetHardwareButtonsLockCommand()
    : mCommand{encode()}
{
}

QByteArray SetHardwareButtonsLockCommand::encoded() const
{
    return mCommand;
}

QByteArray SetHardwareButtonsLockCommand::encode()
{
    QByteArray command;
    constexpr auto bytesCount = 2;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("80"));
    command.append(QByteArray::fromHex("01"));

    return command;
}

QDebug
operator<<(QDebug debug,
           const SetHardwareButtonsLockCommand &setHardwareButtonsLockCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetHardwareButtonsLockCommand: "
                    << utility::toHexWithSpace(
                           setHardwareButtonsLockCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat::types
