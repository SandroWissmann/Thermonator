#include "HardwareButtonsLock.hpp"

#include "HardwareButtonsControl.hpp"

namespace thermonator::eq3thermostat::command {

HardwareButtonsLock::HardwareButtonsLock(QObject *parent) : QObject{parent}
{
    mHardwareButtonsControl = std::make_unique<HardwareButtonsControl>(this);

    connect(mHardwareButtonsControl.get(),
            &HardwareButtonsControl::commandEncoded, this,
            &HardwareButtonsLock::commandEncoded);
}

// declaration has to be in cpp to make std::unique_ptr member forward
// declaration work
HardwareButtonsLock::~HardwareButtonsLock() = default;

void HardwareButtonsLock::encodeCommand()
{
    mHardwareButtonsControl->encodeCommand(HardwareButtonsControl::State::lock);
}

} // namespace thermonator::eq3thermostat::command
