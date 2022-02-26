#include "ScanConnectWindowController.hpp"

#include <QDebug>

namespace thermonator::guiController {

ScanConnectWindowController::ScanConnectWindowController(QObject *parent)
    : QObject{parent}
{
    qRegisterMetaType<
        thermonator::guiController::ScanConnectWindowController *>();
}

bool ScanConnectWindowController::connectButtonIsActive()
{
    auto connectButtonIsActiv = !m_selectedBluetoothDeviceMacAddress.isEmpty();
    return connectButtonIsActiv;
}

void ScanConnectWindowController::startScanning()
{
    qDebug() << Q_FUNC_INFO;

    emit requestStartScanning();
}

void ScanConnectWindowController::connectToBluetoothDevice()
{
    qDebug() << Q_FUNC_INFO;

    if (m_selectedBluetoothDeviceMacAddress.isEmpty()) {
        return;
    }
    emit requestConnectToBluetooothDevice(m_selectedBluetoothDeviceMacAddress);
}

} // namespace thermonator::guiController
