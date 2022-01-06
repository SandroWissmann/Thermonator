#include "Controller.hpp"

#include "command/BoostOff.hpp"
#include "command/BoostOn.hpp"
#include "command/ConfigureOffsetTemperature.hpp"
#include "command/ConfigureOpenWindowMode.hpp"
#include "command/DateTime.hpp"
#include "command/DayTimer.hpp"
#include "command/HardwareButtonsLock.hpp"
#include "command/HardwareButtonsUnlock.hpp"
#include "command/SwitchToEcoTemperature.hpp"
#include "command/ThermostatOff.hpp"
#include "command/ThermostatOn.hpp"
#include "types/ConfigureComfortAndEcoTemperatureCommand.hpp"
#include "types/DayTimer.hpp"
#include "types/RequestSerialNumberCommand.hpp"
#include "types/SerialNumberNotificationData.hpp"
#include "types/SetComfortTemperatureCommand.hpp"
#include "types/SetCurrentDateTimeCommand.hpp"
#include "types/SetTemperatureCommand.hpp"
#include "types/StatusNotificationData.hpp"

#include <QDebug>

#include <algorithm> // for std::clamp

namespace thermonator::eq3thermostat {

Controller::Controller(QObject *parent) : QObject{parent}
{
    initCommandSwitchToEcoTemperature();
    initCommandThermostatOn();
    initCommandThermostatOff();
    initCommandBoostOn();
    initCommandBoostOff();
    initCommandHardwareButtonsLock();
    initCommandHardwareButtonsUnlock();
    initCommandConfigureOpenWindowMode();
    initCommandConfigureOffsetTemperature();
    initCommandDayTimer();
}

// declaration has to be in cpp to make std::unique_ptr member forward
// declaration work
Controller::~Controller() = default;

void Controller::requestSerialNumber()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::RequestSerialNumber;

    types::RequestSerialNumberCommand requestSerialNumberCommand;
    auto command = requestSerialNumberCommand.encoded();
    emit sendCommand(command);
}

void Controller::setCurrentDateTime()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetCurrentDateTime;

    types::SetCurrentDateTimeCommand setCurrentDateTimeCommand;
    auto command = setCurrentDateTimeCommand.encoded();
    emit sendCommand(command);
}

void Controller::setTemperature(double value)
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetTemperature;

    types::Temperature temperature{value};
    types::SetTemperatureCommand setTemperatureCommand(temperature);
    auto command = setTemperatureCommand.encoded();
    emit sendCommand(command);
}

void Controller::configureComfortAndEcoTemperature(double comfortValue,
                                                   double ecoValue)
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::ConfigureComfortAndEcoTemperature;

    types::Temperature comfortTemperature{comfortValue};
    types::Temperature ecoTemperature{ecoValue};
    types::ConfigureComfortAndEcoTemperatureCommand
        configureComfortAndEcoTemperatureCommand(comfortTemperature,
                                                 ecoTemperature);
    auto command = configureComfortAndEcoTemperatureCommand.encoded();
    emit sendCommand(command);
}

void Controller::setComfortTemperature()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetComfortTemperature;

    types::SetComfortTemperatureCommand setComfortTemperatureCommand;
    auto command = setComfortTemperatureCommand.encoded();
    emit sendCommand(command);
}

void Controller::switchToEcoTemperature()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SwitchToEcoTemperature;
    mWaitForAnswer = true;
    mCommandSwitchToEcoTemperature->encodeCommand();
}

void Controller::thermostatOn()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::ThermostatOn;
    mWaitForAnswer = true;
    mCommandThermostatOn->encodeCommand();
}

void Controller::thermostatOff()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::ThermostatOff;
    mWaitForAnswer = true;
    mCommandThermostatOff->encodeCommand();
}

void Controller::boostOn()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::BoostOn;
    mWaitForAnswer = true;
    mCommandBoostOn->encodeCommand();
}

void Controller::boostOff()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::BoostOff;
    mWaitForAnswer = true;
    mCommandBoostOff->encodeCommand();
}

