#include "DeviceManager.hpp"

#include "DeviceScanner.hpp"
#include "ServiceScanner.hpp"
#include "eq3Thermostat/Controller.hpp"
#include "eq3Thermostat/Eq3Thermostat.hpp"
#include "eq3Thermostat/IOService.hpp"
#include "utility/Utility.hpp"

#include <QDebug>

namespace thermonator {

DeviceManager::DeviceManager(QObject *parent) : QObject{nullptr}
{
}

// declaration has to be in cpp to make std::unique_ptr member forward
// declaration work
DeviceManager::~DeviceManager() = default;

void DeviceManager::startScan()
{
    mDeviceScanner = std::make_unique<DeviceScanner>(this);

    connect(mDeviceScanner.get(), &DeviceScanner::scanCompleted, this,
            &DeviceManager::onDeviceScanCompleted);
    mDeviceScanner->startScan();
}

void DeviceManager::connectToIOService(const QString &macAddress)
{

    if (!mDeviceScanner) {
        qDebug() << Q_FUNC_INFO << "DeviceScanner is nullptr";
        return;
    }

    auto deviceInfoPtr = mDeviceScanner->deviceInfoPtr(macAddress);
    if (!deviceInfoPtr) {
        qDebug() << Q_FUNC_INFO << "deviceInfo with mac address " << macAddress
                 << " not found";
        return;
    }

    mServiceScanner = std::make_unique<ServiceScanner>(deviceInfoPtr, this);

    connect(mServiceScanner.get(), &ServiceScanner::serviceScanCompleted, this,
            &DeviceManager::onServiceScanCompleted);

    mServiceScanner->startScan();
}

bool DeviceManager::deviceScanComplete() const
{
    return mDeviceScanCompleted;
}

bool DeviceManager::serviceScanCompleted() const
{
    return mServiceScanCompleted;
}

bool DeviceManager::iOServiceReady() const
{
    return mIOServiceReady;
}

void DeviceManager::onDeviceScanCompleted()
{
    qDebug() << Q_FUNC_INFO;
    mDeviceScanCompleted = true;
    // TODO: mac address currently hard coded to one thermostat to be changed
    // later...
    connectToIOService("00:1A:22:16:BE:93");
}

void DeviceManager::onServiceScanCompleted()
{
    qDebug() << Q_FUNC_INFO;
    mServiceScanCompleted = true;
    if (!mServiceScanner) {
        qDebug() << Q_FUNC_INFO << "mServiceScanner is nullptr";
        return;
    }

    auto uuid = eq3thermostat::IOService::iOServiceUuid();
    auto lowEnergyServicePtr = mServiceScanner->makeService(uuid);
    if (!lowEnergyServicePtr) {
        qDebug() << Q_FUNC_INFO << "lowEnergyServicePtr is nullptr";
        return;
    }

    mEq3ThermostatIOService =
        std::make_unique<eq3thermostat::IOService>(lowEnergyServicePtr, this);

    connect(mEq3ThermostatIOService.get(),
            &eq3thermostat::IOService::serviceReady, this,
            &DeviceManager::onIOServiceReady);

    mEq3ThermostatIOService->init();
}

void DeviceManager::onIOServiceReady()
{
    qDebug() << Q_FUNC_INFO;
    if (!mEq3ThermostatIOService) {
        qDebug() << Q_FUNC_INFO << "mEq3ThermostatIOService is nullptr";
        return;
    }
    mIOServiceReady = true;

    mEq3Thermostat = std::make_unique<eq3thermostat::Eq3Thermostat>(this);
    mEq3ThermostatController =
        std::make_unique<eq3thermostat::Controller>(this);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::commandRequested,
            mEq3ThermostatIOService.get(),
            &eq3thermostat::IOService::onWriteCommand);

    connect(mEq3ThermostatIOService.get(),
            &eq3thermostat::IOService::writeCommandAnswerd,
            mEq3ThermostatController.get(),
            &eq3thermostat::Controller::onAnswerReceived);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::serialNumberReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetSerialNumber);

    mEq3ThermostatController->requestSerialNumber();
}

} // namespace thermonator
