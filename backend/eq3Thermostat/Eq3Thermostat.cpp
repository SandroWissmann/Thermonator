#include "Eq3Thermostat.hpp"

#include "../utility/EnumToString.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

Eq3Thermostat::Eq3Thermostat(QObject *parent)
{
}

QString Eq3Thermostat::serialNumber() const
{
    auto serialNumber = mSerialNumberNotificationData.serialNumber();
    return serialNumber.value();
}

bool Eq3Thermostat::autoModeEnabled() const
{
    auto statusFlags = mStatusNotificationData.statusFlags();
    return statusFlags.autoModeEnabled();
}

bool Eq3Thermostat::manualModeEnabled() const
{
    auto statusFlags = mStatusNotificationData.statusFlags();
    return statusFlags.manualModeEnabled();
}

bool Eq3Thermostat::vacationModeEnabled() const
{
    auto statusFlags = mStatusNotificationData.statusFlags();
    return statusFlags.vacationModeEnabled();
}

bool Eq3Thermostat::boostEnabled() const
{
    auto statusFlags = mStatusNotificationData.statusFlags();
    return statusFlags.boostEnabled();
}

bool Eq3Thermostat::daylightSummerTimeEnabled() const
{
    auto statusFlags = mStatusNotificationData.statusFlags();
    return statusFlags.daylightSummerTimeEnabled();
}

bool Eq3Thermostat::openWindowModeEnabled() const
{
    auto statusFlags = mStatusNotificationData.statusFlags();
    return statusFlags.openWindowModeEnabled();
}

bool Eq3Thermostat::hardwareButtonsLocked() const
{
    auto statusFlags = mStatusNotificationData.statusFlags();
    return statusFlags.hardwareButtonsLocked();
}

bool Eq3Thermostat::unknownEnabled() const
{
    auto statusFlags = mStatusNotificationData.statusFlags();
    return statusFlags.hardwareButtonsLocked();
}

bool Eq3Thermostat::lowBatteryEnabled() const
{
    auto statusFlags = mStatusNotificationData.statusFlags();
    return statusFlags.lowBatteryEnabled();
}

int Eq3Thermostat::valvePosition() const
{
    auto valvePosition = mStatusNotificationData.valvePosition();
    return valvePosition.value();
}

int Eq3Thermostat::unknownStatusByte() const
{
    auto unknownStatusByte = mStatusNotificationData.unknownStatusByte();
    return unknownStatusByte.value();
}

double Eq3Thermostat::targetTemperature() const
{
    auto targetTemperature = mStatusNotificationData.targetTemperature();
    return targetTemperature.value();
}

int Eq3Thermostat::holidayEndDay() const
{
    auto holidayEndDateTime = mStatusNotificationData.holidayEndDateTime();
    return holidayEndDateTime.day();
}

int Eq3Thermostat::holidayEndMonth() const
{
    auto holidayEndDateTime = mStatusNotificationData.holidayEndDateTime();
    return holidayEndDateTime.month();
}

int Eq3Thermostat::holidayEndYear() const
{
    auto holidayEndDateTime = mStatusNotificationData.holidayEndDateTime();
    return holidayEndDateTime.year();
}

int Eq3Thermostat::holidayEndMinute() const
{
    auto holidayEndDateTime = mStatusNotificationData.holidayEndDateTime();
    return holidayEndDateTime.minute();
}

int Eq3Thermostat::holidayEndHour() const
{
    auto holidayEndDateTime = mStatusNotificationData.holidayEndDateTime();
    return holidayEndDateTime.hour();
}

double Eq3Thermostat::openWindowTemperature() const
{
    auto openWindowTemperature =
        mStatusNotificationData.openWindowTemperature();
    return openWindowTemperature.value();
}

int Eq3Thermostat::openWindowInterval() const
{
    auto openWindowInterval = mStatusNotificationData.openWindowInterval();
    return openWindowInterval.value();
}

double Eq3Thermostat::comfortTemperature() const
{
    auto comfortTemperature = mStatusNotificationData.comfortTemperature();
    return comfortTemperature.value();
}

double Eq3Thermostat::ecoTemperature() const
{
    auto ecoTemperature = mStatusNotificationData.ecoTemperature();
    return ecoTemperature.value();
}

