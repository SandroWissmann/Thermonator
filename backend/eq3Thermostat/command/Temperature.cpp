#include "Temperature.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

#include <algorithm>

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

    int temperatureEncoded = encodeTemperature(temperature);
    command.append(temperatureEncoded);

    command.append(QByteArray::fromHex("0000000000000000"));

    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

int Temperature::encodeTemperature(double temperature)
{
    constexpr auto minTemperature = 5.0;
    constexpr auto maxTemperature = 29.5;

    temperature = std::clamp(temperature, minTemperature, maxTemperature);

    auto temperatureEncoded = static_cast<int>(temperature * 2);
    return temperatureEncoded;
}

} // namespace thermonator::eq3thermostat::command
