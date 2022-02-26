#ifndef THERMONATOR_GUICONTROLLER_SCANCONNECTWINDOWCONTROLLER_HPP
#define THERMONATOR_GUICONTROLLER_SCANCONNECTWINDOWCONTROLLER_HPP

#include <QObject>
#include <QString>

namespace thermonator::guiController {

class ScanConnectWindowController : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool connectButtonIsActive READ connectButtonIsActive NOTIFY
                   connectButtonIsActiveChanged)
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

    Q_INVOKABLE
    void startScanning();

    Q_INVOKABLE
    void connectToBluetoothDevice();

signals:
    void connectButtonIsActiveChanged();

    void requestStartScanning();
    void requestConnectToBluetooothDevice(const QString &macAddress);

private:
    QString m_selectedBluetoothDeviceMacAddress;
};

} // namespace thermonator::guiController

Q_DECLARE_METATYPE(thermonator::guiController::ScanConnectWindowController *)

#endif
