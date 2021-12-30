#include "SerialNumberNotification.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::answer {

SerialNumberNotification::SerialNumberNotification(QObject *parent)
    : QObject{parent}
{
}

void SerialNumberNotification::decodeAnswer(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO << "Answer: " << utility::toHexWithSpace(answer);

    const QByteArray serialNumberBytes = answer.mid(4, 10);

    qDebug() << Q_FUNC_INFO << "SerialNumberBytes:"
             << utility::toHexWithSpace(serialNumberBytes);

    QString serialNumber;
    serialNumber.reserve(serialNumberBytes.size());

    for (const auto &serialNumberByte : serialNumberBytes) {
        auto asciiSign = utility::hexToAscii(serialNumberByte);
        serialNumber.push_back(asciiSign);
    }

    qDebug() << Q_FUNC_INFO << "serial number:" << serialNumber;
    emit answerDecoded(serialNumber);
}

} // namespace thermonator::eq3thermostat::answer
