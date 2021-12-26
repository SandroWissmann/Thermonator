#ifndef THERMONATOR_EQ3THERMOSTAT_IOSERVICE_HPP
#define THERMONATOR_EQ3THERMOSTAT_IOSERVICE_HPP

#include <QLowEnergyService>
#include <QObject>

#include <memory>

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

    // writes a command to the thermostat. Note there is no check if command
    // is valid here
    void writeCommand(const QByteArray &command);

    static QBluetoothUuid iOServiceUuid();

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
