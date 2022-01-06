#include "SetTemperatureCommand.hpp"

#include "../../utility/Utility.hpp"
#include "Temperature.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

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
    command.append(static_cast<unsigned char>(0x41));
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

} // namespace thermonator::eq3thermostat::types
