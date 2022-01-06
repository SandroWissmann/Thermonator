#include "SetBoostOffCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

SetBoostOffCommand::SetBoostOffCommand() : mCommand{encode()}
{
}

QByteArray SetBoostOffCommand::encoded() const
{
    return mCommand;
}

QByteArray SetBoostOffCommand::encode()
{
    QByteArray command;
    constexpr auto bytesCount = 2;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("45"));
    command.append(QByteArray::fromHex("00"));

    return command;
}

QDebug operator<<(QDebug debug, const SetBoostOffCommand &setBoostOffCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetBoostOffCommand: "
                    << utility::toHexWithSpace(setBoostOffCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat::types
