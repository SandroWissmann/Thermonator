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
    auto statusFlags = mStatusNotification.statusFlags();
    return statusFlags.autoModeEnabled();
}

bool Eq3Thermostat::manualModeEnabled() const
{
    auto statusFlags = mStatusNotification.statusFlags();
    return statusFlags.manualModeEnabled();
}

bool Eq3Thermostat::vacationModeEnabled() const
{
    auto statusFlags = mStatusNotification.statusFlags();
    return statusFlags.vacationModeEnabled();
}

bool Eq3Thermostat::boostEnabled() const
{
    auto statusFlags = mStatusNotification.statusFlags();
    return statusFlags.boostEnabled();
}

bool Eq3Thermostat::daylightSummerTimeEnabled() const
{
    auto statusFlags = mStatusNotification.statusFlags();
    return statusFlags.daylightSummerTimeEnabled();
}

bool Eq3Thermostat::openWindowModeEnabled() const
{
    auto statusFlags = mStatusNotification.statusFlags();
    return statusFlags.openWindowModeEnabled();
}

bool Eq3Thermostat::hardwareButtonsLocked() const
{
    auto statusFlags = mStatusNotification.statusFlags();
    return statusFlags.hardwareButtonsLocked();
}

bool Eq3Thermostat::unknownEnabled() const
{
    auto statusFlags = mStatusNotification.statusFlags();
    return statusFlags.hardwareButtonsLocked();
}

bool Eq3Thermostat::lowBatteryEnabled() const
{
    auto statusFlags = mStatusNotification.statusFlags();
    return statusFlags.lowBatteryEnabled();
}

int Eq3Thermostat::valvePosition() const
{
    auto valvePosition = mStatusNotification.valvePosition();
    return valvePosition.value();
}

int Eq3Thermostat::unknownStatusByte() const
{
    auto unknownStatusByte = mStatusNotification.unknownStatusByte();
    return unknownStatusByte.value();
}

double Eq3Thermostat::targetTemperature() const
{
    auto targetTemperature = mStatusNotification.targetTemperature();
    return targetTemperature.value();
}

int Eq3Thermostat::holidayEndDay() const
{
    auto holidayEndDateTime = mStatusNotification.holidayEndDateTime();
    return holidayEndDateTime.day();
}

int Eq3Thermostat::holidayEndMonth() const
{
    auto holidayEndDateTime = mStatusNotification.holidayEndDateTime();
    return holidayEndDateTime.month();
}

int Eq3Thermostat::holidayEndYear() const
{
    auto holidayEndDateTime = mStatusNotification.holidayEndDateTime();
    return holidayEndDateTime.year();
}

int Eq3Thermostat::holidayEndMinute() const
{
    auto holidayEndDateTime = mStatusNotification.holidayEndDateTime();
    return holidayEndDateTime.minute();
}

int Eq3Thermostat::holidayEndHour() const
{
    auto holidayEndDateTime = mStatusNotification.holidayEndDateTime();
    return holidayEndDateTime.hour();
}

double Eq3Thermostat::openWindowTemperature() const
{
    auto openWindowTemperature = mStatusNotification.openWindowTemperature();
    return openWindowTemperature.value();
}

int Eq3Thermostat::openWindowInterval() const
{
    auto openWindowInterval = mStatusNotification.openWindowInterval();
    return openWindowInterval.value();
}

double Eq3Thermostat::comfortTemperature() const
{
    auto comfortTemperature = mStatusNotification.comfortTemperature();
    return comfortTemperature.value();
}

double Eq3Thermostat::ecoTemperature() const
{
    auto ecoTemperature = mStatusNotification.ecoTemperature();
    return ecoTemperature.value();
}

double Eq3Thermostat::temperatureOffset() const
{
    auto temperatureOffset = mStatusNotification.temperatureOffset();
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

void Eq3Thermostat::onSetStatusNotification(
    const StatusNotification &statusNotification)
{
    qDebug() << Q_FUNC_INFO << "statusNotification:" << statusNotification;

    if (mStatusNotification == statusNotification) {
        return;
    }
    auto backupNotification = mStatusNotification;
    mStatusNotification = statusNotification;

    notifyChangesBaseStatusNotification(backupNotification,
                                        mStatusNotification);

    auto backupStatusFlags = backupNotification.statusFlags();
    auto statusFlags = mStatusNotification.statusFlags();

    notifyChangesInStatusFlags(backupStatusFlags, statusFlags);

    auto backupHolidayEndDateTime = backupNotification.holidayEndDateTime();
    auto holidayEndDateTime = mStatusNotification.holidayEndDateTime();

    notifyChangesInHolidayEndDateTime(backupHolidayEndDateTime,
                                      holidayEndDateTime);
}

void Eq3Thermostat::notifyChangesBaseStatusNotification(
    const StatusNotification &oldStatusNotification,
    const StatusNotification &newStatusNotification)
{
    if (oldStatusNotification.valvePosition() !=
        newStatusNotification.valvePosition()) {
        emit valvePositionChanged();
    }
    if (oldStatusNotification.unknownStatusByte() !=
        oldStatusNotification.unknownStatusByte()) {
        emit valvePositionChanged();
    }
    if (oldStatusNotification.targetTemperature() !=
        oldStatusNotification.targetTemperature()) {
        emit valvePositionChanged();
    }

    if (oldStatusNotification.openWindowTemperature() !=
        oldStatusNotification.openWindowTemperature()) {
        emit openWindowTemperatureChanged();
    }
    if (oldStatusNotification.openWindowInterval() !=
        oldStatusNotification.openWindowInterval()) {
        emit openWindowIntervalChanged();
    }
    if (oldStatusNotification.comfortTemperature() !=
        oldStatusNotification.comfortTemperature()) {
        emit comfortTemperatureChanged();
    }
    if (oldStatusNotification.ecoTemperature() !=
        oldStatusNotification.ecoTemperature()) {
        emit ecoTemperatureChanged();
    }
    if (oldStatusNotification.temperatureOffset() !=
        oldStatusNotification.temperatureOffset()) {
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

} // namespace thermonator::eq3thermostat
