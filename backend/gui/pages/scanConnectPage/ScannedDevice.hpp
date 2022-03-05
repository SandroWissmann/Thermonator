#ifndef THERMONATOR_GUI_PAGES_SCANCONNECTPAGE_SCANNEDDEVICE_HPP
#define THERMONATOR_GUI_PAGES_SCANCONNECTPAGE_SCANNEDDEVICE_HPP

#include <QBluetoothDeviceInfo>
#include <QString>

namespace thermonator::gui {

class ScannedDevice {
public:
    explicit ScannedDevice(const QBluetoothDeviceInfo &deviceInfo);

    ScannedDevice(const ScannedDevice &) = default;
    ScannedDevice &operator=(const ScannedDevice &) = default;
    ScannedDevice(ScannedDevice &&) = default;
    ScannedDevice &operator=(ScannedDevice &&) = default;
    ~ScannedDevice() = default;

    QBluetoothDeviceInfo deviceInfo() const;

    QString macAddress() const;

    bool isSelected() const;

    void setIsSelected(bool isSelected);

private:
    QBluetoothDeviceInfo mDeviceInfo;
    bool mIsSelected{false};
};
} // namespace thermonator::gui
#endif
