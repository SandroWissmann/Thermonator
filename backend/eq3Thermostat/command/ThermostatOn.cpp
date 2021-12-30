#include "ThermostatOn.hpp"

#include "Temperature.hpp"

namespace thermonator::eq3thermostat::command {

ThermostatOn::ThermostatOn(QObject *parent) : QObject{parent}
{
    mTemperature = std::make_unique<Temperature>(this);

    connect(mTemperature.get(), &Temperature::commandEncoded, this,
            &ThermostatOn::commandEncoded);
}

// declaration has to be in cpp to make std::unique_ptr member forward
// declaration work
ThermostatOn::~ThermostatOn() = default;

void ThermostatOn::encodeCommand()
{
    // It looks like the firmware of the thermostate uses the normally out of
    // range temperature to detect thermostate on command

    constexpr auto thermostateOnTemperature = 30.0;
    mTemperature->encodeCommand(thermostateOnTemperature);
}

} // namespace thermonator::eq3thermostat::command
