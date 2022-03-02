#include "DeviceScanner.hpp"

#include <QBluetoothDeviceInfo>

#include <QDebug>
#include <QMetaEnum>

namespace thermonator {

DeviceScanner::DeviceScanner(QObject *parent) : QObject{parent}
{
    mDeviceDiscoveryAgentPtr = new QBluetoothDeviceDiscoveryAgent(this);
    mDeviceDiscoveryAgentPtr->setLowEnergyDiscoveryTimeout(5000);

    connect(mDeviceDiscoveryAgentPtr,
            &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this,
            &DeviceScanner::onAddDeviceInfo);
    connect(mDeviceDiscoveryAgentPtr,
            static_cast<void (QBluetoothDeviceDiscoveryAgent::*)(
                QBluetoothDeviceDiscoveryAgent::Error)>(
                &QBluetoothDeviceDiscoveryAgent::error),
            this, &DeviceScanner::onScanError);

    connect(mDeviceDiscoveryAgentPtr, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &DeviceScanner::onScanCompleted);
    connect(mDeviceDiscoveryAgentPtr, &QBluetoothDeviceDiscoveryAgent::canceled,
            this, &DeviceScanner::onScanCompleted);
}

std::shared_ptr<QBluetoothDeviceInfo>
DeviceScanner::deviceInfoPtr(const QString &macAddress)
{
    auto deviceInfoPtrIt = std::find_if(
        mDevicesInfosPtr.begin(), mDevicesInfosPtr.end(),
        [macAddress](std::shared_ptr<QBluetoothDeviceInfo> deviceInfoPtr) {
            return deviceInfoPtr->address().toString() == macAddress;
        });

    if (deviceInfoPtrIt != mDevicesInfosPtr.end()) {
        return *deviceInfoPtrIt;
    }
    return nullptr;
}

void DeviceScanner::onStartScanning()
{
    qDebug() << Q_FUNC_INFO;

    mDevicesInfosPtr.clear();
    mDeviceDiscoveryAgentPtr->start(
        QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);

    qDebug() << Q_FUNC_INFO << "Scanning for devices...";
}

void DeviceScanner::onAddDeviceInfo(const QBluetoothDeviceInfo &deviceInfo)
{
    qDebug() << Q_FUNC_INFO;

    if (!(deviceInfo.coreConfigurations() &
          QBluetoothDeviceInfo::LowEnergyCoreConfiguration)) {
        return;
    }

    qDebug() << Q_FUNC_INFO
             << "Found device with address:" << deviceInfo.address();

    emit deviceDiscovered(deviceInfo);

    auto deviceInfoPtr = std::make_shared<QBluetoothDeviceInfo>(deviceInfo);
    mDevicesInfosPtr.emplace_back(deviceInfoPtr);
}
void DeviceScanner::onScanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    QMetaEnum metaEnum =
        QMetaEnum::fromType<QBluetoothDeviceDiscoveryAgent::Error>();
    qDebug() << Q_FUNC_INFO << metaEnum.valueToKey(error);
}

void DeviceScanner::onScanCompleted()
{
    qDebug() << Q_FUNC_INFO;
    emit scanCompleted();
}

} // namespace thermonator
