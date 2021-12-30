#include "SwitchToComfortTemperature.hpp"

namespace thermonator::eq3thermostat::command {

SwitchToComfortTemperature::SwitchToComfortTemperature(QObject *parent)
    : SimpleCommandBase{0x43, parent}
{
}

} // namespace thermonator::eq3thermostat::command
