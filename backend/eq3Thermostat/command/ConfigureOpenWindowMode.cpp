#include "ConfigureOpenWindowMode.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::command {

ConfigureOpenWindowMode::ConfigureOpenWindowMode(QObject *parent)
    : QObject{parent}
{
}

void ConfigureOpenWindowMode::encodeCommand(double openWindowTemperature,
                                            int openWindowIntervall)
{
    Q_ASSERT(openWindowTemperature >= 5.0 && openWindowTemperature <= 29.5);
    Q_ASSERT(openWindowIntervall >= 0 && openWindowIntervall <= 60);
    qDebug() << Q_FUNC_INFO;

    QByteArray command;
    constexpr auto bytesCount = 15;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("14"));

    auto openWindowTemperatureEncoded =
        static_cast<int>(openWindowTemperature * 2);
    command.append(openWindowTemperatureEncoded);
    auto openWindowIntervallEncoded = static_cast<int>(openWindowIntervall / 5);
    command.append(openWindowIntervallEncoded);

    command.append(QByteArray::fromHex("00000000000000"));

    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

} // namespace thermonator::eq3thermostat::command
