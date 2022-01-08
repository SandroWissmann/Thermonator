#include "StatusNotification.hpp"

#include "../../utility/Utility.hpp"

namespace thermonator::eq3thermostat {

StatusNotification::StatusNotification(
    StatusFlags statusFlags, ValvePosition valvePosition,
    UnknownStatusByte unknownStatusByte, Temperature targetTemperature,
    DateTime holidayEndDateTime, Temperature openWindowTemperature,
    OpenWindowInterval openWindowInterval, Temperature comfortTemperature,
    Temperature ecoTemperature, TemperatureOffset temperatureOffset)

    : mStatusFlags{statusFlags}, mValvePosition{valvePosition},
      mUnknownStatusByte{unknownStatusByte},
      mTargetTemperature{targetTemperature},
      mHolidayEndDateTime{holidayEndDateTime},
      mOpenWindowTemperature{openWindowTemperature},
      mOpenWindowInterval{openWindowInterval},
      mComfortTemperature{comfortTemperature}, mEcoTemperature{ecoTemperature},
      mTemperatureOffset{temperatureOffset}
{
}

StatusNotification StatusNotification::fromEncodedData(const QByteArray &data)
{
    qDebug() << Q_FUNC_INFO << "data:" << utility::toHexWithSpace(data);

    auto bytes = utility::toUChars(data);

    if (data.size() != 15) {
        qDebug() << Q_FUNC_INFO << "data has wrong size";
        return StatusNotification{};
    }
    if (data.at(0) != 0x02) {
        qDebug() << Q_FUNC_INFO
                 << "first byte of data has wrong value: " << Qt::hex
                 << static_cast<int>(data.at(0));
        return StatusNotification{};
    }
    if (data.at(1) != 0x01) {
        qDebug() << Q_FUNC_INFO
                 << "second byte of data has wrong value: " << Qt::hex
                 << static_cast<int>(data.at(1));
        return StatusNotification{};
    }

    StatusFlags statusFlags{bytes.at(2)};

    ValvePosition valvePosition{bytes.at(3)};
    if (!valvePosition.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "valvePosition is invalid. value:" << valvePosition;
        return StatusNotification{};
    }

    UnknownStatusByte unknownStatusByte{bytes.at(4)};

    Temperature targetTemperature{bytes.at(5)};
    if (!targetTemperature.isValid() &&
        !targetTemperature.isThermostatOffTemperature() &&
        !targetTemperature.isThermostatOnTemperature()) {
        qDebug() << Q_FUNC_INFO
                 << "targetTemperature is invalid. value:" << targetTemperature;
        return StatusNotification{};
    }

    DateTime holidayEndDateTime{bytes.at(7), bytes.at(8), bytes.at(6),
                                bytes.at(9)};
    if (statusFlags.vacationModeEnabled() && !holidayEndDateTime.isValid()) {
        qDebug() << Q_FUNC_INFO << "holidayEndDateTime is invalid. value:"
                 << holidayEndDateTime;
        return StatusNotification{};
    }

    Temperature openWindowTemperature{bytes.at(10)};
    if (!openWindowTemperature.isValid()) {
        qDebug() << Q_FUNC_INFO << "openWindowTemperature is invalid. value:"
                 << openWindowTemperature;
        return StatusNotification{};
    }

    OpenWindowInterval openWindowInterval(bytes.at(11));
    if (!openWindowInterval.isValid()) {
        qDebug() << Q_FUNC_INFO << "openWindowInterval is invalid. value:"
                 << openWindowInterval;
        return StatusNotification{};
    }

    Temperature comfortTemperature{bytes.at(12)};
    if (!comfortTemperature.isValid()) {
        qDebug() << Q_FUNC_INFO << "comfortTemperature is invalid. value:"
                 << comfortTemperature;
        return StatusNotification{};
    }

    Temperature ecoTemperature{bytes.at(13)};
    if (!ecoTemperature.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "ecoTemperature is invalid. value:" << ecoTemperature;
        return StatusNotification{};
    }

    TemperatureOffset temperatureOffset{bytes.at(14)};
    if (!temperatureOffset.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "temperatureOffset is invalid. value:" << temperatureOffset;
        return StatusNotification{};
    }

    StatusNotification statusNotification{
        statusFlags,        valvePosition,      unknownStatusByte,
        targetTemperature,  holidayEndDateTime, openWindowTemperature,
        openWindowInterval, comfortTemperature, ecoTemperature,
        temperatureOffset};
    return statusNotification;
}

bool StatusNotification::isValid() const
{
    if (!mValvePosition.isValid()) {
        return false;
    }
    if (!mUnknownStatusByte.isValid()) {
        return false;
    }
    if (!mTargetTemperature.isValid() &&
        !mTargetTemperature.isThermostatOffTemperature() &&
        !mTargetTemperature.isThermostatOnTemperature()) {
        return false;
    }
    // When vacation flag is not set we dont get a valid time from the
    // thermostat
    if (mStatusFlags.vacationModeEnabled() && !mHolidayEndDateTime.isValid()) {
        return false;
    }
    if (!mOpenWindowTemperature.isValid()) {
        return false;
    }
    if (!mOpenWindowInterval.isValid()) {
        return false;
    }
    if (!mComfortTemperature.isValid()) {
        return false;
    }
    if (!mEcoTemperature.isValid()) {
        return false;
    }
    if (!mTemperatureOffset.isValid()) {
        return false;
    }
    return true;
}

StatusFlags StatusNotification::statusFlags() const
{
    return mStatusFlags;
}

ValvePosition StatusNotification::valvePosition() const
{
    return mValvePosition;
}

UnknownStatusByte StatusNotification::unknownStatusByte() const
{
    return mUnknownStatusByte;
}

Temperature StatusNotification::targetTemperature() const
{
    return mTargetTemperature;
}

DateTime StatusNotification::holidayEndDateTime() const
{
    return mHolidayEndDateTime;
}

Temperature StatusNotification::openWindowTemperature() const
{
    return mOpenWindowTemperature;
}

OpenWindowInterval StatusNotification::openWindowInterval() const
{
    return mOpenWindowInterval;
}

Temperature StatusNotification::comfortTemperature() const
{
    return mComfortTemperature;
}

Temperature StatusNotification::ecoTemperature() const
{
    return mEcoTemperature;
}

TemperatureOffset StatusNotification::temperatureOffset() const
{
    return mTemperatureOffset;
}

QDebug operator<<(QDebug debug, const StatusNotification &statusNotification)
{
    QDebugStateSaver saver(debug);

    debug.nospace()
        << "statusFlags: " << statusNotification.statusFlags() << '\n'
        << "valvePosition: " << statusNotification.valvePosition() << '\n'
        << "unknownStatusByte: " << statusNotification.unknownStatusByte()
        << '\n'
        << "targetTemperature: " << statusNotification.targetTemperature()
        << '\n'
        << "holidayEndDateTime: " << statusNotification.holidayEndDateTime()
        << '\n'
        << "openWindowTemperature: "
        << statusNotification.openWindowTemperature() << '\n'
        << "openWindowInterval: " << statusNotification.openWindowInterval()
        << '\n'
        << "comfortTemperature: " << statusNotification.comfortTemperature()
        << '\n'
        << "ecoTemperature: " << statusNotification.ecoTemperature() << '\n'
        << "temperatureOffset: " << statusNotification.temperatureOffset();

    return debug;
}

} // namespace thermonator::eq3thermostat
