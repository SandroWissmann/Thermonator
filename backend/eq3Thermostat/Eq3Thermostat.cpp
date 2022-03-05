#include "Eq3Thermostat.hpp"

#include "../utility/EnumToString.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

Eq3Thermostat::Eq3Thermostat(QObject *parent)
{
}

QString Eq3Thermostat::serialNumber() const
{
    return mSerialNumber.value();
}

bool Eq3Thermostat::autoModeEnabled() const
{
    auto statusFlags = mStatus.statusFlags();
    return statusFlags.autoModeEnabled();
}

bool Eq3Thermostat::manualModeEnabled() const
{
    auto statusFlags = mStatus.statusFlags();
    return statusFlags.manualModeEnabled();
}

bool Eq3Thermostat::vacationModeEnabled() const
{
    auto statusFlags = mStatus.statusFlags();
    return statusFlags.vacationModeEnabled();
}

bool Eq3Thermostat::boostEnabled() const
{
    auto statusFlags = mStatus.statusFlags();
    return statusFlags.boostEnabled();
}

bool Eq3Thermostat::daylightSummerTimeEnabled() const
{
    auto statusFlags = mStatus.statusFlags();
    return statusFlags.daylightSummerTimeEnabled();
}

bool Eq3Thermostat::openWindowModeEnabled() const
{
    auto statusFlags = mStatus.statusFlags();
    return statusFlags.openWindowModeEnabled();
}

bool Eq3Thermostat::hardwareButtonsLocked() const
{
    auto statusFlags = mStatus.statusFlags();
    return statusFlags.hardwareButtonsLocked();
}

bool Eq3Thermostat::unknownEnabled() const
{
    auto statusFlags = mStatus.statusFlags();
    return statusFlags.hardwareButtonsLocked();
}

bool Eq3Thermostat::lowBatteryEnabled() const
{
    auto statusFlags = mStatus.statusFlags();
    return statusFlags.lowBatteryEnabled();
}

int Eq3Thermostat::valvePosition() const
{
    auto valvePosition = mStatus.valvePosition();
    return valvePosition.value();
}

int Eq3Thermostat::unknownStatusByte() const
{
    auto unknownStatusByte = mStatus.unknownStatusByte();
    return unknownStatusByte.value();
}

double Eq3Thermostat::targetTemperature() const
{
    auto targetTemperature = mStatus.targetTemperature();
    return targetTemperature.value();
}

int Eq3Thermostat::holidayEndDay() const
{
    auto holidayEndDateTime = mStatus.holidayEndDateTime();
    return holidayEndDateTime.day();
}

int Eq3Thermostat::holidayEndMonth() const
{
    auto holidayEndDateTime = mStatus.holidayEndDateTime();
    return holidayEndDateTime.month();
}

int Eq3Thermostat::holidayEndYear() const
{
    auto holidayEndDateTime = mStatus.holidayEndDateTime();
    return holidayEndDateTime.year();
}

int Eq3Thermostat::holidayEndMinute() const
{
    auto holidayEndDateTime = mStatus.holidayEndDateTime();
    return holidayEndDateTime.minute();
}

int Eq3Thermostat::holidayEndHour() const
{
    auto holidayEndDateTime = mStatus.holidayEndDateTime();
    return holidayEndDateTime.hour();
}

double Eq3Thermostat::openWindowTemperature() const
{
    auto openWindowTemperature = mStatus.openWindowTemperature();
    return openWindowTemperature.value();
}

int Eq3Thermostat::openWindowInterval() const
{
    auto openWindowInterval = mStatus.openWindowInterval();
    return openWindowInterval.value();
}

double Eq3Thermostat::comfortTemperature() const
{
    auto comfortTemperature = mStatus.comfortTemperature();
    return comfortTemperature.value();
}

double Eq3Thermostat::ecoTemperature() const
{
    auto ecoTemperature = mStatus.ecoTemperature();
    return ecoTemperature.value();
}

double Eq3Thermostat::temperatureOffset() const
{
    auto temperatureOffset = mStatus.temperatureOffset();
    return temperatureOffset.value();
}

WeekTimer Eq3Thermostat::weekTimer() const
{
    return mWeekTimer;
}

void Eq3Thermostat::onSetSerialNumber(const SerialNumber &serialNumber)
{
    qDebug() << Q_FUNC_INFO << "serialNumber:" << serialNumber;
    if (mSerialNumber == serialNumber) {
        return;
    }
    auto backupSerialNumber = mSerialNumber;
    mSerialNumber = serialNumber;

    if (backupSerialNumber != mSerialNumber) {
        emit serialNumberChanged();
    }
}

void Eq3Thermostat::onSetStatus(const Status &status)
{
    qDebug() << Q_FUNC_INFO << "status:" << status;

    if (mStatus == status) {
        return;
    }
    auto backupStatus = mStatus;
    mStatus = status;

    notifyChangesInBaseStatus(backupStatus, mStatus);

    auto backupStatusFlags = backupStatus.statusFlags();
    auto statusFlags = mStatus.statusFlags();

    notifyChangesInStatusFlags(backupStatusFlags, statusFlags);

    auto backupHolidayEndDateTime = backupStatus.holidayEndDateTime();
    auto holidayEndDateTime = mStatus.holidayEndDateTime();

    notifyChangesInHolidayEndDateTime(backupHolidayEndDateTime,
                                      holidayEndDateTime);
}

void Eq3Thermostat::onSetDayTimer(const DayTimer &dayTimer)
{
    qDebug() << Q_FUNC_INFO << "dayTimer:" << dayTimer;

    auto dayOfWeek = dayTimer.dayOfWeek();
    if (mWeekTimer.dayTimer(dayOfWeek) == dayTimer) {
        return;
    }
    mWeekTimer.setDayTimer(dayTimer);
    emit weekTimerChanged();
}

void Eq3Thermostat::notifyChangesInBaseStatus(const Status &oldStatus,
                                              const Status &newStatus)
{
    if (oldStatus.valvePosition() != newStatus.valvePosition()) {
        emit valvePositionChanged();
    }
    if (oldStatus.unknownStatusByte() != oldStatus.unknownStatusByte()) {
        emit valvePositionChanged();
    }
    if (oldStatus.targetTemperature() != oldStatus.targetTemperature()) {
        emit valvePositionChanged();
    }
    if (oldStatus.openWindowTemperature() !=
        oldStatus.openWindowTemperature()) {
        emit openWindowTemperatureChanged();
    }
    if (oldStatus.openWindowInterval() != oldStatus.openWindowInterval()) {
        emit openWindowIntervalChanged();
    }
    if (oldStatus.comfortTemperature() != oldStatus.comfortTemperature()) {
        emit comfortTemperatureChanged();
    }
    if (oldStatus.ecoTemperature() != oldStatus.ecoTemperature()) {
        emit ecoTemperatureChanged();
    }
    if (oldStatus.temperatureOffset() != oldStatus.temperatureOffset()) {
        emit temperatureOffsetChanged();
    }
}

void Eq3Thermostat::notifyChangesInStatusFlags(
    const StatusFlags &oldStatusFlags, const StatusFlags &newStatusFlags)
{
    if (oldStatusFlags == newStatusFlags) {
        return;
    }
    if (oldStatusFlags.autoModeEnabled() != newStatusFlags.autoModeEnabled()) {
        emit autoModeEnabledChanged();
        emit manualModeEnabledChanged();
    }
    if (oldStatusFlags.vacationModeEnabled() !=
        newStatusFlags.vacationModeEnabled()) {
        emit vacationModeEnabledChanged();
    }
    if (oldStatusFlags.boostEnabled() != newStatusFlags.boostEnabled()) {
        emit boostEnabledChanged();
    }
    if (oldStatusFlags.daylightSummerTimeEnabled() !=
        newStatusFlags.daylightSummerTimeEnabled()) {
        emit daylightSummerTimeEnabledChanged();
    }
    if (oldStatusFlags.openWindowModeEnabled() !=
        newStatusFlags.openWindowModeEnabled()) {
        emit openWindowModeEnabledChanged();
    }
    if (oldStatusFlags.hardwareButtonsLocked() !=
        newStatusFlags.hardwareButtonsLocked()) {
        emit hardwareButtonsLockedChanged();
    }
    if (oldStatusFlags.unknownEnabled() != newStatusFlags.unknownEnabled()) {
        emit unknownEnabledChanged();
    }
    if (oldStatusFlags.lowBatteryEnabled() !=
        newStatusFlags.lowBatteryEnabled()) {
        emit lowBatteryEnabledChanged();
    }
}

void Eq3Thermostat::notifyChangesInHolidayEndDateTime(
    const DateTime &oldHolidayEndDateTime,
    const DateTime &newHolidayEndDateTime)
{
    if (oldHolidayEndDateTime == newHolidayEndDateTime) {
        return;
    }
    if (oldHolidayEndDateTime.year() != newHolidayEndDateTime.year()) {
        emit holidayEndYearChanged();
    }
    if (oldHolidayEndDateTime.month() != newHolidayEndDateTime.month()) {
        emit holidayEndMonthChanged();
    }
    if (oldHolidayEndDateTime.day() != newHolidayEndDateTime.day()) {
        emit holidayEndDayChanged();
    }
    if (oldHolidayEndDateTime.hour() != newHolidayEndDateTime.hour()) {
        emit holidayEndHourChanged();
    }
    if (oldHolidayEndDateTime.minute() != newHolidayEndDateTime.minute()) {
        emit holidayEndMinuteChanged();
    }
}

} // namespace thermonator::eq3thermostat
