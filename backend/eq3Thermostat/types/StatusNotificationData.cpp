#include "StatusNotificationData.hpp"

#include "../../utility/Utility.hpp"

namespace thermonator::eq3thermostat::types {

StatusNotificationData::StatusNotificationData(
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

StatusNotificationData
StatusNotificationData::fromEncodedData(const QByteArray &data)
{
    qDebug() << Q_FUNC_INFO << "data:" << utility::toHexWithSpace(data);

    auto bytes = utility::toUChars(data);

    if (data.size() != 15) {
        qDebug() << Q_FUNC_INFO << "data has wrong size";
        return StatusNotificationData{};
    }
    if (data.at(0) != 0x02) {
        qDebug() << Q_FUNC_INFO
                 << "first byte of data has wrong value: " << Qt::hex
                 << static_cast<int>(data.at(0));
        return StatusNotificationData{};
    }
    if (data.at(1) != 0x01) {
        qDebug() << Q_FUNC_INFO
                 << "second byte of data has wrong value: " << Qt::hex
                 << static_cast<int>(data.at(1));
        return StatusNotificationData{};
    }

    types::StatusFlags statusFlags{bytes.at(2)};

    types::ValvePosition valvePosition{bytes.at(3)};
    if (!valvePosition.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "valvePosition is invalid. value:" << valvePosition;
        return StatusNotificationData{};
    }

    types::UnknownStatusByte unknownStatusByte{bytes.at(4)};

    types::Temperature targetTemperature{bytes.at(5)};
    if (!targetTemperature.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "targetTemperature is invalid. value:" << targetTemperature;
        return StatusNotificationData{};
    }

    types::DateTime holidayEndDateTime{bytes.at(7), bytes.at(8), bytes.at(6),
                                       bytes.at(9)};
    if (statusFlags.vacationModeEnabled() && !holidayEndDateTime.isValid()) {
        qDebug() << Q_FUNC_INFO << "holidayEndDateTime is invalid. value:"
                 << holidayEndDateTime;
        return StatusNotificationData{};
    }

    types::Temperature openWindowTemperature{bytes.at(10)};
    if (!openWindowTemperature.isValid()) {
        qDebug() << Q_FUNC_INFO << "openWindowTemperature is invalid. value:"
                 << openWindowTemperature;
        return StatusNotificationData{};
    }

    types::OpenWindowInterval openWindowInterval(bytes.at(11));
    if (!openWindowInterval.isValid()) {
        qDebug() << Q_FUNC_INFO << "openWindowInterval is invalid. value:"
                 << openWindowInterval;
        return StatusNotificationData{};
    }

    types::Temperature comfortTemperature{bytes.at(12)};
    if (!comfortTemperature.isValid()) {
        qDebug() << Q_FUNC_INFO << "comfortTemperature is invalid. value:"
                 << comfortTemperature;
        return StatusNotificationData{};
    }

    types::Temperature ecoTemperature{bytes.at(13)};
    if (!ecoTemperature.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "ecoTemperature is invalid. value:" << ecoTemperature;
        return StatusNotificationData{};
    }

    types::TemperatureOffset temperatureOffset{bytes.at(14)};
    if (!temperatureOffset.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "temperatureOffset is invalid. value:" << temperatureOffset;
        return StatusNotificationData{};
    }

    StatusNotificationData statusNotificationData{
        statusFlags,        valvePosition,      unknownStatusByte,
        targetTemperature,  holidayEndDateTime, openWindowTemperature,
        openWindowInterval, comfortTemperature, ecoTemperature,
        temperatureOffset};
    return statusNotificationData;
}

bool StatusNotificationData::isValid() const
{
    if (!mValvePosition.isValid()) {
        return false;
    }
    if (!mUnknownStatusByte.isValid()) {
        return false;
    }
    if (!mTargetTemperature.isValid()) {
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

StatusFlags StatusNotificationData::statusFlags() const
{
    return mStatusFlags;
}

ValvePosition StatusNotificationData::valvePosition() const
{
    return mValvePosition;
}

UnknownStatusByte StatusNotificationData::unknownStatusByte() const
{
    return mUnknownStatusByte;
}

Temperature StatusNotificationData::targetTemperature() const
{
    return mTargetTemperature;
}

DateTime StatusNotificationData::holidayEndDateTime() const
{
    return mHolidayEndDateTime;
}

Temperature StatusNotificationData::openWindowTemperature() const
{
    return mOpenWindowTemperature;
}

OpenWindowInterval StatusNotificationData::openWindowInterval() const
{
    return mOpenWindowInterval;
}

Temperature StatusNotificationData::comfortTemperature() const
{
    return mComfortTemperature;
}

Temperature StatusNotificationData::ecoTemperature() const
{
    return mEcoTemperature;
}

TemperatureOffset StatusNotificationData::temperatureOffset() const
{
    return mTemperatureOffset;
}

QDebug operator<<(QDebug debug,
                  const StatusNotificationData &statusNotificationData)
{
    QDebugStateSaver saver(debug);

    debug.nospace()
        << "statusFlags: " << statusNotificationData.statusFlags() << '\n'
        << "valvePosition: " << statusNotificationData.valvePosition() << '\n'
        << "unknownStatusByte: " << statusNotificationData.unknownStatusByte()
        << '\n'
        << "targetTemperature: " << statusNotificationData.targetTemperature()
        << '\n'
        << "holidayEndDateTime: " << statusNotificationData.holidayEndDateTime()
        << '\n'
        << "openWindowTemperature: "
        << statusNotificationData.openWindowTemperature() << '\n'
        << "openWindowInterval: " << statusNotificationData.openWindowInterval()
        << '\n'
        << "comfortTemperature: " << statusNotificationData.comfortTemperature()
        << '\n'
        << "ecoTemperature: " << statusNotificationData.ecoTemperature() << '\n'
        << "temperatureOffset: " << statusNotificationData.temperatureOffset();

    return debug;
}

} // namespace thermonator::eq3thermostat::types
