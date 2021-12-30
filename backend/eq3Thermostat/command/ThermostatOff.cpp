#include "ThermostatOff.hpp"

#include "Temperature.hpp"

namespace thermonator::eq3thermostat::command {

ThermostatOff::ThermostatOff(QObject *parent) : QObject{parent}
{
    mTemperature = std::make_unique<Temperature>(this);

    connect(mTemperature.get(), &Temperature::commandEncoded, this,
            &ThermostatOff::commandEncoded);
}

// declaration has to be in cpp to make std::unique_ptr member forward
// declaration work
ThermostatOff::~ThermostatOff() = default;

void ThermostatOff::encodeCommand()
{
    // It looks like the firmware of the thermostate uses the normally out of
    // range temperature to detect thermostate off command

    constexpr auto thermostateOnTemperature = 4.5;
    mTemperature->encodeCommand(thermostateOnTemperature);
}

} // namespace thermonator::eq3thermostat::command
