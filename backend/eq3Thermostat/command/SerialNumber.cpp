#include "SerialNumber.hpp"

#include <QDebug>

#include "../../utility/Utility.hpp"

namespace thermonator::eq3thermostat::command {

SerialNumber::SerialNumber(QObject *parent) : QObject{parent}
{
}

void SerialNumber::encodeCommand()
{
    qDebug() << Q_FUNC_INFO;
    auto command = QByteArray::fromHex("00000000000000000000000000000000");
    emit commandEncoded(command);
}

void SerialNumber::decodeAnswer(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO;

    const QByteArray serialNumberBytes = answer.mid(4, 10);

    qDebug() << Q_FUNC_INFO << utility::toHexWithSpace(serialNumberBytes);

    QString serialNumber;
    serialNumber.reserve(serialNumberBytes.size());

    for (const auto &serialNumberByte : serialNumberBytes) {
        auto asciiSign = hexToAscii(serialNumberByte);
        serialNumber.push_back(asciiSign);
    }

    qDebug() << Q_FUNC_INFO << serialNumber;
    emit answerDecoded(serialNumber);
}

char SerialNumber::hexToAscii(char hex)
{
    return char(hex - 0x30);
}

} // namespace thermonator::eq3thermostat::command
