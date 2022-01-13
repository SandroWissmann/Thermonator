#ifndef THERMONATOR_EQ3THERMOSTAT_CONTROLLER_HPP
#define THERMONATOR_EQ3THERMOSTAT_CONTROLLER_HPP

#include "types/DayOfWeek.hpp"

#include <QObject>

#include <memory>

namespace thermonator::eq3thermostat {

class SerialNumberNotification;
class StatusNotification;
class DayTimer;
class DayTimerEntries;

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    // Query serial number of thermostate
    Q_INVOKABLE
    void getSerialNumber();

    // Set current date and time from system in the thermostate
    Q_INVOKABLE
    void setCurrentDateTime();

    // set the current temperature
    // Temperature has to be in range 5.0 °C to 29.5 °C. Steps have to be in 0.5
    // °C. If value is out of range clamping to the next value is performed
    Q_INVOKABLE
    void setTemperature(double value);

    // configure the comfort and eco temperature
    // Temperature has to be in range 5.0 °C to 29.5 °C. Steps have to be in 0.5
    // °C. If value is out of range clamping to the next value is performed
    Q_INVOKABLE
    void configureComfortAndEcoTemperature(double comfortValue,
                                           double ecoValue);

    // Current temperature is changed to the comfort temperature saved in the
    // thermostate
    Q_INVOKABLE
    void setComfortTemperature();

    // Current temperature is changed to the eco temperature saved in the
    // thermostate
    Q_INVOKABLE
    void setEcoTemperature();

    // Turn on the thermostat. Sets also current target temperature to 29.5°C
    Q_INVOKABLE
    void setThermostatOn();

    // Turn off the thermostat.
    Q_INVOKABLE
    void setThermostatOff();

    // Turn on the temporary boost function on for 300 seconds.
    Q_INVOKABLE
    void setBoostOn();

    // Turn off the temporary boost function. Only does something if boost is
    // on.
    Q_INVOKABLE
    void setBoostOff();

    // Lock the hardware buttons
    Q_INVOKABLE
    void setHardwareButtonsLock();

    // Unlock the hardware buttons
    Q_INVOKABLE
    void setHardwareButtonsUnlock();

    // Set the values for open Window mode.
    // Temperature has to be in range 5.0 °C to 29.5 °C.
    // Steps have to be in 0.5 °C.
    // Intervall has to be in range 0 to 60 min.
    // Steps have to be in 5 min.
    // If value is out of range clamping to the next value is performed
    // If value is not exact in step clamping is performed aswell.
    Q_INVOKABLE
    void configureOpenWindowMode(double openWindowTemperatureValue,
                                 int openWindowIntervalValue);

    // Temperature offset has to be in range -3.5 °C to 3.5 °C. Steps have to be
    // in 0.5 °C. If value is out of range clamping to the next value is
    // performed
    Q_INVOKABLE
    void setTemperatureOffset(double temperatureOffset);

    // Should later be better handle via AbstractItemModel
    Q_INVOKABLE
    void getDayTimer(DayOfWeek dayOfWeek);

    // Should later be better handle via AbstractItemModel
    Q_INVOKABLE
    void setDayTimer(DayOfWeek dayOfWeek,
                     const DayTimerEntries &dayTimerEntries);

public slots:
    void onAnswerReceived(const QByteArray &answer);
signals:
    void sendCommand(const QByteArray &command);

    void serialNumberNotificationReceived(
        const thermonator::eq3thermostat::SerialNumberNotification
            &serialNumberNotification);

    void statusNotificationReceived(
        const thermonator::eq3thermostat::StatusNotification
            &statusNotification);

    void dayTimerReceived(const thermonator::eq3thermostat::DayTimer &dayTimer);

private:
    void decodeAsSerialNumberNotification(const QByteArray &answer);
    void decodeAsStatusNotification(const QByteArray &answer);
    void decodeAsGetDayTimerNotification(const QByteArray &answer);

    enum class CommandType {
        Unknown,
        GetSerialNumber,
        SetCurrentDateTime,
        SetTemperature,
        ConfigureComfortAndEcoTemperature,
        SetComfortTemperature,
        SetEcoTemperature,
        SetThermostatOn,
        SetThermostatOff,
        SetBoostOn,
        SetBoostOff,
        SetHardwareButtonsLock,
        SetHardwareButtonsUnlock,
        ConfigureOpenWindowMode,
        SetTemperatureOffset,
        GetDayTimer,
        SetDayTimer
    };

    CommandType mLastCommandType{CommandType::Unknown};

    // we should move this into io service and create a queue there which
    // "stacks" commands in a queue. probally we should also tell it which
    // command type we are sending. Or create a queue class inbetween ?
    bool mWaitForAnswer{false};
};

} // namespace thermonator::eq3thermostat

#endif
