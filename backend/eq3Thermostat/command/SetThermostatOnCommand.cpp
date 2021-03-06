#include "SetThermostatOnCommand.hpp"

#include "../../utility/Utility.hpp"

#include "../types/Temperature.hpp"
#include "SetTemperatureCommand.hpp"

namespace thermonator::eq3thermostat {

SetThermostatOnCommand::SetThermostatOnCommand() : mCommand{encode()}
{
}

QByteArray SetThermostatOnCommand::encoded() const
{
    return mCommand;
}

QByteArray SetThermostatOnCommand::encode()
{
    unsigned char temperatureOnbyte = 0x3c;
    Temperature temperature{temperatureOnbyte};

    SetTemperatureCommand setTemperatureCommand{temperature};
    return setTemperatureCommand.encoded();
}

QDebug operator<<(QDebug debug,
                  const SetThermostatOnCommand &setThermostatOnCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetThermostatOnCommand: "
                    << utility::toHexWithSpace(
                           setThermostatOnCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat
