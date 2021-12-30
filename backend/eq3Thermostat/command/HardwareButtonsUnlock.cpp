#include "HardwareButtonsUnlock.hpp"

#include "HardwareButtonsControl.hpp"

namespace thermonator::eq3thermostat::command {

HardwareButtonsUnlock::HardwareButtonsUnlock(QObject *parent) : QObject{parent}
{
    mHardwareButtonsControl = std::make_unique<HardwareButtonsControl>(this);

    connect(mHardwareButtonsControl.get(),
            &HardwareButtonsControl::commandEncoded, this,
            &HardwareButtonsUnlock::commandEncoded);
}

// declaration has to be in cpp to make std::unique_ptr member forward
// declaration work
HardwareButtonsUnlock::~HardwareButtonsUnlock() = default;

void HardwareButtonsUnlock::encodeCommand()
{
    mHardwareButtonsControl->encodeCommand(
        HardwareButtonsControl::State::unlock);
}

} // namespace thermonator::eq3thermostat::command
