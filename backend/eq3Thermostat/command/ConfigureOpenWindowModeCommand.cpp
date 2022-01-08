#include "ConfigureOpenWindowModeCommand.hpp"

#include "../../utility/Utility.hpp"
#include "../types/OpenWindowInterval.hpp"
#include "../types/Temperature.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

ConfigureOpenWindowModeCommand::ConfigureOpenWindowModeCommand(
    const Temperature &openWindowTemperature,
    const OpenWindowInterval &openWindowInterval)
    : mCommand{encode(openWindowTemperature, openWindowInterval)}
{
}

QByteArray ConfigureOpenWindowModeCommand::encoded() const
{
    return mCommand;
}

QByteArray ConfigureOpenWindowModeCommand::encode(
    const Temperature &openWindowTemperature,
    const OpenWindowInterval &openWindowInterval)
{
    QByteArray command;
    constexpr auto bytesCount = 3;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("14"));
    command.append(openWindowTemperature.encoded());
    command.append(openWindowInterval.encoded());
    return command;
}

QDebug
operator<<(QDebug debug,
           const ConfigureOpenWindowModeCommand &configureOpenWindowModeCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "ConfigureOpenWindowModeCommand: "
                    << utility::toHexWithSpace(
                           configureOpenWindowModeCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat
