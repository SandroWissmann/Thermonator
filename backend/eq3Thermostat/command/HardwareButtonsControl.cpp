#include "HardwareButtonsControl.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::command {

HardwareButtonsControl::HardwareButtonsControl(QObject *parent)
    : QObject{parent}
{
}

void HardwareButtonsControl::encodeCommand(HardwareButtonsControl::State state)
{
    qDebug() << Q_FUNC_INFO;

    QByteArray command;
    constexpr auto bytesCount = 15;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("80"));

    auto stateEncoded = static_cast<int>(stateToByte(state));
    command.append(stateEncoded);

    command.append(QByteArray::fromHex("0000000000000000"));

    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

char HardwareButtonsControl::stateToByte(State state)
{
    if (state == HardwareButtonsControl::State::lock) {
        return 0x01;
    }
    return 0x00;
}

} // namespace thermonator::eq3thermostat::command
