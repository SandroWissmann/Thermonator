#ifndef THERMONATOR_EQ3THERMOSTAT_CONTROLLER_HPP
#define THERMONATOR_EQ3THERMOSTAT_CONTROLLER_HPP

#include <QObject>

#include <memory>

namespace thermonator::eq3thermostat {

namespace command {
class SerialNumber;
class DateTime;
} // namespace command

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    Q_INVOKABLE
    void requestSerialNumber();

    Q_INVOKABLE
    void setCurrentDateTime();

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
    void onSerialNumberCommandEncoded(const QByteArray &command);
    void onSerialNumberAnswerDecoded(const QString &serialNumber);

    void onDateTimeCommandEncoded(const QByteArray &command);
    void onDateTimeAnswerDecoded(
        double temperatureOffset, double ecoTemperature,
        double comfortTemperature, int openWindowInterval,
        double openWindowTemperature, int minute, int hour, int day, int month,
        int year, double targetTemperature, int valvePosition,
        bool autoModeEnabled, bool manualModeEnabled, bool vacationModeEnabled,
        bool boostEnabled, bool daylightSummerTimeEnabled,
        bool openWindowModeEnabled, bool hardwareButtonsLocked,
        bool unknownEnabled, bool lowBatteryEnabled);

private:
    enum class CommandType { Unknown, SerialNumber, DateTime };

    CommandType mLastCommandType{CommandType::Unknown};

    std::unique_ptr<command::SerialNumber> mCommandSerialNumber;
    std::unique_ptr<command::DateTime> mCommandDateTime;
};

} // namespace thermonator::eq3thermostat

#endif
