#include "ComfortAndEcoTemperature.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::command {

ComfortAndEcoTemperature::ComfortAndEcoTemperature(QObject *parent)
    : QObject{parent}
{
}

void ComfortAndEcoTemperature::encodeCommand(double comfortTemperature,
                                             double ecoTemperature)
{
    qDebug() << Q_FUNC_INFO;

    QByteArray command;
    constexpr auto bytesCount = 15;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("11"));

    auto comfortTemperatureEncoded =
        utility::encodeTemperature(comfortTemperature);
    command.append(comfortTemperatureEncoded);
    auto ecoTemperatureEncoded = utility::encodeTemperature(ecoTemperature);
    command.append(ecoTemperatureEncoded);

    command.append(QByteArray::fromHex("00000000000000"));

    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

} // namespace thermonator::eq3thermostat::command
