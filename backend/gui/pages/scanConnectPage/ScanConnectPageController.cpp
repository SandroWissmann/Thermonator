#include "ScanConnectPageController.hpp"

#include "ScannedDevicesModel.hpp"

#include <QDebug>

namespace thermonator::gui {

ScanConnectPageController::ScanConnectPageController(QObject *parent)
    : QObject{parent}, m_scannedDevicesModelPtr{new ScannedDevicesModel{this}}
{
    qRegisterMetaType<thermonator::gui::ScanConnectPageController *>();
}

bool ScanConnectPageController::connectButtonIsActive()
{
    auto connectButtonIsActiv = !m_selectedBluetoothDeviceMacAddress.isEmpty();
    return connectButtonIsActiv;
}

ScannedDevicesModel *ScanConnectPageController::scannedDevicesModel()
{
    return m_scannedDevicesModelPtr;
}

void ScanConnectPageController::startScanning()
{
    qDebug() << Q_FUNC_INFO;
    m_selectedBluetoothDeviceMacAddress.clear();
    emit connectButtonIsActiveChanged();
    m_scannedDevicesModelPtr->resetDevices();

    emit requestStartScanning();
}

void ScanConnectPageController::selectScannedDevice(const QString &macAddress)
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

void ScanConnectPageController::connectToSelectedBluetoothDevice()
{
    if (m_selectedBluetoothDeviceMacAddress.isEmpty()) {
        return;
    }

    qDebug() << Q_FUNC_INFO
             << "mac address: " << m_selectedBluetoothDeviceMacAddress;

    // maybe we dont really connect yet we just open the configuration page
    // signal could be obsolete
    emit requestConnectToBluetooothDevice(m_selectedBluetoothDeviceMacAddress);
    // TODO: send device info to thermostat configuration page
    emit loadThermostatConfigurationPage();
}

void ScanConnectPageController::onReceiveNewDevice(
    const QBluetoothDeviceInfo &deviceInfo)
{
    m_scannedDevicesModelPtr->addDevice(deviceInfo);
}

} // namespace thermonator::gui