double Eq3Thermostat::temperatureOffset() const
{
    auto temperatureOffset = mStatusNotificationData.temperatureOffset();
    return temperatureOffset.value();
}

types::WeekTimer Eq3Thermostat::weekTimer() const
{
    return mWeekTimer;
}

void Eq3Thermostat::onSetSerialNumberNotificationData(
    const types::SerialNumberNotificationData &serialNumberNotificationData)
{
    qDebug() << Q_FUNC_INFO
             << "serialNumberNotificationData:" << serialNumberNotificationData;
    if (mSerialNumberNotificationData == serialNumberNotificationData) {
        return;
    }
    auto backuoSerialNumberNotification = mSerialNumberNotificationData;
    mSerialNumberNotificationData = serialNumberNotificationData;

    if (backuoSerialNumberNotification.serialNumber() !=
        mSerialNumberNotificationData.serialNumber()) {
        emit serialNumberChanged();
    }
}

void Eq3Thermostat::onSetStatusNotificationData(
    const types::StatusNotificationData &statusNotificationData)
{
    qDebug() << Q_FUNC_INFO
             << "statusNotificationData:" << statusNotificationData;

    if (mStatusNotificationData == statusNotificationData) {
        return;
    }
    auto backupNotificationData = mStatusNotificationData;
    mStatusNotificationData = statusNotificationData;

    notifyChangesBaseStatusNotificationData(backupNotificationData,
                                            mStatusNotificationData);

    auto backupStatusFlags = backupNotificationData.statusFlags();
    auto statusFlags = mStatusNotificationData.statusFlags();

    notifyChangesInStatusFlags(backupStatusFlags, statusFlags);

    auto backupHolidayEndDateTime = backupNotificationData.holidayEndDateTime();
    auto holidayEndDateTime = mStatusNotificationData.holidayEndDateTime();

    notifyChangesInHolidayEndDateTime(backupHolidayEndDateTime,
                                      holidayEndDateTime);
}

void Eq3Thermostat::notifyChangesBaseStatusNotificationData(
    const types::StatusNotificationData &oldStatusNotificationData,
    const types::StatusNotificationData &newStatusNotificationData)
{
    if (oldStatusNotificationData.valvePosition() !=
        newStatusNotificationData.valvePosition()) {
        emit valvePositionChanged();
    }
    if (oldStatusNotificationData.unknownStatusByte() !=
        newStatusNotificationData.unknownStatusByte()) {
        emit valvePositionChanged();
    }
    if (oldStatusNotificationData.targetTemperature() !=
        newStatusNotificationData.targetTemperature()) {
        emit valvePositionChanged();
    }

    if (oldStatusNotificationData.openWindowTemperature() !=
        newStatusNotificationData.openWindowTemperature()) {
        emit openWindowTemperatureChanged();
    }
    if (oldStatusNotificationData.openWindowInterval() !=
        newStatusNotificationData.openWindowInterval()) {
        emit openWindowIntervalChanged();
    }
    if (oldStatusNotificationData.comfortTemperature() !=
        newStatusNotificationData.comfortTemperature()) {
        emit comfortTemperatureChanged();
    }
    if (oldStatusNotificationData.ecoTemperature() !=
        newStatusNotificationData.ecoTemperature()) {
        emit ecoTemperatureChanged();
    }
    if (oldStatusNotificationData.temperatureOffset() !=
        newStatusNotificationData.temperatureOffset()) {
        emit temperatureOffsetChanged();
    }
}

void Eq3Thermostat::notifyChangesInStatusFlags(
    const types::StatusFlags &oldStatusFlags,
    const types::StatusFlags &newStatusFlags)
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
    const types::DateTime &oldHolidayEndDateTime,
    const types::DateTime &newHolidayEndDateTime)
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

void Eq3Thermostat::onSetDayTimer(const types::DayTimer &dayTimer)
{
    auto dayOfWeek = dayTimer.dayOfWeek();
    qDebug() << Q_FUNC_INFO << "dayOfWeek:" << utility::enumToString(dayOfWeek);
    qDebug() << Q_FUNC_INFO << "dayTimer:" << dayTimer;

    if (mWeekTimer.dayTimer(dayOfWeek) == dayTimer) {
        return;
    }
    mWeekTimer.setDayTimer(dayTimer);
    emit weekTimerChanged();
}

} // namespace thermonator::eq3thermostat
