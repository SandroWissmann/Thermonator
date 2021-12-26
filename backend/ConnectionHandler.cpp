#include "ConnectionHandler.hpp"

namespace thermonator {

ConnectionHandler::ConnectionHandler(QObject *parent) : QObject(parent)
{
    mBluetoothLocalDevice.powerOn();

    connect(&mBluetoothLocalDevice,
            &QBluetoothLocalDevice::hostModeStateChanged, this,
            &ConnectionHandler::hostModeChanged);
}

bool ConnectionHandler::alive() const
{
    return mBluetoothLocalDevice.isValid() &&
           mBluetoothLocalDevice.hostMode() !=
               QBluetoothLocalDevice::HostPoweredOff;
}

bool ConnectionHandler::requiresAddressType() const
{
#if QT_CONFIG(bluez)
    return true;
#else
    return false;
#endif
}

QString ConnectionHandler::name() const
{
    return mBluetoothLocalDevice.name();
}

QString ConnectionHandler::address() const
{
    return mBluetoothLocalDevice.address().toString();
}

void ConnectionHandler::hostModeChanged(
    QBluetoothLocalDevice::HostMode /*mode*/)
{
    emit deviceChanged();
}

} // namespace thermonator
