#ifndef THERMONATOR_GUI_PAGES_SCANCONNECTPAGE_SCANCONNECTPAGECONTROLLER_HPP
#define THERMONATOR_GUI_PAGES_SCANCONNECTPAGE_SCANCONNECTPAGECONTROLLER_HPP

#include <QObject>
#include <QString>

class QBluetoothDeviceInfo;

namespace thermonator::gui {

class ScannedDevicesModel;

class ScanConnectPageController : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool connectButtonIsActive READ connectButtonIsActive NOTIFY
                   connectButtonIsActiveChanged)
    Q_PROPERTY(thermonator::gui::ScannedDevicesModel *scannedDevicesModel READ
                   scannedDevicesModel CONSTANT)
public:
    ScanConnectPageController(QObject *parent = nullptr);

    ScanConnectPageController(const ScanConnectPageController &) = delete;
    ScanConnectPageController &
    operator=(const ScanConnectPageController &) = delete;
    ScanConnectPageController(ScanConnectPageController &&) = delete;
    ScanConnectPageController &operator=(ScanConnectPageController &&) = delete;
    ~ScanConnectPageController() = default;

    bool connectButtonIsActive();

    thermonator::gui::ScannedDevicesModel *scannedDevicesModel();

    Q_INVOKABLE
    void startScanning();

    Q_INVOKABLE
    void selectScannedDevice(const QString &macAddress);

    Q_INVOKABLE
    void connectToSelectedBluetoothDevice();

signals:
    void connectButtonIsActiveChanged();

    void requestStartScanning();
    void requestConnectToBluetooothDevice(const QString &macAddress);

public slots:
    void onReceiveNewDevice(const QBluetoothDeviceInfo &deviceInfo);

private:
    QString m_selectedBluetoothDeviceMacAddress;

    ScannedDevicesModel *m_scannedDevicesModelPtr;
};

} // namespace thermonator::gui

Q_DECLARE_METATYPE(thermonator::gui::ScanConnectPageController *)

#endif
