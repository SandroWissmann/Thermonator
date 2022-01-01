#ifndef THERMONATOR_EQ3THERMOSTAT_EQ3THERMOSTAT_HPP
#define THERMONATOR_EQ3THERMOSTAT_EQ3THERMOSTAT_HPP

#include "types/WeekTimer.hpp"

#include <QObject>
#include <QString>

namespace thermonator::eq3thermostat {

class Eq3Thermostat : public QObject {
    Q_OBJECT
    Q_PROPERTY(
        QString serialNumber READ serialNumber NOTIFY serialNumberChanged)

    Q_PROPERTY(double temperatureOffset READ temperatureOffset NOTIFY
                   temperatureOffsetChanged);
    Q_PROPERTY(
        double ecoTemperature READ ecoTemperature NOTIFY ecoTemperatureChanged);
    Q_PROPERTY(double comfortTemperature READ comfortTemperature NOTIFY
                   comfortTemperatureChanged);

    Q_PROPERTY(int openWindowInterval READ openWindowInterval NOTIFY
                   openWindowIntervalChanged);
    Q_PROPERTY(double openWindowTemperature READ openWindowTemperature NOTIFY
                   openWindowTemperatureChanged);
    Q_PROPERTY(int minute READ minute NOTIFY minuteChanged);
    Q_PROPERTY(int hour READ hour NOTIFY hourChanged);
    Q_PROPERTY(int day READ day NOTIFY dayChanged);
    Q_PROPERTY(int month READ month NOTIFY monthChanged);
    Q_PROPERTY(int year READ year NOTIFY yearChanged);

    Q_PROPERTY(double targetTemperature READ targetTemperature NOTIFY
                   targetTemperatureChanged);
    Q_PROPERTY(
        int valvePosition READ valvePosition NOTIFY valvePositionChanged);
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

    // TODO: Week Timer should be presented exposed with WeekTimerModel to be
    // added later. Use QAbstractItemModel
    Q_PROPERTY(
        types::WeekTimer weekTimer READ weekTimer NOTIFY weekTimerChanged);

public:
    explicit Eq3Thermostat(QObject *parent = nullptr);

    ~Eq3Thermostat() = default;

    QString serialNumber() const;

    double temperatureOffset() const;
    double ecoTemperature() const;
    double comfortTemperature() const;
    int openWindowInterval() const;
    double openWindowTemperature() const;
    int minute() const;
    int hour() const;
    int day() const;
    int month() const;
    int year() const;
    double targetTemperature() const;
    int valvePosition() const;
    bool autoModeEnabled() const;
    bool manualModeEnabled() const;
    bool vacationModeEnabled() const;
    bool boostEnabled() const;
    bool daylightSummerTimeEnabled() const;
    bool openWindowModeEnabled() const;
    bool hardwareButtonsLocked() const;
    bool unknownEnabled() const;
    bool lowBatteryEnabled() const;

    types::WeekTimer weekTimer() const;

public slots:
    void onSetSerialNumber(const QString &serialNumber);

    void onSetTemperatureOffset(double temperatureOffset);
    void onSetEcoTemperature(double ecoTemperature);
    void onSetComfortTemperature(double comfortTemperature);
    void onSetOpenWindowInterval(int openWindowInterval);
    void onSetOpenWindowTemperature(double openWindowTemperature);
    void onSetMinute(int minute);
    void onSetHour(int hour);
    void onSetDay(int day);
    void onSetMonth(int month);
    void onSetYear(int year);
    void onSetTargetTemperature(double targetTemperature);
    void onSetValvePosition(int valvePosition);
    void onSetAutoModeEnabled(bool autoModeEnabled);
    void onSetManualModeEnabled(bool manualModeEnabled);
    void onSetVacationModeEnabled(bool vacationModeEnabled);
    void onSetBoostEnabled(bool boostEnabled);
    void onSetDaylightSummerTimeEnabled(bool daylightSummerTimeEnabled);
    void onSetOpenWindowModeEnabled(bool openWindowModeEnabled);
    void onSetHardwareButtonsLocked(bool hardwareButtonsLocked);
    void onSetUnknownEnabled(bool unknownEnabled);
    void onSetLowBatteryEnabled(bool lowBatteryEnabled);

    void onSetDayTimer(types::DayOfWeek dayOfWeek,
                       const types::DayTimer &dayTimer);

signals:
    void serialNumberChanged();

    void temperatureOffsetChanged();
    void ecoTemperatureChanged();
    void comfortTemperatureChanged();
    void openWindowIntervalChanged();
    void openWindowTemperatureChanged();
    void minuteChanged();
    void hourChanged();
    void dayChanged();
    void monthChanged();
    void yearChanged();
    void targetTemperatureChanged();
    void valvePositionChanged();
    void autoModeEnabledChanged();
    void manualModeEnabledChanged();
    void vacationModeEnabledChanged();
    void boostEnabledChanged();
    void daylightSummerTimeEnabledChanged();
    void openWindowModeEnabledChanged();
    void hardwareButtonsLockedChanged();
    void unknownEnabledChanged();
    void lowBatteryEnabledChanged();

    void weekTimerChanged();

private:
    QString mSerialNumber;

    double mTemperatureOffset{0.0};
    double mEcoTemperature{0.0};
    double mComfortTemperature{0.0};
    int mOpenWindowInterval{0};
    double mOpenWindowTemperature{0.0};
    int mMinute{0};
    int mHour{0};
    int mDay{0};
    int mMonth{0};
    int mYear{0};
    double mTargetTemperature{0.0};
    int mValvePosition{0};
    bool mAutoModeEnabled{false};
    bool mManualModeEnabled{false};
    bool mVacationModeEnabled{false};
    bool mBoostEnabled{false};
    bool mDaylightSummerTimeEnabled{false};
    bool mOpenWindowModeEnabled{false};
    bool mHardwareButtonsLocked{false};
    bool mUnknownEnabled{false};
    bool mLowBatteryEnabled{false};

    types::WeekTimer mWeekTimer;
};

} // namespace thermonator::eq3thermostat

#endif
