#include "DayTimer.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::command {

DayTimer::DayTimer(QObject *parent) : QObject{parent}
{
}

void DayTimer::encodeCommand(types::DayOfWeek dayOfWeek)
{
    qDebug() << Q_FUNC_INFO;

    QByteArray command;
    constexpr auto bytesCount = 15;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("20"));

    auto dayOfWeekEncoded = static_cast<int>(dayOfWeek);
    command.append(dayOfWeekEncoded);

    command.append(QByteArray::fromHex("0000000000000000"));

    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

} // namespace thermonator::eq3thermostat::command
