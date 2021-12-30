#include "ThermostatOff.hpp"

namespace thermonator::eq3thermostat::command {

ThermostatOff::ThermostatOff(QObject *parent) : QObject{parent}
{
    mTemperature = std::make_unique<Temperature>(this);

    connect(mTemperature.get(), &Temperature::commandEncoded, this,
            &ThermostatOff::commandEncoded);
}

void ThermostatOff::encodeCommand()
{
    // It looks like the firmware of the thermostate uses the normally out of
    // range temperature to detect thermostate off command

    constexpr auto thermostateOnTemperature = 4.5;
    mTemperature->encodeCommand(thermostateOnTemperature);
}

} // namespace thermonator::eq3thermostat::command
