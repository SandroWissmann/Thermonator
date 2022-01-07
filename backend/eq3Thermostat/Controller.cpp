#include "Controller.hpp"

#include "types/ConfigureComfortAndEcoTemperatureCommand.hpp"
#include "types/ConfigureOpenWindowModeCommand.hpp"
#include "types/DayTimer.hpp"
#include "types/GetDayTimerCommand.hpp"
#include "types/OpenWindowInterval.hpp"
#include "types/RequestSerialNumberCommand.hpp"
#include "types/SerialNumberNotificationData.hpp"
#include "types/SetBoostOffCommand.hpp"
#include "types/SetBoostOnCommand.hpp"
#include "types/SetComfortTemperatureCommand.hpp"
#include "types/SetCurrentDateTimeCommand.hpp"
#include "types/SetEcoTemperatureCommand.hpp"
#include "types/SetHardwareButtonsLockCommand.hpp"
#include "types/SetHardwareButtonsUnlockCommand.hpp"
#include "types/SetTemperatureCommand.hpp"
#include "types/SetTemperatureOffsetCommand.hpp"
#include "types/SetThermostatOffCommand.hpp"
#include "types/SetThermostatOnCommand.hpp"
#include "types/StatusNotificationData.hpp"
#include "types/TemperatureOffset.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

Controller::Controller(QObject *parent) : QObject{parent}
{
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

void Controller::setEcoTemperature()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetEcoTemperature;

    types::SetEcoTemperatureCommand setEcoTemperatureCommand;
    auto command = setEcoTemperatureCommand.encoded();
    emit sendCommand(command);
}

void Controller::setThermostatOn()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetThermostatOn;

    types::SetThermostatOnCommand setThermostatOnCommand;
    auto command = setThermostatOnCommand.encoded();
    emit sendCommand(command);
}

void Controller::setThermostatOff()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetThermostatOff;

    types::SetThermostatOffCommand setThermostatOffCommand;
    auto command = setThermostatOffCommand.encoded();
    emit sendCommand(command);
}

void Controller::setBoostOn()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetBoostOn;

    types::SetBoostOnCommand setBoostOnCommand;
    auto command = setBoostOnCommand.encoded();
    emit sendCommand(command);
}

void Controller::setBoostOff()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetBoostOff;

    types::SetBoostOffCommand setBoostOffCommand;
    auto command = setBoostOffCommand.encoded();
    emit sendCommand(command);
}

void Controller::setHardwareButtonsLock()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetHardwareButtonsLock;

    types::SetHardwareButtonsLockCommand setHardwareButtonsLockCommand;
    auto command = setHardwareButtonsLockCommand.encoded();
    emit sendCommand(command);
}

void Controller::setHardwareButtonsUnlock()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetHardwareButtonsUnlock;

    types::SetHardwareButtonsUnlockCommand setHardwareButtonsUnlockCommand;
    auto command = setHardwareButtonsUnlockCommand.encoded();
    emit sendCommand(command);
}

void Controller::configureOpenWindowMode(double openWindowTemperatureValue,
                                         int openWindowIntervalValue)
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::ConfigureOpenWindowMode;

    types::Temperature openWindowTemperature{openWindowTemperatureValue};
    types::OpenWindowInterval openWindowInterval{openWindowIntervalValue};
    types::ConfigureOpenWindowModeCommand configureOpenWindowModeCommand(
        openWindowTemperature, openWindowInterval);
    auto command = configureOpenWindowModeCommand.encoded();
    emit sendCommand(command);
}

void Controller::setTemperatureOffset(double value)
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetTemperatureOffset;

    types::TemperatureOffset temperatureOffset{value};
    types::SetTemperatureOffsetCommand setTemperatureOffsetCommand(
        temperatureOffset);
    auto command = setTemperatureOffsetCommand.encoded();
    emit sendCommand(command);
}

void Controller::getDayTimer(types::DayOfWeek dayOfWeek)
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::GetDayTimer;

    // assume here dayOfWeek is never invalid from caller site
    Q_ASSERT(dayOfWeek != types::DayOfWeek::invalid);

    types::GetDayTimerCommand getDayTimerCommand(dayOfWeek);
    auto command = getDayTimerCommand.encoded();
    emit sendCommand(command);
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
    case CommandType::SetEcoTemperature:
        [[fallthrough]];
    case CommandType::SetThermostatOn:
        [[fallthrough]];
    case CommandType::SetThermostatOff:
        [[fallthrough]];
    case CommandType::SetBoostOn:
        [[fallthrough]];
    case CommandType::SetBoostOff:
        [[fallthrough]];
    case CommandType::SetHardwareButtonsLock:
        [[fallthrough]];
    case CommandType::SetHardwareButtonsUnlock:
        [[fallthrough]];
    case CommandType::ConfigureOpenWindowMode:
        [[fallthrough]];
    case CommandType::SetTemperatureOffset:
        decodeAsStatusNotification(answer);
        break;
    case CommandType::GetDayTimer:
        decodeAsDayTimerNotification(answer);
        break;
    case CommandType::Unknown:
        qDebug() << Q_FUNC_INFO << "Unknown CommandType cannot decode";
        break;
    }
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

} // namespace thermonator::eq3thermostat
