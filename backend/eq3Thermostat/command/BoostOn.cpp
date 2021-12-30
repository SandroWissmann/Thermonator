#include "BoostOn.hpp"

#include "BoostControl.hpp"

namespace thermonator::eq3thermostat::command {

BoostOn::BoostOn(QObject *parent) : QObject{parent}
{
    mBoostControl = std::make_unique<BoostControl>(this);

    connect(mBoostControl.get(), &BoostControl::commandEncoded, this,
            &BoostOn::commandEncoded);
}

// declaration has to be in cpp to make std::unique_ptr member forward
// declaration work
BoostOn::~BoostOn() = default;

void BoostOn::encodeCommand()
{
    mBoostControl->encodeCommand(BoostControl::State::on);
}

} // namespace thermonator::eq3thermostat::command
