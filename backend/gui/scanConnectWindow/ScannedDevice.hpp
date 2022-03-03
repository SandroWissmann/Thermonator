#ifndef THERMONATOR_GUI_SCANNEDDEVICE_HPP
#define THERMONATOR_GUI_SCANNEDDEVICE_HPP

#include <QString>

namespace thermonator::gui {

class ScannedDevice {
public:
    explicit ScannedDevice(const QString &macAddress);

    ScannedDevice(const ScannedDevice &) = default;
    ScannedDevice &operator=(const ScannedDevice &) = default;
    ScannedDevice(ScannedDevice &&) = default;
    ScannedDevice &operator=(ScannedDevice &&) = default;
    ~ScannedDevice() = default;

    QString macAddress() const;

    bool isSelected() const;

    void setIsSelected(bool isSelected);

private:
    QString mMacAddress;
    bool mIsSelected{false};
};
} // namespace thermonator::gui
#endif
