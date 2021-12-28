#include "Eq3Thermostat.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

Eq3Thermostat::Eq3Thermostat(QObject *parent)
{
}

QString Eq3Thermostat::serialNumber() const
{
    return mSerialNumber;
}

void Eq3Thermostat::onSetSerialNumber(const QString &serialNumber)
{
    qDebug() << Q_FUNC_INFO << serialNumber;
    if (mSerialNumber == serialNumber) {
        return;
    }
    mSerialNumber = serialNumber;
    emit serialNumberChanged();
}

} // namespace thermonator::eq3thermostat
