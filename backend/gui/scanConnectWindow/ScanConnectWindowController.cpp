#include "ScanConnectWindowController.hpp"

#include "ScannedDevicesModel.hpp"

#include <QDebug>

namespace thermonator::gui {

ScanConnectWindowController::ScanConnectWindowController(QObject *parent)
    : QObject{parent}, m_scannedDevicesModelPtr{new ScannedDevicesModel{this}}
{
    qRegisterMetaType<thermonator::gui::ScanConnectWindowController *>();
}

bool ScanConnectWindowController::connectButtonIsActive()
{
    auto connectButtonIsActiv = !m_selectedBluetoothDeviceMacAddress.isEmpty();
    return connectButtonIsActiv;
}

ScannedDevicesModel *ScanConnectWindowController::scannedDevicesModel()
{
    return m_scannedDevicesModelPtr;
}

void ScanConnectWindowController::startScanning()
{
    qDebug() << Q_FUNC_INFO;
    m_selectedBluetoothDeviceMacAddress.clear();
    emit connectButtonIsActiveChanged();
    m_scannedDevicesModelPtr->resetDevices();

    emit requestStartScanning();
}

void ScanConnectWindowController::selectScannedDevice(const QString &macAddress)
{
    if (m_selectedBluetoothDeviceMacAddress == macAddress) {
        return;
    }

    auto selectedDevice = m_scannedDevicesModelPtr->selectDevice(macAddress);

    if (!selectedDevice) {
        return;
    }

    m_selectedBluetoothDeviceMacAddress = macAddress;
    emit connectButtonIsActiveChanged();
}

void ScanConnectWindowController::connectToSelectedBluetoothDevice()
{
    if (m_selectedBluetoothDeviceMacAddress.isEmpty()) {
        return;
    }

    qDebug() << Q_FUNC_INFO
             << "mac address: " << m_selectedBluetoothDeviceMacAddress;

    emit requestConnectToBluetooothDevice(m_selectedBluetoothDeviceMacAddress);
}

void ScanConnectWindowController::onReceiveNewDevice(
    const QBluetoothDeviceInfo &deviceInfo)
{
    m_scannedDevicesModelPtr->addDevice(deviceInfo);
}

} // namespace thermonator::gui
