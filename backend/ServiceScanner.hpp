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
    explicit ServiceScanner(std::shared_ptr<QBluetoothDeviceInfo> deviceInfoPtr,
                            QObject *parent = nullptr);

    ~ServiceScanner() = default;

    void startScan();

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
    std::unique_ptr<QLowEnergyController> mLowEnergyControllerPtr;

    std::vector<QBluetoothUuid> mDiscoveredServicesUuids;
    bool mScanComplete{false};
};

} // namespace thermonator

#endif
