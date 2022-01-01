#include "Eq3Thermostat.hpp"

#include "../utility/EnumToString.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

Eq3Thermostat::Eq3Thermostat(QObject *parent)
{
}

QString Eq3Thermostat::serialNumber() const
{
    return mSerialNumber;
}

double Eq3Thermostat::temperatureOffset() const
{
    return mTemperatureOffset;
}

double Eq3Thermostat::ecoTemperature() const
{
    return mEcoTemperature;
}

double Eq3Thermostat::comfortTemperature() const
{
    return mComfortTemperature;
}

int Eq3Thermostat::openWindowInterval() const
{
    return mOpenWindowInterval;
}

double Eq3Thermostat::openWindowTemperature() const
{
    return mOpenWindowTemperature;
}

int Eq3Thermostat::minute() const
{
    return mMinute;
}

int Eq3Thermostat::hour() const
{
    return mHour;
}

int Eq3Thermostat::day() const
{
    return mDay;
}

int Eq3Thermostat::month() const
{
    return mMonth;
}

int Eq3Thermostat::year() const
{
    return mYear;
}

double Eq3Thermostat::targetTemperature() const
{
    return mTargetTemperature;
}

int Eq3Thermostat::valvePosition() const
{
    return mValvePosition;
}

bool Eq3Thermostat::autoModeEnabled() const
{
    return mAutoModeEnabled;
}

bool Eq3Thermostat::manualModeEnabled() const
{
    return mManualModeEnabled;
}

bool Eq3Thermostat::vacationModeEnabled() const
{
    return mVacationModeEnabled;
}

bool Eq3Thermostat::boostEnabled() const
{
    return mBoostEnabled;
}

bool Eq3Thermostat::daylightSummerTimeEnabled() const
{
    return mDaylightSummerTimeEnabled;
}

bool Eq3Thermostat::openWindowModeEnabled() const
{
    return mOpenWindowModeEnabled;
}

bool Eq3Thermostat::hardwareButtonsLocked() const
{
    return mHardwareButtonsLocked;
}

bool Eq3Thermostat::unknownEnabled() const
{
    return mHardwareButtonsLocked;
}

bool Eq3Thermostat::lowBatteryEnabled() const
{
    return mLowBatteryEnabled;
}

types::WeekTimer Eq3Thermostat::weekTimer() const
{
    return mWeekTimer;
}

void Eq3Thermostat::onSetSerialNumber(const QString &serialNumber)
{
    qDebug() << Q_FUNC_INFO << "serialNumber:" << serialNumber;
    if (mSerialNumber == serialNumber) {
        return;
    }
    mSerialNumber = serialNumber;
    emit serialNumberChanged();
}

void Eq3Thermostat::onSetTemperatureOffset(double temperatureOffset)
{
    qDebug() << Q_FUNC_INFO << "temperatureOffset:" << temperatureOffset;
    if (mTemperatureOffset == temperatureOffset) {
        return;
    }
    mTemperatureOffset = temperatureOffset;
    emit temperatureOffsetChanged();
}

void Eq3Thermostat::onSetEcoTemperature(double ecoTemperature)
{
    qDebug() << Q_FUNC_INFO << "ecoTemperature:" << ecoTemperature;
    if (mEcoTemperature == ecoTemperature) {
        return;
    }
    mEcoTemperature = ecoTemperature;
    emit ecoTemperatureChanged();
}

void Eq3Thermostat::onSetComfortTemperature(double comfortTemperature)
{
    qDebug() << Q_FUNC_INFO << "comfortTemperature:" << comfortTemperature;
    if (mComfortTemperature == comfortTemperature) {
        return;
    }
    mComfortTemperature = comfortTemperature;
    emit comfortTemperatureChanged();
}

void Eq3Thermostat::onSetOpenWindowInterval(int openWindowInterval)
{
    qDebug() << Q_FUNC_INFO << "openWindowInterval:" << openWindowInterval;
    if (mOpenWindowInterval == openWindowInterval) {
        return;
    }
    mOpenWindowInterval = openWindowInterval;
    emit openWindowIntervalChanged();
}

void Eq3Thermostat::onSetOpenWindowTemperature(double openWindowTemperature)
{
    qDebug() << Q_FUNC_INFO
             << "openWindowTemperature:" << openWindowTemperature;
    if (mOpenWindowTemperature == openWindowTemperature) {
        return;
    }
    mOpenWindowTemperature = openWindowTemperature;
    emit openWindowTemperatureChanged();
}

void Eq3Thermostat::onSetMinute(int minute)
{
    qDebug() << Q_FUNC_INFO << "minute:" << minute;
    if (mMinute == minute) {
        return;
    }
    mMinute = minute;
    emit minuteChanged();
}

void Eq3Thermostat::onSetHour(int hour)
{
    qDebug() << Q_FUNC_INFO << "hour:" << hour;
    if (mHour == hour) {
        return;
    }
    mHour = hour;
    emit hourChanged();
}

void Eq3Thermostat::onSetDay(int day)
{
    qDebug() << Q_FUNC_INFO << "day:" << day;
    if (mDay == day) {
        return;
    }
    mDay = day;
    emit dayChanged();
}

