#include "SetCurrentDateTimeCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDateTime>
#include <QDebug>

#include <bitset>

namespace thermonator::eq3thermostat::types {

SetCurrentDateTimeCommand::SetCurrentDateTimeCommand() : mCommand{encode()}
{
}

QByteArray SetCurrentDateTimeCommand::encoded() const
{
    return mCommand;
}

QByteArray SetCurrentDateTimeCommand::encode()
{
    qDebug() << Q_FUNC_INFO;
    auto currentDateTime = QDateTime::currentDateTime();

    qDebug() << Q_FUNC_INFO << "currentDateTime:" << currentDateTime;
    auto currentYear = currentDateTime.toString("yy").toInt();
    auto currentMonth = currentDateTime.toString("MM").toInt();
    auto currentDay = currentDateTime.toString("dd").toInt();
    auto currentHour = currentDateTime.toString("hh").toInt();
    auto currentMinute = currentDateTime.toString("mm").toInt();
    auto currentSecond = currentDateTime.toString("ss").toInt();

    QByteArray command;
    constexpr auto bytesCount = 7;
    command.reserve(bytesCount);

    command.append(QByteArray::fromHex("03"));
    command.append(currentYear);
    command.append(currentMonth);
    command.append(currentDay);
    command.append(currentHour);
    command.append(currentMinute);
    command.append(currentSecond);

    return command;
}

QDebug operator<<(QDebug debug,
                  const SetCurrentDateTimeCommand &setCurrentDateTimeCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetCurrentDateTimeCommand: "
                    << utility::toHexWithSpace(
                           setCurrentDateTimeCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat::types
