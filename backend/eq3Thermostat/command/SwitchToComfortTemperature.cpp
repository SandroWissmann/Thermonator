#include "SwitchToComfortTemperature.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::command {

SwitchToComfortTemperature::SwitchToComfortTemperature(QObject *parent)
    : QObject{parent}
{
}

void SwitchToComfortTemperature::encodeCommand()
{
    qDebug() << Q_FUNC_INFO;
    auto command = QByteArray::fromHex("43000000000000000000000000000000");
    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

} // namespace thermonator::eq3thermostat::command
