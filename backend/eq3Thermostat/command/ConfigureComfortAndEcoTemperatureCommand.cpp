#include "ConfigureComfortAndEcoTemperatureCommand.hpp"

#include "../../utility/Utility.hpp"
#include "../types/Temperature.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

ConfigureComfortAndEcoTemperatureCommand::
    ConfigureComfortAndEcoTemperatureCommand(
        const Temperature &comfortTemperature,
        const Temperature &ecoTemperature)
    : mCommand{encode(comfortTemperature, ecoTemperature)}
{
}

QByteArray ConfigureComfortAndEcoTemperatureCommand::encoded() const
{
    return mCommand;
}

QByteArray ConfigureComfortAndEcoTemperatureCommand::encode(
    const Temperature &comfortTemperature, const Temperature &ecoTemperature)
{
    QByteArray command;
    constexpr auto bytesCount = 3;
    command.reserve(bytesCount);
    command.append(static_cast<unsigned char>(0x11));
    command.append(comfortTemperature.encoded());
    command.append(ecoTemperature.encoded());
    return command;
}

QDebug operator<<(QDebug debug, const ConfigureComfortAndEcoTemperatureCommand
                                    &configureComfortAndEcoTemperatureCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "ConfigureComfortAndEcoTemperatureCommand: "
                    << utility::toHexWithSpace(
                           configureComfortAndEcoTemperatureCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat
