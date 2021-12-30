#include "IOService.hpp"

#include "../utility/Utility.hpp"

#include <QDebug>
#include <QMetaEnum>

#include <string_view>

namespace thermonator::eq3thermostat {

IOService::IOService(std::shared_ptr<QLowEnergyService> lowEnergyServicePtr,
                     QObject *parent)
    : QObject{parent}, mLowEnergyServicePtr{lowEnergyServicePtr}
{
    Q_ASSERT(mLowEnergyServicePtr);

    connect(mLowEnergyServicePtr.get(), &QLowEnergyService::stateChanged, this,
            &IOService::onServiceStateChanged);
    connect(mLowEnergyServicePtr.get(),
            &QLowEnergyService::characteristicWritten, this,
            &IOService::onCharacteristicWritten);
    connect(mLowEnergyServicePtr.get(), &QLowEnergyService::characteristicRead,
            this, &IOService::onCharacteristicRead);
    connect(mLowEnergyServicePtr.get(),
            &QLowEnergyService::characteristicChanged, this,
            &IOService::onCharacteristicChanged);
    connect(
        mLowEnergyServicePtr.get(),
        qOverload<QLowEnergyService::ServiceError>(&QLowEnergyService::error),
        this, &IOService::onServiceError);
}

void IOService::init()
{
    mLowEnergyServicePtr->discoverDetails();
}

bool IOService::ready() const
{
    return mLowEnergyServicePtr->state() ==
           QLowEnergyService::ServiceDiscovered;
}

QBluetoothUuid IOService::iOServiceUuid()
{
    return QBluetoothUuid{QString{"{3e135142-654f-9090-134a-a6ff5bb77046}"}};
}

void IOService::onWriteCommand(const QByteArray &command)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << Q_FUNC_INFO << command.toHex();
    if (!ready()) {
        return;
    }

    auto uuid = writeCharacteristicUuid();
    auto characteristic = mLowEnergyServicePtr->characteristic(uuid);
    mLowEnergyServicePtr->writeCharacteristic(characteristic, command);

    qDebug() << Q_FUNC_INFO
             << "write command: " << utility::toHexWithSpace(command);
}

QBluetoothUuid IOService::writeCharacteristicUuid()
{
    // handle = 0x411
    return QBluetoothUuid{QString{"{3fa4585a-ce4a-3bad-db4b-b8df8179ea09}"}};
}

QBluetoothUuid IOService::notifyCharacteristicUuid()
{
    // handle = 0x421
    return QBluetoothUuid{QString{"{d0e8434d-cd29-0996-af41-6c90f4e0eb2a}"}};
}

void IOService::onServiceStateChanged(
    QLowEnergyService::ServiceState serviceState)
{
    switch (serviceState) {
    case QLowEnergyService::InvalidService:
        qDebug() << Q_FUNC_INFO << "Connection to device lost. Invalid Service";
        break;
    case QLowEnergyService::DiscoveryRequired:
        qDebug() << Q_FUNC_INFO << "Service Discovery requiered";
        break;
    case QLowEnergyService::DiscoveringServices:
        qDebug() << Q_FUNC_INFO << "Discovering services...";
        break;
    case QLowEnergyService::ServiceDiscovered:
        qDebug() << Q_FUNC_INFO << "Service discovered.";
        emit serviceReady();
        break;
    case QLowEnergyService::LocalService:
        qDebug() << Q_FUNC_INFO << "Local Service.";
        break;
    default:
        qDebug() << Q_FUNC_INFO << "Unknown state";
        break;
    }
}

void IOService::onCharacteristicWritten(
    const QLowEnergyCharacteristic &characteristic, const QByteArray &value)
{
    if (characteristic.uuid() == writeCharacteristicUuid()) {
        qDebug() << Q_FUNC_INFO << "Command written. Command: "
                 << utility::toHexWithSpace(value);
    }
    else {
        // Case should never happen
        qDebug() << Q_FUNC_INFO
                 << "Unknown characteristic written. Characteristic.uuid: "
                 << characteristic.uuid()
                 << " value: " << utility::toHexWithSpace(value);
    }
}

void IOService::onCharacteristicRead(
    const QLowEnergyCharacteristic &characteristic, const QByteArray &value)
{
    // Should never be called because we should only read via notify
    qDebug() << Q_FUNC_INFO << "Characteristic read. Characteristic.uuid: "
             << characteristic.uuid()
             << " value: " << utility::toHexWithSpace(value);
}

void IOService::onCharacteristicChanged(
    const QLowEnergyCharacteristic &characteristic, const QByteArray &value)
{
    if (characteristic.uuid() == notifyCharacteristicUuid()) {
        qDebug() << Q_FUNC_INFO << "Command written. value: "
                 << utility::toHexWithSpace(value);
    }

    emit writeCommandAnswerd(value);
}

void IOService::onServiceError(QLowEnergyService::ServiceError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QLowEnergyService::ServiceError>();
    qDebug() << Q_FUNC_INFO << metaEnum.valueToKey(error);
}

} // namespace thermonator::eq3thermostat
