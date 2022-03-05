#include "ScannedDevice.hpp"

#include <QBluetoothAddress>

namespace thermonator::gui {

ScannedDevice::ScannedDevice(const QBluetoothDeviceInfo &deviceInfo)
    : mDeviceInfo{deviceInfo}
{
}

QBluetoothDeviceInfo ScannedDevice::deviceInfo() const
{
    return mDeviceInfo;
}

QString ScannedDevice::macAddress() const
{
    return mDeviceInfo.address().toString();
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
