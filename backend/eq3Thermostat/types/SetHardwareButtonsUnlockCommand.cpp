#include "SetHardwareButtonsUnlockCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

SetHardwareButtonsUnlockCommand::SetHardwareButtonsUnlockCommand()
    : mCommand{encode()}
{
}

QByteArray SetHardwareButtonsUnlockCommand::encoded() const
{
    return mCommand;
}

QByteArray SetHardwareButtonsUnlockCommand::encode()
{
    QByteArray command;
    constexpr auto bytesCount = 2;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("80"));
    command.append(QByteArray::fromHex("00"));

    return command;
}

QDebug operator<<(
    QDebug debug,
    const SetHardwareButtonsUnlockCommand &setHardwareButtonsUnlockCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetHardwareButtonsUnlockCommand: "
                    << utility::toHexWithSpace(
                           setHardwareButtonsUnlockCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat::types
