#include "SimpleCommandBase.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::command {

SimpleCommandBase::SimpleCommandBase(char commandByte, QObject *parent)
    : QObject{parent}, mCommandByte{commandByte}
{
}

void SimpleCommandBase::encodeCommand()
{
    qDebug() << Q_FUNC_INFO;

    QByteArray command;
    constexpr auto bytesCount = 15;
    command.reserve(bytesCount);

    command.append(static_cast<int>(mCommandByte));
    command.append(QByteArray::fromHex("000000000000000000000000000000"));

    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

} // namespace thermonator::eq3thermostat::command
