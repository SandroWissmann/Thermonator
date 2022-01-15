#include "Controller.hpp"

#include "command/ConfigureComfortAndEcoTemperatureCommand.hpp"
#include "command/ConfigureOpenWindowModeCommand.hpp"
#include "command/GetDayTimerCommand.hpp"
#include "command/GetSerialNumberCommand.hpp"
#include "command/SetBoostOffCommand.hpp"
#include "command/SetBoostOnCommand.hpp"
#include "command/SetComfortTemperatureCommand.hpp"
#include "command/SetCurrentDateTimeCommand.hpp"
#include "command/SetDayTimerCommand.hpp"
#include "command/SetEcoTemperatureCommand.hpp"
#include "command/SetHardwareButtonsLockCommand.hpp"
#include "command/SetHardwareButtonsUnlockCommand.hpp"
#include "command/SetTemperatureCommand.hpp"
#include "command/SetTemperatureOffsetCommand.hpp"
#include "command/SetThermostatOffCommand.hpp"
#include "command/SetThermostatOnCommand.hpp"
#include "notification/GetDayTimerNotification.hpp"
#include "notification/SerialNumberNotification.hpp"
#include "notification/StatusNotification.hpp"
#include "types/DayTimer.hpp"
#include "types/OpenWindowInterval.hpp"
#include "types/TemperatureOffset.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

Controller::Controller(QObject *parent) : QObject{parent}
{
}

// declaration has to be in cpp to make std::unique_ptr member forward
// declaration work
Controller::~Controller() = default;

void Controller::getSerialNumber()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::GetSerialNumber;

    GetSerialNumberCommand requestSerialNumberCommand;
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

    SetCurrentDateTimeCommand setCurrentDateTimeCommand;
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

    Temperature temperature{value};
    SetTemperatureCommand setTemperatureCommand(temperature);
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

    Temperature comfortTemperature{comfortValue};
    Temperature ecoTemperature{ecoValue};
    ConfigureComfortAndEcoTemperatureCommand
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

    SetComfortTemperatureCommand setComfortTemperatureCommand;
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

    SetEcoTemperatureCommand setEcoTemperatureCommand;
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

    SetThermostatOnCommand setThermostatOnCommand;
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

    SetThermostatOffCommand setThermostatOffCommand;
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

    SetBoostOnCommand setBoostOnCommand;
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

    SetBoostOffCommand setBoostOffCommand;
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

    SetHardwareButtonsLockCommand setHardwareButtonsLockCommand;
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

    SetHardwareButtonsUnlockCommand setHardwareButtonsUnlockCommand;
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

    Temperature openWindowTemperature{openWindowTemperatureValue};
    OpenWindowInterval openWindowInterval{openWindowIntervalValue};
    ConfigureOpenWindowModeCommand configureOpenWindowModeCommand(
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

    TemperatureOffset temperatureOffset{value};
    SetTemperatureOffsetCommand setTemperatureOffsetCommand(temperatureOffset);
    auto command = setTemperatureOffsetCommand.encoded();
    emit sendCommand(command);
}

void Controller::getDayTimer(DayOfWeek dayOfWeek)
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::GetDayTimer;

    // assume here dayOfWeek is never invalid from caller site
    Q_ASSERT(dayOfWeek != DayOfWeek::invalid);

    GetDayTimerCommand getDayTimerCommand(dayOfWeek);
    auto command = getDayTimerCommand.encoded();
    emit sendCommand(command);
}

void Controller::setDayTimer(DayOfWeek dayOfWeek,
                             const DayTimerEntries &dayTimerEntries)
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
        qDebug() << Q_FUNC_INFO << "Command already in progress";
        return;
    }
    mLastCommandType = CommandType::SetDayTimer;

    // assume here dayOfWeek is never invalid from caller site
    Q_ASSERT(dayOfWeek != DayOfWeek::invalid);
    // assume here dayTimerEntries is never invalid from caller site
    Q_ASSERT(dayTimerEntries.isValid());

    SetDayTimerCommand setDayTimerCommand(dayOfWeek, dayTimerEntries);
    auto command = setDayTimerCommand.encoded();
    emit sendCommand(command);
}

void Controller::onAnswerReceived(const QByteArray &answer)
{
    mWaitForAnswer = false;
    qDebug() << Q_FUNC_INFO;
    switch (mLastCommandType) {
    case CommandType::GetSerialNumber:
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
        decodeAsGetDayTimerNotification(answer);
        break;
    case CommandType::SetDayTimer:
        // not yet supported add SetDayTimerNotification here
        break;
    case CommandType::Unknown:
        qDebug() << Q_FUNC_INFO << "Unknown CommandType cannot decode";
        break;
    }
}

void Controller::decodeAsSerialNumberNotification(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO;
    auto serialNumberNotification =
        SerialNumberNotification::fromEncodedData(answer);

    if (!serialNumberNotification.isValid()) {
        qDebug() << Q_FUNC_INFO << "serialNumberNotification is invalid";
        return;
    }
    auto serialNumber = serialNumberNotification.serialNumber();
    emit serialNumberReceived(serialNumber);
}

void Controller::decodeAsStatusNotification(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO;
    auto statusNotification = StatusNotification::fromEncodedData(answer);

    if (!statusNotification.isValid()) {
        qDebug() << Q_FUNC_INFO << "statusNotification is invalid";
        return;
    }
    auto status = statusNotification.status();
    emit statusReceived(status);
}

void Controller::decodeAsGetDayTimerNotification(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO;
    auto getDayTimerNotification =
        GetDayTimerNotification::fromEncodedData(answer);

    if (!getDayTimerNotification.isValid()) {
        qDebug() << Q_FUNC_INFO << "DayTimerNotification is invalid";
        return;
    }
    auto dayTimer = getDayTimerNotification.dayTimer();
    emit dayTimerReceived(dayTimer);
}

} // namespace thermonator::eq3thermostat
