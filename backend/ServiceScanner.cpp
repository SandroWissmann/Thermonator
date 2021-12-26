#include "ServiceScanner.hpp"

#include <QDebug>
#include <QMetaEnum>

namespace thermonator {

ServiceScanner::ServiceScanner(
    std::shared_ptr<QBluetoothDeviceInfo> deviceInfoPtr, QObject *parent)
    : QObject(parent)
{
    Q_ASSERT(deviceInfoPtr);

    // Make connections
    auto lowEnergyControllerPlainPtr =
        QLowEnergyController::createCentral(*deviceInfoPtr, this);
    mLowEnergyControllerPtr.reset(lowEnergyControllerPlainPtr);

    connect(mLowEnergyControllerPtr.get(),
            &QLowEnergyController::serviceDiscovered, this,
            &ServiceScanner::onServiceDiscovered);

    connect(mLowEnergyControllerPtr.get(),
            &QLowEnergyController::discoveryFinished, this,
            &ServiceScanner::onServiceScanDone);

    connect(
        mLowEnergyControllerPtr.get(),
        qOverload<QLowEnergyController::Error>(&QLowEnergyController::error),
        this, &ServiceScanner::onError);

    connect(mLowEnergyControllerPtr.get(), &QLowEnergyController::connected,
            this, &ServiceScanner::onConnected);

    connect(mLowEnergyControllerPtr.get(), &QLowEnergyController::disconnected,
            this, &ServiceScanner::onDisconnected);
}

void ServiceScanner::startScan()
{
    mLowEnergyControllerPtr->connectToDevice();
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

} // namespace thermonator
