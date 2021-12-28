#ifndef THERMONATOR_DEVICE_MANAGER_HPP
#define THERMONATOR_DEVICE_MANAGER_HPP

#include <QObject>

#include <memory>

namespace thermonator {

class DeviceScanner;
class ServiceScanner;

namespace eq3thermostat {

class IOService;
class Controller;
class Eq3Thermostat;

} // namespace eq3thermostat

// might change later used to glue member classes together to connect to device
// service and send / receive commands
class DeviceManager : public QObject {
    Q_OBJECT
public:
    explicit DeviceManager(QObject *parent = nullptr);

    ~DeviceManager();

    void startScan();
    void connectToIOService(const QString &macAddress);

    bool deviceScanComplete() const;
    bool serviceScanCompleted() const;
    bool iOServiceReady() const;

private slots:
    void onDeviceScanCompleted();
    void onServiceScanCompleted();
    void onIOServiceReady();

private:
    std::unique_ptr<DeviceScanner> mDeviceScanner;
    std::unique_ptr<ServiceScanner> mServiceScanner;
    std::unique_ptr<eq3thermostat::IOService> mEq3ThermostatIOService;
    std::unique_ptr<eq3thermostat::Eq3Thermostat> mEq3Thermostat;
    std::unique_ptr<eq3thermostat::Controller> mEq3ThermostatController;

    bool mDeviceScanCompleted{false};
    bool mServiceScanCompleted{false};
    bool mIOServiceReady{false};
};

} // namespace thermonator

#endif
