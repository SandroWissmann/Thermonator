#ifndef THERMONATOR_DEVICE_MANAGER_HPP
#define THERMONATOR_DEVICE_MANAGER_HPP

#include <QObject>

#include <memory>

namespace thermonator {

class DeviceScanner;
class ServiceScanner;

namespace eq3thermostat {

class IOService;

}

// might change later used to glue member classes together to connect to device
// service and send / receive commands
class DeviceManager : public QObject {
    Q_OBJECT
public:
    explicit DeviceManager(QObject *parent = nullptr);

    ~DeviceManager();

    void startScan();
    void connectToIOService(const QString &macAddress);
    void sendCommand(const QByteArray &command);

    bool deviceScanComplete() const;
    bool serviceScanCompleted() const;
    bool iOServiceReady() const;

private slots:
    void onDeviceScanCompleted();
    void onServiceScanCompleted();
    void onIOServiceReady();
    void onWriteCommandAnswered(const QByteArray &answer);

private:
    std::unique_ptr<DeviceScanner> mDeviceScanner;
    std::unique_ptr<ServiceScanner> mServiceScanner;
    std::unique_ptr<eq3thermostat::IOService> mEq3ThermostatIOService;

    bool mDeviceScanCompleted{false};
    bool mServiceScanCompleted{false};
    bool mIOServiceReady{false};
};

} // namespace thermonator

#endif
