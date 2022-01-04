#include "Controller.hpp"

#include "answer/SerialNumberNotification.hpp"
#include "command/BoostOff.hpp"
#include "command/BoostOn.hpp"
#include "command/ComfortAndEcoTemperature.hpp"
#include "command/ConfigureOffsetTemperature.hpp"
#include "command/ConfigureOpenWindowMode.hpp"
#include "command/DateTime.hpp"
#include "command/DayTimer.hpp"
#include "command/HardwareButtonsLock.hpp"
#include "command/HardwareButtonsUnlock.hpp"
#include "command/SerialNumber.hpp"
#include "command/SwitchToComfortTemperature.hpp"
#include "command/SwitchToEcoTemperature.hpp"
#include "command/Temperature.hpp"
#include "command/ThermostatOff.hpp"
#include "command/ThermostatOn.hpp"
#include "types/StatusNotificationData.hpp"

#include <QDebug>

#include <algorithm> // for std::clamp

namespace thermonator::eq3thermostat {

Controller::Controller(QObject *parent) : QObject{parent}
{
    initCommandSerialNumber();
    initCommandDateTime();
    initCommandTemperature();
    initCommandComfortAndEcoTemperature();
    initCommandSwitchToComfortTemperature();
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

    initAnswerSerialNumberNotification();
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
    mLastCommandType = CommandType::SerialNumber;
    mWaitForAnswer = true;
    mCommandSerialNumber->encodeCommand();
}

void Controller::setCurrentDateTime()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::DateTime;
    mWaitForAnswer = true;
    mCommandDateTime->encodeCommand();
}

void Controller::setTemperature(double temperature)
{
    qDebug() << Q_FUNC_INFO;
    temperature = clampTemperature(temperature);
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::Temperature;
    mWaitForAnswer = true;
    mCommandTemperature->encodeCommand(temperature);
}

void Controller::setComfortAndEcoTemperature(double comfortTemperature,
                                             double ecoTemperature)
{
    qDebug() << Q_FUNC_INFO;
    comfortTemperature = clampTemperature(comfortTemperature);
    ecoTemperature = clampTemperature(ecoTemperature);
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::ComfortAndEcoTemperature;
    mWaitForAnswer = true;
    mCommandComfortAndEcoTemperature->encodeCommand(comfortTemperature,
                                                    ecoTemperature);
}

void Controller::switchToComfortTemperature()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SwitchToComfortTemperature;
    mWaitForAnswer = true;
    mCommandSwitchToComfortTemperature->encodeCommand();
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
    mLastCommandType = CommandType::ComfortAndEcoTemperature;
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
    case CommandType::SerialNumber:
        qDebug() << Q_FUNC_INFO << "decode as SerialNumberNotification";
        mAnswerSerialNumberNotification->decodeAnswer(answer);
        break;
    case CommandType::DateTime:
        [[fallthrough]];
    case CommandType::Temperature:
        [[fallthrough]];
    case CommandType::ComfortAndEcoTemperature:
        [[fallthrough]];
    case CommandType::SwitchToComfortTemperature:
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
    case CommandType::ConfigureOffsetTemperature: {
        qDebug() << Q_FUNC_INFO << "decode as StatusNotificationData";
        auto statusNotificationData =
            types::StatusNotificationData::fromEncodedData(answer);

        if (!statusNotificationData.isValid()) {
            qDebug() << Q_FUNC_INFO << "statusNotificationData is invalid";
        }
        else {
            emit statusNotificationDataReceived(statusNotificationData);
        }
        break;
    }
    case CommandType::DayTimer: {
        qDebug() << Q_FUNC_INFO << "decode as DayTimerNotification";
        auto dayTimer = types::DayTimer::fromEncodedData(answer);

        if (!dayTimer.isValid()) {
            qDebug() << Q_FUNC_INFO << "dayTimer is invalid";
        }
        else {
            emit dayTimerReceived(dayTimer);
        }
        break;
    }
    case CommandType::Unknown:
        qDebug() << Q_FUNC_INFO << "Unknown CommandType cannot decode";
        break;
    }
}

