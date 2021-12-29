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

void SerialNumber::decodeAnswer(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO << "Answer: " << utility::toHexWithSpace(answer);

    const QByteArray serialNumberBytes = answer.mid(4, 10);

    qDebug() << Q_FUNC_INFO << "SerialNumberBytes:"
             << utility::toHexWithSpace(serialNumberBytes);

    QString serialNumber;
    serialNumber.reserve(serialNumberBytes.size());

    for (const auto &serialNumberByte : serialNumberBytes) {
        auto asciiSign = hexToAscii(serialNumberByte);
        serialNumber.push_back(asciiSign);
    }

    qDebug() << Q_FUNC_INFO << "serial number:" << serialNumber;
    emit answerDecoded(serialNumber);
}

char SerialNumber::hexToAscii(char hex)
{
    return char(hex - 0x30);
}

} // namespace thermonator::eq3thermostat::command
