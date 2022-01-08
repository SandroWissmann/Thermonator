#include "SetTemperatureCommand.hpp"

#include "../../utility/Utility.hpp"
#include "../types/Temperature.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

SetTemperatureCommand::SetTemperatureCommand(const Temperature &temperature)
    : mCommand{encode(temperature)}
{
}

QByteArray SetTemperatureCommand::encoded() const
{
    return mCommand;
}

QByteArray SetTemperatureCommand::encode(const Temperature &temperature)
{
    QByteArray command;
    constexpr auto bytesCount = 2;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("41"));
    command.append(temperature.encoded());
    return command;
}

QDebug operator<<(QDebug debug,
                  const SetTemperatureCommand &setTemperatureCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetTemperatureCommand: "
                    << utility::toHexWithSpace(setTemperatureCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat
