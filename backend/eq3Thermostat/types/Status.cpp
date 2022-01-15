#include "Status.hpp"

namespace thermonator::eq3thermostat {

Status::Status(StatusFlags statusFlags, ValvePosition valvePosition,
               UnknownStatusByte unknownStatusByte,
               Temperature targetTemperature, DateTime holidayEndDateTime,
               Temperature openWindowTemperature,
               OpenWindowInterval openWindowInterval,
               Temperature comfortTemperature, Temperature ecoTemperature,
               TemperatureOffset temperatureOffset)

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

Status Status::fromEncodedBytes(const std::array<unsigned char, 13> &bytes)
{
    StatusFlags statusFlags{bytes.at(0)};

    ValvePosition valvePosition{bytes.at(1)};
    if (!valvePosition.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "valvePosition is invalid. value:" << valvePosition;
        return Status{};
    }

    UnknownStatusByte unknownStatusByte{bytes.at(2)};

    Temperature targetTemperature{bytes.at(3)};
    if (!targetTemperature.isValid() &&
        !targetTemperature.isThermostatOffTemperature() &&
        !targetTemperature.isThermostatOnTemperature()) {
        qDebug() << Q_FUNC_INFO
                 << "targetTemperature is invalid. value:" << targetTemperature;
        return Status{};
    }

    DateTime holidayEndDateTime{bytes.at(5), bytes.at(6), bytes.at(4),
                                bytes.at(7)};
    if (statusFlags.vacationModeEnabled() && !holidayEndDateTime.isValid()) {
        qDebug() << Q_FUNC_INFO << "holidayEndDateTime is invalid. value:"
                 << holidayEndDateTime;
        return Status{};
    }

    Temperature openWindowTemperature{bytes.at(8)};
    if (!openWindowTemperature.isValid()) {
        qDebug() << Q_FUNC_INFO << "openWindowTemperature is invalid. value:"
                 << openWindowTemperature;
        return Status{};
    }

    OpenWindowInterval openWindowInterval(bytes.at(9));
    if (!openWindowInterval.isValid()) {
        qDebug() << Q_FUNC_INFO << "openWindowInterval is invalid. value:"
                 << openWindowInterval;
        return Status{};
    }

    Temperature comfortTemperature{bytes.at(10)};
    if (!comfortTemperature.isValid()) {
        qDebug() << Q_FUNC_INFO << "comfortTemperature is invalid. value:"
                 << comfortTemperature;
        return Status{};
    }

    Temperature ecoTemperature{bytes.at(11)};
    if (!ecoTemperature.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "ecoTemperature is invalid. value:" << ecoTemperature;
        return Status{};
    }

    TemperatureOffset temperatureOffset{bytes.at(12)};
    if (!temperatureOffset.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "temperatureOffset is invalid. value:" << temperatureOffset;
        return Status{};
    }

    Status status{statusFlags,        valvePosition,      unknownStatusByte,
                  targetTemperature,  holidayEndDateTime, openWindowTemperature,
                  openWindowInterval, comfortTemperature, ecoTemperature,
                  temperatureOffset};
    return status;
}

bool Status::isValid() const
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

StatusFlags Status::statusFlags() const
{
    return mStatusFlags;
}

ValvePosition Status::valvePosition() const
{
    return mValvePosition;
}

UnknownStatusByte Status::unknownStatusByte() const
{
    return mUnknownStatusByte;
}

Temperature Status::targetTemperature() const
{
    return mTargetTemperature;
}

DateTime Status::holidayEndDateTime() const
{
    return mHolidayEndDateTime;
}

Temperature Status::openWindowTemperature() const
{
    return mOpenWindowTemperature;
}

OpenWindowInterval Status::openWindowInterval() const
{
    return mOpenWindowInterval;
}

Temperature Status::comfortTemperature() const
{
    return mComfortTemperature;
}

Temperature Status::ecoTemperature() const
{
    return mEcoTemperature;
}

TemperatureOffset Status::temperatureOffset() const
{
    return mTemperatureOffset;
}

QDebug operator<<(QDebug debug, const Status &status)
{
    QDebugStateSaver saver(debug);

    debug.nospace()
        << "statusFlags: " << status.statusFlags() << '\n'
        << "valvePosition: " << status.valvePosition() << '\n'
        << "unknownStatusByte: " << status.unknownStatusByte() << '\n'
        << "targetTemperature: " << status.targetTemperature() << '\n'
        << "holidayEndDateTime: " << status.holidayEndDateTime() << '\n'
        << "openWindowTemperature: " << status.openWindowTemperature() << '\n'
        << "openWindowInterval: " << status.openWindowInterval() << '\n'
        << "comfortTemperature: " << status.comfortTemperature() << '\n'
        << "ecoTemperature: " << status.ecoTemperature() << '\n'
        << "temperatureOffset: " << status.temperatureOffset();

    return debug;
}

} // namespace thermonator::eq3thermostat
