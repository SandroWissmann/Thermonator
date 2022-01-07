#include "SetTemperatureOffsetCommand.hpp"

#include "../../utility/Utility.hpp"
#include "TemperatureOffset.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

SetTemperatureOffsetCommand::SetTemperatureOffsetCommand(
    const TemperatureOffset &temperatureOffset)
    : mCommand{encode(temperatureOffset)}
{
}

QByteArray SetTemperatureOffsetCommand::encoded() const
{
    return mCommand;
}

QByteArray
SetTemperatureOffsetCommand::encode(const TemperatureOffset &temperatureOffset)
{
    QByteArray command;
    constexpr auto bytesCount = 2;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("13"));
    command.append(temperatureOffset.encoded());
    return command;
}

QDebug
operator<<(QDebug debug,
           const SetTemperatureOffsetCommand &setTemperatureOffsetCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetTemperatureOffsetCommand: "
                    << utility::toHexWithSpace(
                           setTemperatureOffsetCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat::types
