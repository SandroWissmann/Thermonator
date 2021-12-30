#include "SerialNumber.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::command {

SerialNumber::SerialNumber(QObject *parent) : QObject{parent}
{
}

void SerialNumber::encodeCommand()
{
    qDebug() << Q_FUNC_INFO;
    auto command = QByteArray::fromHex("00000000000000000000000000000000");
    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

} // namespace thermonator::eq3thermostat::command