void Controller::onSerialNumberAnswerDecoded(const QString &serialNumber)
{
    qDebug() << Q_FUNC_INFO;
    emit serialNumberReceived(serialNumber);
}

void Controller::initCommandSerialNumber()
{
    mCommandSerialNumber = std::make_unique<command::SerialNumber>(this);

    connect(mCommandSerialNumber.get(), &command::SerialNumber::commandEncoded,
            this, &Controller::commandRequested);
}

void Controller::initCommandDateTime()
{
    mCommandDateTime = std::make_unique<command::DateTime>(this);

    connect(mCommandDateTime.get(), &command::DateTime::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initCommandTemperature()
{
    mCommandTemperature = std::make_unique<command::Temperature>(this);

    connect(mCommandTemperature.get(), &command::Temperature::commandEncoded,
            this, &Controller::commandRequested);
}

void Controller::initCommandComfortAndEcoTemperature()
{
    mCommandComfortAndEcoTemperature =
        std::make_unique<command::ComfortAndEcoTemperature>(this);

    connect(mCommandComfortAndEcoTemperature.get(),
            &command::ComfortAndEcoTemperature::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initCommandSwitchToComfortTemperature()
{
    mCommandSwitchToComfortTemperature =
        std::make_unique<command::SwitchToComfortTemperature>(this);

    connect(mCommandSwitchToComfortTemperature.get(),
            &command::SwitchToComfortTemperature::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initCommandSwitchToEcoTemperature()
{
    mCommandSwitchToEcoTemperature =
        std::make_unique<command::SwitchToEcoTemperature>(this);

    connect(mCommandSwitchToEcoTemperature.get(),
            &command::SwitchToEcoTemperature::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initCommandThermostatOn()
{
    mCommandThermostatOn = std::make_unique<command::ThermostatOn>(this);

    connect(mCommandThermostatOn.get(), &command::ThermostatOn::commandEncoded,
            this, &Controller::commandRequested);
}

void Controller::initCommandThermostatOff()
{
    mCommandThermostatOff = std::make_unique<command::ThermostatOff>(this);

    connect(mCommandThermostatOff.get(),
            &command::ThermostatOff::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initCommandHardwareButtonsLock()
{
    mCommandHardwareButtonsLock =
        std::make_unique<command::HardwareButtonsLock>(this);

    connect(mCommandHardwareButtonsLock.get(),
            &command::HardwareButtonsLock::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initCommandHardwareButtonsUnlock()
{
    mCommandHardwareButtonsUnlock =
        std::make_unique<command::HardwareButtonsUnlock>(this);

    connect(mCommandHardwareButtonsUnlock.get(),
            &command::HardwareButtonsUnlock::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initCommandBoostOn()
{
    mCommandBoostOn = std::make_unique<command::BoostOn>(this);

    connect(mCommandBoostOn.get(), &command::BoostOn::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initCommandBoostOff()
{
    mCommandBoostOff = std::make_unique<command::BoostOff>(this);

    connect(mCommandBoostOff.get(), &command::BoostOff::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initCommandConfigureOpenWindowMode()
{
    mCommandConfigureOpenWindowMode =
        std::make_unique<command::ConfigureOpenWindowMode>(this);

    connect(mCommandConfigureOpenWindowMode.get(),
            &command::ConfigureOpenWindowMode::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initCommandConfigureOffsetTemperature()
{
    mCommandConfigureOffsetTemperature =
        std::make_unique<command::ConfigureOffsetTemperature>(this);

    connect(mCommandConfigureOffsetTemperature.get(),
            &command::ConfigureOffsetTemperature::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initCommandDayTimer()
{
    mCommandDayTimer = std::make_unique<command::DayTimer>(this);

    connect(mCommandDayTimer.get(), &command::DayTimer::commandEncoded, this,
            &Controller::commandRequested);
}

void Controller::initAnswerSerialNumberNotification()
{
    mAnswerSerialNumberNotification =
        std::make_unique<answer::SerialNumberNotification>(this);

    connect(mAnswerSerialNumberNotification.get(),
            &answer::SerialNumberNotification::answerDecoded, this,
            &Controller::onSerialNumberAnswerDecoded);
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
