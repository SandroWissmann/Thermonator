#include "SetComfortTemperatureCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

SetComfortTemperatureCommand::SetComfortTemperatureCommand()
    : mCommand{encode()}
{
}

QByteArray SetComfortTemperatureCommand::encoded() const
{
    return mCommand;
}

QByteArray SetComfortTemperatureCommand::encode()
{
    QByteArray command;
    constexpr auto bytesCount = 1;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("43"));

    return command;
}

QDebug
operator<<(QDebug debug,
           const SetComfortTemperatureCommand &setComfortTemperatureCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetComfortTemperatureCommand: "
                    << utility::toHexWithSpace(
                           setComfortTemperatureCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat
