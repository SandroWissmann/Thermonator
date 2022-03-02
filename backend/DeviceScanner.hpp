#ifndef THERMONATOR_DEVICE_SCANNER_HPP
#define THERMONATOR_DEVICE_SCANNER_HPP

#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QList>
#include <QObject>
#include <QVariant>

#include <memory>
#include <vector>

class QBluetoothDeviceInfo;

namespace thermonator {

class DeviceScanner : public QObject {
    Q_OBJECT
public:
    explicit DeviceScanner(QObject *parent = nullptr);

    ~DeviceScanner() = default;

    // get deviceInfo by mac address or nullptr if it was not found
    std::shared_ptr<QBluetoothDeviceInfo>
    deviceInfoPtr(const QString &macAddress);

signals:
    // this signal is emitted when a new device was discovered
    void deviceDiscovered(const QBluetoothDeviceInfo &deviceInfo);

    // this signal is emitted when scanning is completed
    void scanCompleted();

public slots:
    // start scanning to find available deviceinfos
    void onStartScanning();

private slots:
    void onAddDeviceInfo(const QBluetoothDeviceInfo &deviceInfo);
    void onScanError(QBluetoothDeviceDiscoveryAgent::Error error);
    void onScanCompleted();

private:
    QBluetoothDeviceDiscoveryAgent *mDeviceDiscoveryAgentPtr;
    std::vector<std::shared_ptr<QBluetoothDeviceInfo>> mDevicesInfosPtr;
};

} // namespace thermonator

#endif
