#include "BoostOff.hpp"

#include "BoostControl.hpp"

namespace thermonator::eq3thermostat::command {

BoostOff::BoostOff(QObject *parent) : QObject{parent}
{
    mBoostControl = std::make_unique<BoostControl>(this);

    connect(mBoostControl.get(), &BoostControl::commandEncoded, this,
            &BoostOff::commandEncoded);
}

// declaration has to be in cpp to make std::unique_ptr member forward
// declaration work
BoostOff::~BoostOff() = default;

void BoostOff::encodeCommand()
{
    mBoostControl->encodeCommand(BoostControl::State::off);
}

} // namespace thermonator::eq3thermostat::command
