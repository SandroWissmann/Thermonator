#include "SetEcoTemperatureCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

SetEcoTemperatureCommand::SetEcoTemperatureCommand() : mCommand{encode()}
{
}

QByteArray SetEcoTemperatureCommand::encoded() const
{
    return mCommand;
}

QByteArray SetEcoTemperatureCommand::encode()
{
    QByteArray command;
    constexpr auto bytesCount = 1;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("44"));

    return command;
}

QDebug operator<<(QDebug debug,
                  const SetEcoTemperatureCommand &setEcoTemperatureCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetEcoTemperatureCommand: "
                    << utility::toHexWithSpace(
                           setEcoTemperatureCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat::types
