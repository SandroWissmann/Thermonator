#include "BoostControl.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::command {

BoostControl::BoostControl(QObject *parent) : QObject{parent}
{
}

void BoostControl::encodeCommand(BoostControl::State state)
{
    qDebug() << Q_FUNC_INFO;

    QByteArray command;
    constexpr auto bytesCount = 15;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("45"));

    auto stateEncoded = static_cast<int>(stateToByte(state));
    command.append(stateEncoded);

    command.append(QByteArray::fromHex("0000000000000000"));

    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

char BoostControl::stateToByte(State state)
{
    if (state == BoostControl::State::on) {
        return 0xff;
    }
    return 0x00;
}

} // namespace thermonator::eq3thermostat::command