void Controller::hardwareButtonsLock()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::HardwareButtonsLock;
    mWaitForAnswer = true;
    mCommandHardwareButtonsLock->encodeCommand();
}

void Controller::hardwareButtonsUnlock()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::HardwareButtonsUnlock;
    mWaitForAnswer = true;
    mCommandHardwareButtonsUnlock->encodeCommand();
}

void Controller::configureOpenWindowMode(double openWindowTemperature,
                                         int openWindowInterval)
{
    qDebug() << Q_FUNC_INFO;
    openWindowTemperature = clampTemperature(openWindowTemperature);
    openWindowInterval = clampInterval(openWindowInterval);
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::ConfigureOpenWindowMode;
    mWaitForAnswer = true;
    mCommandConfigureOpenWindowMode->encodeCommand(openWindowTemperature,
                                                   openWindowInterval);
}

void Controller::configureOffsetTemperature(double offsetTemperature)
{
    qDebug() << Q_FUNC_INFO;
    offsetTemperature = clampOffsetTemperature(offsetTemperature);
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::ConfigureOffsetTemperature;
    mWaitForAnswer = true;
    mCommandConfigureOffsetTemperature->encodeCommand(offsetTemperature);
}

void Controller::requestDayTimer(types::DayOfWeek dayOfWeek)
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::DayTimer;
    mWaitForAnswer = true;
    mCommandDayTimer->encodeCommand(dayOfWeek);
}

void Controller::onAnswerReceived(const QByteArray &answer)
{
    mWaitForAnswer = false;
    qDebug() << Q_FUNC_INFO;
    switch (mLastCommandType) {
    case CommandType::RequestSerialNumber:
        decodeAsSerialNumberNotification(answer);
        break;
    case CommandType::SetCurrentDateTime:
        [[fallthrough]];
    case CommandType::SetTemperature:
        [[fallthrough]];
    case CommandType::ConfigureComfortAndEcoTemperature:
        [[fallthrough]];
    case CommandType::SetComfortTemperature:
        [[fallthrough]];
    case CommandType::SwitchToEcoTemperature:
        [[fallthrough]];
    case CommandType::ThermostatOn:
        [[fallthrough]];
    case CommandType::ThermostatOff:
        [[fallthrough]];
    case CommandType::BoostOn:
        [[fallthrough]];
    case CommandType::BoostOff:
        [[fallthrough]];
    case CommandType::HardwareButtonsLock:
        [[fallthrough]];
    case CommandType::HardwareButtonsUnlock:
        [[fallthrough]];
    case CommandType::ConfigureOpenWindowMode:
        [[fallthrough]];
    case CommandType::ConfigureOffsetTemperature:
        decodeAsStatusNotification(answer);
        break;
    case CommandType::DayTimer:
        decodeAsDayTimerNotification(answer);
        break;
    case CommandType::Unknown:
        qDebug() << Q_FUNC_INFO << "Unknown CommandType cannot decode";
        break;
    }
}

void Controller::initCommandSwitchToEcoTemperature()
{
    mCommandSwitchToEcoTemperature =
        std::make_unique<command::SwitchToEcoTemperature>(this);

    connect(mCommandSwitchToEcoTemperature.get(),
            &command::SwitchToEcoTemperature::commandEncoded, this,
            &Controller::sendCommand);
}

void Controller::initCommandThermostatOn()
{
    mCommandThermostatOn = std::make_unique<command::ThermostatOn>(this);

    connect(mCommandThermostatOn.get(), &command::ThermostatOn::commandEncoded,
            this, &Controller::sendCommand);
}

void Controller::initCommandThermostatOff()
{
    mCommandThermostatOff = std::make_unique<command::ThermostatOff>(this);

    connect(mCommandThermostatOff.get(),
            &command::ThermostatOff::commandEncoded, this,
            &Controller::sendCommand);
}

