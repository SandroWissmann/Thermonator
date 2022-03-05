#ifndef THERMONATOR_SERVICE_SCANNER_HPP
#define THERMONATOR_SERVICE_SCANNER_HPP

#include <QBluetoothUuid>
#include <QLowEnergyController>
#include <QObject>

#include <memory>
#include <vector>

class QBluetoothDeviceInfo;
class QLowEnergyController;

namespace thermonator {

class ServiceScanner : public QObject {
    Q_OBJECT
public:
    explicit ServiceScanner(QObject *parent = nullptr);

    ~ServiceScanner() = default;

    void connectAndStartScan(const QBluetoothDeviceInfo &deviceInfo);

    void disconnect();

    bool scanComplete() const;

    std::vector<QBluetoothUuid> servicesUuid() const;

    std::shared_ptr<QLowEnergyService> makeService(QBluetoothUuid uuid);

signals:
    void serviceScanCompleted();

private slots:
    void onError(QLowEnergyController::Error error);
    void onConnected();
    void onDisconnected();

    void onServiceDiscovered(const QBluetoothUuid &bluetoothUuid);
    void onServiceScanDone();

private:
    void makeConnections();

    std::unique_ptr<QLowEnergyController> mLowEnergyControllerPtr{nullptr};

    std::vector<QBluetoothUuid> mDiscoveredServicesUuids;
    bool mScanComplete{false};
    std::vector<QMetaObject::Connection> mConnections;
};

} // namespace thermonator

#endif
