#include "ConfigureOffsetTemperature.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::command {

ConfigureOffsetTemperature::ConfigureOffsetTemperature(QObject *parent)
    : QObject{parent}
{
}

void ConfigureOffsetTemperature::encodeCommand(double offsetTemperature)
{
    Q_ASSERT(offsetTemperature >= -3.5 && offsetTemperature <= 3.5);
    qDebug() << Q_FUNC_INFO;

    QByteArray command;
    constexpr auto bytesCount = 15;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("13"));

    auto offsetTemperatureEncoded = static_cast<int>(offsetTemperature * 2) + 7;
    command.append(offsetTemperatureEncoded);

    command.append(QByteArray::fromHex("0000000000000000"));

    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

} // namespace thermonator::eq3thermostat::command