void Eq3Thermostat::onSetMonth(int month)
{
    qDebug() << Q_FUNC_INFO << "month:" << month;
    if (mMonth == month) {
        return;
    }
    mMonth = month;
    emit monthChanged();
}

void Eq3Thermostat::onSetYear(int year)
{
    qDebug() << Q_FUNC_INFO << "year:" << year;
    if (mYear == year) {
        return;
    }
    mYear = year;
    emit yearChanged();
}

void Eq3Thermostat::onSetTargetTemperature(double targetTemperature)
{
    qDebug() << Q_FUNC_INFO << "targetTemperature:" << targetTemperature;
    if (mTargetTemperature == targetTemperature) {
        return;
    }
    mTargetTemperature = targetTemperature;
    emit targetTemperatureChanged();
}

void Eq3Thermostat::onSetValvePosition(int valvePosition)
{
    qDebug() << Q_FUNC_INFO << "valvePosition:" << valvePosition;
    if (mValvePosition == valvePosition) {
        return;
    }
    mValvePosition = valvePosition;
    emit valvePositionChanged();
}

void Eq3Thermostat::onSetAutoModeEnabled(bool autoModeEnabled)
{
    qDebug() << Q_FUNC_INFO << "autoModeEnabled:" << autoModeEnabled;
    if (mAutoModeEnabled == autoModeEnabled) {
        return;
    }
    mAutoModeEnabled = autoModeEnabled;
    emit autoModeEnabledChanged();
}

void Eq3Thermostat::onSetManualModeEnabled(bool manualModeEnabled)
{
    qDebug() << Q_FUNC_INFO << "manualModeEnabled:" << manualModeEnabled;
    if (mManualModeEnabled == manualModeEnabled) {
        return;
    }
    mManualModeEnabled = manualModeEnabled;
    emit manualModeEnabledChanged();
}

void Eq3Thermostat::onSetVacationModeEnabled(bool vacationModeEnabled)
{
    qDebug() << Q_FUNC_INFO << "vacationModeEnabled:" << vacationModeEnabled;
    if (mVacationModeEnabled == vacationModeEnabled) {
        return;
    }
    mVacationModeEnabled = vacationModeEnabled;
    emit vacationModeEnabledChanged();
}

void Eq3Thermostat::onSetBoostEnabled(bool boostEnabled)
{
    qDebug() << Q_FUNC_INFO << "boostEnabled:" << boostEnabled;
    if (mBoostEnabled == boostEnabled) {
        return;
    }
    mBoostEnabled = boostEnabled;
    emit boostEnabledChanged();
}

void Eq3Thermostat::onSetDaylightSummerTimeEnabled(
    bool daylightSummerTimeEnabled)
{
    qDebug() << Q_FUNC_INFO
             << "daylightSummerTimeEnabled:" << daylightSummerTimeEnabled;
    if (mDaylightSummerTimeEnabled == daylightSummerTimeEnabled) {
        return;
    }
    mDaylightSummerTimeEnabled = daylightSummerTimeEnabled;
    emit daylightSummerTimeEnabledChanged();
}

void Eq3Thermostat::onSetOpenWindowModeEnabled(bool openWindowModeEnabled)
{
    qDebug() << Q_FUNC_INFO
             << "openWindowModeEnabled:" << openWindowModeEnabled;
    if (mOpenWindowModeEnabled == openWindowModeEnabled) {
        return;
    }
    mOpenWindowModeEnabled = openWindowModeEnabled;
    emit openWindowModeEnabledChanged();
}

void Eq3Thermostat::onSetHardwareButtonsLocked(bool hardwareButtonsLocked)
{
    qDebug() << Q_FUNC_INFO
             << "hardwareButtonsLocked:" << hardwareButtonsLocked;
    if (mHardwareButtonsLocked == hardwareButtonsLocked) {
        return;
    }
    mHardwareButtonsLocked = hardwareButtonsLocked;
    emit hardwareButtonsLockedChanged();
}

void Eq3Thermostat::onSetUnknownEnabled(bool unknownEnabled)
{
    qDebug() << Q_FUNC_INFO << "unknownEnabled:" << unknownEnabled;
    if (mUnknownEnabled == unknownEnabled) {
        return;
    }
    mUnknownEnabled = unknownEnabled;
    emit unknownEnabledChanged();
}

void Eq3Thermostat::onSetLowBatteryEnabled(bool lowBatteryEnabled)
{
    qDebug() << Q_FUNC_INFO << "lowBatteryEnabled:" << lowBatteryEnabled;
    if (mLowBatteryEnabled == lowBatteryEnabled) {
        return;
    }
    mLowBatteryEnabled = lowBatteryEnabled;
    emit lowBatteryEnabledChanged();
}

void Eq3Thermostat::onSetDayTimer(types::DayOfWeek dayOfWeek,
                                  const types::DayTimer &dayTimer)
{
    qDebug() << Q_FUNC_INFO << "dayOfWeek:" << utility::enumToString(dayOfWeek);
    qDebug() << Q_FUNC_INFO << "dayTimer:" << dayTimer;

    if (mWeekTimer.dayTimer(dayOfWeek) == dayTimer) {
        return;
    }
    mWeekTimer.setDayTimer(dayOfWeek, dayTimer);
    emit weekTimerChanged();
}

} // namespace thermonator::eq3thermostat
