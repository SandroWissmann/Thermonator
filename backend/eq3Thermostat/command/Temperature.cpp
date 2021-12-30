#include "Temperature.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::command {

Temperature::Temperature(QObject *parent) : QObject{parent}
{
}

void Temperature::encodeCommand(double temperature)
{
    qDebug() << Q_FUNC_INFO;

    QByteArray command;
    constexpr auto bytesCount = 15;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("41"));

    auto temperatureEncoded = utility::encodeTemperature(temperature);
    command.append(temperatureEncoded);

    command.append(QByteArray::fromHex("0000000000000000"));

    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

} // namespace thermonator::eq3thermostat::command
