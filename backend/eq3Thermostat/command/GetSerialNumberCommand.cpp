#include "GetSerialNumberCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

GetSerialNumberCommand::GetSerialNumberCommand() : mCommand{encode()}
{
}

QByteArray GetSerialNumberCommand::encoded() const
{
    return mCommand;
}

QByteArray GetSerialNumberCommand::encode()
{
    QByteArray command;
    constexpr auto bytesCount = 1;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("00"));

    return command;
}

QDebug operator<<(QDebug debug,
                  const GetSerialNumberCommand &getSerialNumberCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "RequestSerialNumberCommand: "
                    << utility::toHexWithSpace(
                           getSerialNumberCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat
