#ifndef THERMONATOR_EQ3THERMOSTAT_CONTROLLER_HPP
#define THERMONATOR_EQ3THERMOSTAT_CONTROLLER_HPP

#include <QObject>

#include <memory>

namespace thermonator::eq3thermostat {

namespace command {
class SerialNumber;
class DateTime;
class Temperature;
class ComfortAndEcoTemperature;
class SwitchToComfortTemperature;
class SwitchToEcoTemperature;
class ThermostatOn;
class ThermostatOff;
class BoostOn;
class BoostOff;
class HardwareButtonsLock;
class HardwareButtonsUnlock;
class ConfigureOpenWindowMode;
class ConfigureOffsetTemperature;
} // namespace command

namespace answer {
class SerialNumberNotification;
class StatusNotification;
} // namespace answer

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    // Query serial number of thermostate
    Q_INVOKABLE
    void requestSerialNumber();

    // Set current date and time from system in the thermostate
    Q_INVOKABLE
    void setCurrentDateTime();

    // Temperature has to be in range 5.0 °C to 29.5 °C. Steps have to be in 0.5
    // °C. If value is out of range clamping to the next value is performed
    Q_INVOKABLE
    void setTemperature(double temperature);

    // Temperature has to be in range 5.0 °C to 29.5 °C. Steps have to be in 0.5
    // °C. If value is out of range clamping to the next value is performed
    Q_INVOKABLE
    void setComfortAndEcoTemperature(double comfortTemperature,
                                     double ecoTemperature);

    // Current temperature is changed to the comfort temperature saved in the
    // thermostate
    Q_INVOKABLE
    void switchToComfortTemperature();

    // Current temperature is changed to the eco temperature saved in the
    // thermostate
    Q_INVOKABLE
    void switchToEcoTemperature();

    // Turn on the thermostat. Sets also current target temperature to 29.5°C
    Q_INVOKABLE
    void thermostatOn();

    // Turn off the thermostat.
    Q_INVOKABLE
    void thermostatOff();

    // Turn on the temporary boost function on for 300 seconds.
    Q_INVOKABLE
    void boostOn();

    // Turn off the temporary boost function. Only does something if boost is
    // on.
    Q_INVOKABLE
    void boostOff();

    // Lock the hardware buttons
    Q_INVOKABLE
    void hardwareButtonsLock();

    // Unlock the hardware buttons
    Q_INVOKABLE
    void hardwareButtonsUnlock();

    // Set the values for open Window mode.
    // Temperature has to be in range 5.0 °C to 29.5 °C.
    // Steps have to be in 0.5 °C.
    // Intervall has to be in range 0 to 60 min.
    // Steps have to be in 5 min.
    // If value is out of range clamping to the next value is performed
    // If value is not exact in step clamping is performed aswell.
    Q_INVOKABLE
    void configureOpenWindowMode(double openWindowTemperature,
                                 int openWindowInterval);

    // Temperature has to be in range -3.5 °C to 3.5 °C. Steps have to be in 0.5
    // °C If value is out of range clamping to the next value is performed
    Q_INVOKABLE
    void configureOffsetTemperature(double offsetTemperature);

public slots:
    void onAnswerReceived(const QByteArray &answer);
signals:
    void commandRequested(const QByteArray &command);

    void serialNumberReceived(const QString &serialNumber);

    void temperatureOffsetReceived(double temperatureOffset);
    void ecoTemperatureReceived(double ecoTemperature);
    void comfortTemperatureReceived(double comfortTemperature);
    void openWindowIntervalReceived(int openWindowInterval);
    void openWindowTemperatureReceived(double openWindowTemperature);
    void minuteReceived(int minute);
    void hourReceived(int hour);
    void dayReceived(int day);
    void monthReceived(int month);
    void yearReceived(int year);
    void targetTemperatureReceived(double targetTemperature);
    void valvePositionReceived(int valvePosition);
    void autoModeEnabledReceived(bool autoModeEnabled);
    void manualModeEnabledReceived(bool manualModeEnabled);
    void vacationModeEnabledReceived(bool vacationModeEnabled);
    void boostEnabledReceived(bool boostEnabled);
    void daylightSummerTimeEnabledReceived(bool daylightSummerTimeEnabled);
    void openWindowModeEnabledReceived(bool openWindowModeEnabled);
    void hardwareButtonsLockedReceived(bool hardwareButtonsLocked);
    void unknownEnabledReceived(bool unknownEnabled);
    void lowBatteryEnabledReceived(bool lowBatteryEnabled);

private slots:
    void onSerialNumberAnswerDecoded(const QString &serialNumber);

    void onStatusAnswerDecoded(
        double temperatureOffset, double ecoTemperature,
        double comfortTemperature, int openWindowInterval,
        double openWindowTemperature, int minute, int hour, int day, int month,
        int year, double targetTemperature, int valvePosition,
        bool autoModeEnabled, bool manualModeEnabled, bool vacationModeEnabled,
        bool boostEnabled, bool daylightSummerTimeEnabled,
        bool openWindowModeEnabled, bool hardwareButtonsLocked,
        bool unknownEnabled, bool lowBatteryEnabled);

private:
    void initCommandSerialNumber();
    void initCommandDateTime();
    void initCommandTemperature();
    void initCommandComfortAndEcoTemperature();
    void initCommandSwitchToComfortTemperature();
    void initCommandSwitchToEcoTemperature();
    void initCommandThermostatOn();
    void initCommandThermostatOff();
    void initCommandBoostOn();
    void initCommandBoostOff();
    void initCommandHardwareButtonsLock();
    void initCommandHardwareButtonsUnlock();
    void initCommandConfigureOpenWindowMode();
    void initCommandConfigureOffsetTemperature();

    void initAnswerSerialNumberNotification();
    void initAnswerStatusNotification();

    double clampTemperature(double temperature);
    double clampOffsetTemperature(double offsetTemperature);
    int clampInterval(int interval);

    enum class CommandType {
        Unknown,
        SerialNumber,
        DateTime,
        Temperature,
        ComfortAndEcoTemperature,
        SwitchToComfortTemperature,
        SwitchToEcoTemperature,
        ThermostatOn,
        ThermostatOff,
        BoostOn,
        BoostOff,
        HardwareButtonsLock,
        HardwareButtonsUnlock,
        ConfigureOpenWindowMode,
        ConfigureOffsetTemperature
    };

    CommandType mLastCommandType{CommandType::Unknown};
    bool mWaitForAnswer{false};

    std::unique_ptr<command::SerialNumber> mCommandSerialNumber;
    std::unique_ptr<command::DateTime> mCommandDateTime;
    std::unique_ptr<command::Temperature> mCommandTemperature;
    std::unique_ptr<command::ComfortAndEcoTemperature>
        mCommandComfortAndEcoTemperature;
    std::unique_ptr<command::SwitchToComfortTemperature>
        mCommandSwitchToComfortTemperature;
    std::unique_ptr<command::SwitchToEcoTemperature>
        mCommandSwitchToEcoTemperature;
    std::unique_ptr<command::ThermostatOn> mCommandThermostatOn;
    std::unique_ptr<command::ThermostatOff> mCommandThermostatOff;
    std::unique_ptr<command::BoostOn> mCommandBoostOn;
    std::unique_ptr<command::BoostOff> mCommandBoostOff;
    std::unique_ptr<command::HardwareButtonsLock> mCommandHardwareButtonsLock;
    std::unique_ptr<command::HardwareButtonsUnlock>
        mCommandHardwareButtonsUnlock;
    std::unique_ptr<command::ConfigureOpenWindowMode>
        mCommandConfigureOpenWindowMode;
    std::unique_ptr<command::ConfigureOffsetTemperature>
        mCommandConfigureOffsetTemperature;

    std::unique_ptr<answer::SerialNumberNotification>
        mAnswerSerialNumberNotification;
    std::unique_ptr<answer::StatusNotification> mAnswerStatusNotification;
};

} // namespace thermonator::eq3thermostat

#endif