void Controller::initCommandHardwareButtonsLock()
{
    mCommandHardwareButtonsLock =
        std::make_unique<command::HardwareButtonsLock>(this);

    connect(mCommandHardwareButtonsLock.get(),
            &command::HardwareButtonsLock::commandEncoded, this,
            &Controller::sendCommand);
}

void Controller::initCommandHardwareButtonsUnlock()
{
    mCommandHardwareButtonsUnlock =
        std::make_unique<command::HardwareButtonsUnlock>(this);

    connect(mCommandHardwareButtonsUnlock.get(),
            &command::HardwareButtonsUnlock::commandEncoded, this,
            &Controller::sendCommand);
}

void Controller::initCommandBoostOn()
{
    mCommandBoostOn = std::make_unique<command::BoostOn>(this);

    connect(mCommandBoostOn.get(), &command::BoostOn::commandEncoded, this,
            &Controller::sendCommand);
}

void Controller::initCommandBoostOff()
{
    mCommandBoostOff = std::make_unique<command::BoostOff>(this);

    connect(mCommandBoostOff.get(), &command::BoostOff::commandEncoded, this,
            &Controller::sendCommand);
}

void Controller::initCommandConfigureOpenWindowMode()
{
    mCommandConfigureOpenWindowMode =
        std::make_unique<command::ConfigureOpenWindowMode>(this);

    connect(mCommandConfigureOpenWindowMode.get(),
            &command::ConfigureOpenWindowMode::commandEncoded, this,
            &Controller::sendCommand);
}

void Controller::initCommandConfigureOffsetTemperature()
{
    mCommandConfigureOffsetTemperature =
        std::make_unique<command::ConfigureOffsetTemperature>(this);

    connect(mCommandConfigureOffsetTemperature.get(),
            &command::ConfigureOffsetTemperature::commandEncoded, this,
            &Controller::sendCommand);
}

void Controller::initCommandDayTimer()
{
    mCommandDayTimer = std::make_unique<command::DayTimer>(this);

    connect(mCommandDayTimer.get(), &command::DayTimer::commandEncoded, this,
            &Controller::sendCommand);
}

void Controller::decodeAsSerialNumberNotification(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO;
    auto serialNumberNotificationData =
        types::SerialNumberNotificationData::fromEncodedData(answer);

    if (!serialNumberNotificationData.isValid()) {
        qDebug() << Q_FUNC_INFO << "statusNotificationData is invalid";
        return;
    }
    emit serialNumberNotificationDataReceived(serialNumberNotificationData);
}

void Controller::decodeAsStatusNotification(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO;
    auto statusNotificationData =
        types::StatusNotificationData::fromEncodedData(answer);

    if (!statusNotificationData.isValid()) {
        qDebug() << Q_FUNC_INFO << "statusNotificationData is invalid";
        return;
    }
    emit statusNotificationDataReceived(statusNotificationData);
}

void Controller::decodeAsDayTimerNotification(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO << "decode as DayTimerNotification";
    auto dayTimer = types::DayTimer::fromEncodedData(answer);

    if (!dayTimer.isValid()) {
        qDebug() << Q_FUNC_INFO << "dayTimer is invalid";
        return;
    }
    emit dayTimerReceived(dayTimer);
}

double Controller::clampTemperature(double temperature)
{
    constexpr auto minTemperature = 5.0;
    constexpr auto maxTemperature = 29.5;
    temperature = std::clamp(temperature, minTemperature, maxTemperature);
    return temperature;
}

double Controller::clampOffsetTemperature(double offsetTemperature)
{
    constexpr auto minOffsetTemperature = -3.5;
    constexpr auto maxOffsetTemperature = 3.5;
    offsetTemperature = std::clamp(offsetTemperature, minOffsetTemperature,
                                   maxOffsetTemperature);
    return offsetTemperature;
}

int Controller::clampInterval(int interval)
{
    constexpr auto minInterval = 0;
    constexpr auto maxInterval = 60;
    interval = std::clamp(interval, minInterval, maxInterval);
    return interval;
}

} // namespace thermonator::eq3thermostat
