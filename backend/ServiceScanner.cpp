#include "ServiceScanner.hpp"

#include <QDebug>
#include <QMetaEnum>

namespace thermonator {

ServiceScanner::ServiceScanner(QObject *parent) : QObject(parent)
{
}

void ServiceScanner::connectAndStartScan(const QBluetoothDeviceInfo &deviceInfo)
{
    auto lowEnergyControllerPlainPtr =
        QLowEnergyController::createCentral(deviceInfo, this);
    mLowEnergyControllerPtr.reset(lowEnergyControllerPlainPtr);

    makeConnections();

    mLowEnergyControllerPtr->connectToDevice();
}

void ServiceScanner::disconnect()
{
    if (!mLowEnergyControllerPtr) {
        return;
    }
    mLowEnergyControllerPtr->disconnectFromDevice();
}

bool ServiceScanner::scanComplete() const
{
    return mScanComplete;
}

std::vector<QBluetoothUuid> ServiceScanner::servicesUuid() const
{
    return mDiscoveredServicesUuids;
}

std::shared_ptr<QLowEnergyService>
ServiceScanner::makeService(QBluetoothUuid uuid)
{
    if (!mLowEnergyControllerPtr) {
        return nullptr;
    }
    auto lowEnergyServicePlainPtr =
        mLowEnergyControllerPtr->createServiceObject(uuid, this);

    std::shared_ptr<QLowEnergyService> lowEnergyServicePtr;
    lowEnergyServicePtr.reset(lowEnergyServicePlainPtr);
    return lowEnergyServicePtr;
}

void ServiceScanner::onError(QLowEnergyController::Error error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QLowEnergyService::ServiceError>();
    qDebug() << Q_FUNC_INFO << metaEnum.valueToKey(error);
}

void ServiceScanner::onConnected()
{
    qDebug() << Q_FUNC_INFO << "Controller connected. Search services...";
    mLowEnergyControllerPtr->discoverServices();
}

void ServiceScanner::onDisconnected()
{
    qDebug() << Q_FUNC_INFO << "LowEnergy controller disconnected";
    for (auto &connection : mConnections) {
        QObject::disconnect(connection);
    }
}

void ServiceScanner::onServiceDiscovered(const QBluetoothUuid &bluetoothUuid)
{
    qDebug() << Q_FUNC_INFO << bluetoothUuid.toString();
    mDiscoveredServicesUuids.emplace_back(bluetoothUuid);
}

void ServiceScanner::onServiceScanDone()
{
    qDebug() << Q_FUNC_INFO;
    mScanComplete = true;
    emit serviceScanCompleted();
}

void ServiceScanner::makeConnections()
{
    Q_ASSERT(mLowEnergyControllerPtr);

    mConnections.emplace_back(connect(
        mLowEnergyControllerPtr.get(), &QLowEnergyController::serviceDiscovered,
        this, &ServiceScanner::onServiceDiscovered));

    mConnections.emplace_back(connect(
        mLowEnergyControllerPtr.get(), &QLowEnergyController::discoveryFinished,
        this, &ServiceScanner::onServiceScanDone));

    mConnections.emplace_back(connect(
        mLowEnergyControllerPtr.get(),
        qOverload<QLowEnergyController::Error>(&QLowEnergyController::error),
        this, &ServiceScanner::onError));

    mConnections.emplace_back(connect(mLowEnergyControllerPtr.get(),
                                      &QLowEnergyController::connected, this,
                                      &ServiceScanner::onConnected));

    mConnections.emplace_back(connect(mLowEnergyControllerPtr.get(),
                                      &QLowEnergyController::disconnected, this,
                                      &ServiceScanner::onDisconnected));
}

} // namespace thermonator
