#ifndef THERMONATOR_GUI_SCANCONNECTWINDOWCONTROLLER_HPP
#define THERMONATOR_GUI_SCANCONNECTWINDOWCONTROLLER_HPP

#include <QObject>
#include <QString>

class QBluetoothDeviceInfo;

namespace thermonator::gui {

class ScannedDevicesModel;

class ScanConnectWindowController : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool connectButtonIsActive READ connectButtonIsActive NOTIFY
                   connectButtonIsActiveChanged)
    Q_PROPERTY(ScannedDevicesModel *scannedDevicesModel READ scannedDevicesModel
                   CONSTANT)
public:
    ScanConnectWindowController(QObject *parent = nullptr);

    ScanConnectWindowController(const ScanConnectWindowController &) = delete;
    ScanConnectWindowController &
    operator=(const ScanConnectWindowController &) = delete;
    ScanConnectWindowController(ScanConnectWindowController &&) = delete;
    ScanConnectWindowController &
    operator=(ScanConnectWindowController &&) = delete;
    ~ScanConnectWindowController() = default;

    bool connectButtonIsActive();

    ScannedDevicesModel *scannedDevicesModel();

    Q_INVOKABLE
    void startScanning();

    Q_INVOKABLE
    void connectToBluetoothDevice();

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

Q_DECLARE_METATYPE(thermonator::gui::ScanConnectWindowController *)

#endif
