#ifndef THERMONATOR_EQ3THERMOSTAT_EQ3THERMOSTAT_HPP
#define THERMONATOR_EQ3THERMOSTAT_EQ3THERMOSTAT_HPP

#include "notification/SerialNumberNotification.hpp"
#include "notification/StatusNotification.hpp"
#include "types/WeekTimer.hpp"

#include <QObject>
#include <QString>

namespace thermonator::eq3thermostat {

class Eq3Thermostat : public QObject {
    Q_OBJECT
    Q_PROPERTY(
        QString serialNumber READ serialNumber NOTIFY serialNumberChanged)

    Q_PROPERTY(bool autoModeEnabled READ autoModeEnabled NOTIFY
                   autoModeEnabledChanged);
    Q_PROPERTY(bool manualModeEnabled READ manualModeEnabled NOTIFY
                   manualModeEnabledChanged);
    Q_PROPERTY(bool vacationModeEnabled READ vacationModeEnabled NOTIFY
                   vacationModeEnabled);
    Q_PROPERTY(bool boostEnabled READ boostEnabled NOTIFY boostEnabledChanged);
    Q_PROPERTY(bool daylightSummerTimeEnabled READ daylightSummerTimeEnabled
                   NOTIFY daylightSummerTimeEnabledChanged);
    Q_PROPERTY(bool openWindowModeEnabled READ openWindowModeEnabled NOTIFY
                   openWindowModeEnabled);
    Q_PROPERTY(bool hardwareButtonsLocked READ hardwareButtonsLocked NOTIFY
                   hardwareButtonsLockedChanged);
    Q_PROPERTY(
        bool unknownEnabled READ unknownEnabled NOTIFY unknownEnabledChanged);
    Q_PROPERTY(bool lowBatteryEnabled READ lowBatteryEnabled NOTIFY
                   lowBatteryEnabledChanged);
    Q_PROPERTY(
        int valvePosition READ valvePosition NOTIFY valvePositionChanged);
    Q_PROPERTY(int unknownStatusByte READ unknownStatusByte NOTIFY
                   unknownStatusByteChanged);
    Q_PROPERTY(double targetTemperature READ targetTemperature NOTIFY
                   targetTemperatureChanged);
    Q_PROPERTY(
        int holidayEndDay READ holidayEndDay NOTIFY holidayEndDayChanged);
    Q_PROPERTY(
        int holidayEndMonth READ holidayEndMonth NOTIFY holidayEndMonthChanged);
    Q_PROPERTY(
        int holidayEndYear READ holidayEndYear NOTIFY holidayEndYearChanged);
    Q_PROPERTY(int holidayEndMinute READ holidayEndMinute NOTIFY
                   holidayEndMinuteChanged);
    Q_PROPERTY(
        int holidayEndHour READ holidayEndHour NOTIFY holidayEndHourChanged);
    Q_PROPERTY(double openWindowTemperature READ openWindowTemperature NOTIFY
                   openWindowTemperatureChanged);
    Q_PROPERTY(int openWindowInterval READ openWindowInterval NOTIFY
                   openWindowIntervalChanged);
    Q_PROPERTY(double comfortTemperature READ comfortTemperature NOTIFY
                   comfortTemperatureChanged);
    Q_PROPERTY(
        double ecoTemperature READ ecoTemperature NOTIFY ecoTemperatureChanged);
    Q_PROPERTY(double temperatureOffset READ temperatureOffset NOTIFY
                   temperatureOffsetChanged);

    // TODO: Week Timer should be presented exposed with WeekTimerModel to be
    // added later. Use QAbstractItemModel
    Q_PROPERTY(WeekTimer weekTimer READ weekTimer NOTIFY weekTimerChanged);

public:
    explicit Eq3Thermostat(QObject *parent = nullptr);

    ~Eq3Thermostat() = default;

    QString serialNumber() const;

    // from StatusNotificationData
    bool autoModeEnabled() const;
    bool manualModeEnabled() const;
    bool vacationModeEnabled() const;
    bool boostEnabled() const;
    bool daylightSummerTimeEnabled() const;
    bool openWindowModeEnabled() const;
    bool hardwareButtonsLocked() const;
    bool unknownEnabled() const;
    bool lowBatteryEnabled() const;
    int valvePosition() const;
    int unknownStatusByte() const;
    double targetTemperature() const;
    int holidayEndDay() const;
    int holidayEndMonth() const;
    int holidayEndYear() const;
    int holidayEndMinute() const;
    int holidayEndHour() const;
    double openWindowTemperature() const;
    int openWindowInterval() const;
    double comfortTemperature() const;
    double ecoTemperature() const;
    double temperatureOffset() const;

    WeekTimer weekTimer() const;

public slots:
    void onSetSerialNumberNotification(
        const thermonator::eq3thermostat::SerialNumberNotification
            &serialNumberNotification);

    void
    onSetStatusNotification(const thermonator::eq3thermostat::StatusNotification
                                &statusNotification);

    void notifyChangesBaseStatusNotification(
        const thermonator::eq3thermostat::StatusNotification
            &oldStatusNotification,
        const thermonator::eq3thermostat::StatusNotification
            &newStatusNotification);

    void notifyChangesInStatusFlags(
        const thermonator::eq3thermostat::StatusFlags &oldStatusFlags,
        const thermonator::eq3thermostat::StatusFlags &newStatusFlags);

    void notifyChangesInHolidayEndDateTime(
        const thermonator::eq3thermostat::DateTime &oldHolidayEndDateTime,
        const thermonator::eq3thermostat::DateTime &newHolidayEndDateTime);

    void onSetDayTimer(const thermonator::eq3thermostat::DayTimer &dayTimer);

signals:
    void serialNumberChanged();

    void autoModeEnabledChanged();
    void manualModeEnabledChanged();
    void vacationModeEnabledChanged();
    void boostEnabledChanged();
    void daylightSummerTimeEnabledChanged();
    void openWindowModeEnabledChanged();
    void hardwareButtonsLockedChanged();
    void unknownEnabledChanged();
    void lowBatteryEnabledChanged();
    void valvePositionChanged();
    void unknownStatusByteChanged();
    void targetTemperatureChanged();
    void holidayEndDayChanged();
    void holidayEndMonthChanged();
    void holidayEndYearChanged();
    void holidayEndMinuteChanged();
    void holidayEndHourChanged();
    void openWindowTemperatureChanged();
    void openWindowIntervalChanged();
    void comfortTemperatureChanged();
    void ecoTemperatureChanged();
    void temperatureOffsetChanged();

    void weekTimerChanged();

private:
    SerialNumberNotification mSerialNumberNotification;
    StatusNotification mStatusNotification;
    WeekTimer mWeekTimer;
};

} // namespace thermonator::eq3thermostat

#endif
