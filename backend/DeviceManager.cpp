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

    // Command SerialNumber connections

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::serialNumberReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetSerialNumber);

    // mEq3ThermostatController->requestSerialNumber();

    // Command DateTime connections

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::temperatureOffsetReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetTemperatureOffset);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::ecoTemperatureReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetEcoTemperature);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::comfortTemperatureReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetComfortTemperature);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::openWindowIntervalReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetOpenWindowInterval);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::openWindowTemperatureReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetOpenWindowTemperature);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::minuteReceived, mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetMinute);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::hourReceived, mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetHour);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::dayReceived, mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetDay);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::monthReceived, mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetMonth);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::yearReceived, mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetYear);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::targetTemperatureReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetTargetTemperature);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::valvePositionReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetValvePosition);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::autoModeEnabledReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetAutoModeEnabled);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::manualModeEnabledReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetManualModeEnabled);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::vacationModeEnabledReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetVacationModeEnabled);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::boostEnabledReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetBoostEnabled);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::daylightSummerTimeEnabledReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetDaylightSummerTimeEnabled);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::openWindowModeEnabledReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetOpenWindowModeEnabled);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::hardwareButtonsLockedReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetHardwareButtonsLocked);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::unknownEnabledReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetUnknownEnabled);

    connect(mEq3ThermostatController.get(),
            &eq3thermostat::Controller::lowBatteryEnabledReceived,
            mEq3Thermostat.get(),
            &eq3thermostat::Eq3Thermostat::onSetLowBatteryEnabled);

    // mEq3ThermostatController->setCurrentDateTime();

    // Command Temperature connections

    // mEq3ThermostatController->setTemperature(21.5);

    mEq3ThermostatController->setComfortAndEcoTemperature(21.5, 17.5);
}

} // namespace thermonator
