#include "SetThermostatOffCommand.hpp"

#include "../../utility/Utility.hpp"

#include "../types/Temperature.hpp"
#include "SetTemperatureCommand.hpp"

namespace thermonator::eq3thermostat {

SetThermostatOffCommand::SetThermostatOffCommand() : mCommand{encode()}
{
}

QByteArray SetThermostatOffCommand::encoded() const
{
    return mCommand;
}

QByteArray SetThermostatOffCommand::encode()
{
    unsigned char temperatureOnbyte = 0x09;
    Temperature temperature{temperatureOnbyte};

    SetTemperatureCommand setTemperatureCommand{temperature};
    return setTemperatureCommand.encoded();
}

QDebug operator<<(QDebug debug,
                  const SetThermostatOffCommand &setThermostatOffCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetThermostatOffCommand: "
                    << utility::toHexWithSpace(
                           setThermostatOffCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat
