#include "RequestSerialNumberCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

RequestSerialNumberCommand::RequestSerialNumberCommand() : mCommand{encode()}
{
}

QByteArray RequestSerialNumberCommand::encoded() const
{
    return mCommand;
}

QByteArray RequestSerialNumberCommand::encode()
{
    QByteArray command;
    constexpr auto bytesCount = 1;
    command.reserve(bytesCount);
    command.append(static_cast<int>(0x00));

    return command;
}

QDebug operator<<(QDebug debug,
                  const RequestSerialNumberCommand &requestSerialNumberCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "RequestSerialNumberCommand: "
                    << utility::toHexWithSpace(
                           requestSerialNumberCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat::types
