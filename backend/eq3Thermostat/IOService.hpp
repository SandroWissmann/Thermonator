#ifndef THERMONATOR_EQ3THERMOSTAT_IOSERVICE_HPP
#define THERMONATOR_EQ3THERMOSTAT_IOSERVICE_HPP

#include <QLowEnergyService>
#include <QObject>

#include <memory>

/*
Available Service UUID on eq3thermostat:

"{00001801-0000-1000-8000-00805f9b34fb}"
"{0000180a-0000-1000-8000-00805f9b34fb}"
"{3e135142-654f-9090-134a-a6ff5bb77046}" -> For read / write commands
"{9e5d1e47-5c13-43a0-8635-82ad38a1386f}"
*/

namespace thermonator::eq3thermostat {

class IOService : public QObject {
    Q_OBJECT
public:
    explicit IOService(std::shared_ptr<QLowEnergyService> lowEnergyServicePtr,
                       QObject *parent = nullptr);

    ~IOService() = default;

    // has to be called to make slots working
    void init();

    // indicate if service finished scan for characteristics so we can use the
    // service
    bool ready() const;

    static QBluetoothUuid iOServiceUuid();

public slots:
    // writes a command to the thermostat. Note there is no check if command
    // is valid here
    void onWriteCommand(const QByteArray &command);

signals:
    // indicate if service finished scan for characteristics so we can use the
    // service
    void serviceReady();

    // after write a command from the sending characteristic we should
    // receive an answer
    void writeCommandAnswerd(const QByteArray &answer);

private:
    static QBluetoothUuid writeCharacteristicUuid();
    static QBluetoothUuid notifyCharacteristicUuid();

    void onServiceStateChanged(QLowEnergyService::ServiceState serviceState);

    void onCharacteristicWritten(const QLowEnergyCharacteristic &characteristic,
                                 const QByteArray &value);

    void onCharacteristicRead(const QLowEnergyCharacteristic &characteristic,
                              const QByteArray &value);

    void onCharacteristicChanged(const QLowEnergyCharacteristic &characteristic,
                                 const QByteArray &value);

    void onServiceError(QLowEnergyService::ServiceError error);

private:
    std::shared_ptr<QLowEnergyService> mLowEnergyServicePtr;
};

} // namespace thermonator::eq3thermostat

#endif
