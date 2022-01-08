#include "SetBoostOnCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

SetBoostOnCommand::SetBoostOnCommand() : mCommand{encode()}
{
}

QByteArray SetBoostOnCommand::encoded() const
{
    return mCommand;
}

QByteArray SetBoostOnCommand::encode()
{
    QByteArray command;
    constexpr auto bytesCount = 2;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("45"));
    command.append(QByteArray::fromHex("ff"));

    return command;
}

QDebug operator<<(QDebug debug, const SetBoostOnCommand &setBoostOnCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetBoostOnCommand: "
                    << utility::toHexWithSpace(setBoostOnCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat
