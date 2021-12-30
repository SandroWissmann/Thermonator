#include "SwitchToEcoTemperature.hpp"

namespace thermonator::eq3thermostat::command {

SwitchToEcoTemperature::SwitchToEcoTemperature(QObject *parent)
    : SimpleCommandBase{0x44, parent}
{
}

} // namespace thermonator::eq3thermostat::command
