#include "ScannedDevice.hpp"

namespace thermonator::gui {

ScannedDevice::ScannedDevice(const QString &macAddress)
    : mMacAddress{macAddress}
{
}

QString ScannedDevice::macAddress() const
{
    return mMacAddress;
}

bool ScannedDevice::isSelected() const
{
    return mIsSelected;
}

void ScannedDevice::setIsSelected(bool isSelected)
{
    if (mIsSelected == isSelected) {
        return;
    }
    mIsSelected = isSelected;
}

} // namespace thermonator::gui
