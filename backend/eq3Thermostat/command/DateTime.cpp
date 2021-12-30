#include "DateTime.hpp"

#include "../../utility/Utility.hpp"

#include <QDateTime>
#include <QDebug>

#include <bitset>

namespace thermonator::eq3thermostat::command {

DateTime::DateTime(QObject *parent) : QObject{parent}
{
}

void DateTime::encodeCommand()
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
    constexpr auto bytesCount = 15;
    command.reserve(bytesCount);

    command.append(QByteArray::fromHex("03"));
    command.append(currentYear);
    command.append(currentMonth);
    command.append(currentDay);
    command.append(currentHour);
    command.append(currentMinute);
    command.append(currentSecond);

    command.append(QByteArray::fromHex("0000000000000000"));

    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

} // namespace thermonator::eq3thermostat::command
