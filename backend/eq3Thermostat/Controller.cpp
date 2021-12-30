#include "Controller.hpp"

#include "answer/SerialNumberNotification.hpp"
#include "answer/StatusNotification.hpp"
#include "command/ComfortAndEcoTemperature.hpp"
#include "command/DateTime.hpp"
#include "command/SerialNumber.hpp"
#include "command/SwitchToComfortTemperature.hpp"
#include "command/Temperature.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

Controller::Controller(QObject *parent) : QObject{parent}
{
    initCommandSerialNumber();
    initCommandDateTime();
    initCommandTemperature();
    initCommandComfortAndEcoTemperature();
    initCommandSwitchToComfortTemperature();
    initAnswerSerialNumberNotification();
    initAnswerStatusNotification();
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
        qDebug() << Q_FUNC_INFO << "decode as StatusNotification";
        mAnswerStatusNotification->decodeAnswer(answer);
        break;
    case CommandType::Unknown:
        qDebug() << Q_FUNC_INFO << "CommandType::Unknown";
        break;
    }
}

void Controller::onSerialNumberAnswerDecoded(const QString &serialNumber)
{
    qDebug() << Q_FUNC_INFO;
    emit serialNumberReceived(serialNumber);
}

void Controller::onStatusAnswerDecoded(
    double temperatureOffset, double ecoTemperature, double comfortTemperature,
    int openWindowInterval, double openWindowTemperature, int minute, int hour,
    int day, int month, int year, double targetTemperature, int valvePosition,
    bool autoModeEnabled, bool manualModeEnabled, bool vacationModeEnabled,
    bool boostEnabled, bool daylightSummerTimeEnabled,
    bool openWindowModeEnabled, bool hardwareButtonsLocked, bool unknownEnabled,
    bool lowBatteryEnabled)
{
    qDebug() << Q_FUNC_INFO;

    emit temperatureOffsetReceived(temperatureOffset);
    emit ecoTemperatureReceived(ecoTemperature);
    emit comfortTemperatureReceived(comfortTemperature);
    emit openWindowIntervalReceived(openWindowInterval);
    emit openWindowTemperatureReceived(openWindowTemperature);
    emit minuteReceived(minute);
    emit hourReceived(hour);
    emit dayReceived(day);
    emit monthReceived(month);
    emit yearReceived(year);
    emit targetTemperatureReceived(targetTemperature);
    emit valvePositionReceived(valvePosition);
    emit autoModeEnabledReceived(autoModeEnabled);
    emit manualModeEnabledReceived(manualModeEnabled);
    emit vacationModeEnabledReceived(vacationModeEnabled);
    emit boostEnabledReceived(boostEnabled);
    emit daylightSummerTimeEnabledReceived(daylightSummerTimeEnabled);
    emit openWindowModeEnabledReceived(openWindowModeEnabled);
    emit hardwareButtonsLockedReceived(hardwareButtonsLocked);
    emit unknownEnabledReceived(unknownEnabled);
    emit lowBatteryEnabledReceived(lowBatteryEnabled);
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

void Controller::initAnswerSerialNumberNotification()
{
    mAnswerSerialNumberNotification =
        std::make_unique<answer::SerialNumberNotification>(this);

    connect(mAnswerSerialNumberNotification.get(),
            &answer::SerialNumberNotification::answerDecoded, this,
            &Controller::onSerialNumberAnswerDecoded);
}

void Controller::initAnswerStatusNotification()
{
    mAnswerStatusNotification =
        std::make_unique<answer::StatusNotification>(this);

    connect(mAnswerStatusNotification.get(),
            &answer::StatusNotification::answerDecoded, this,
            &Controller::onStatusAnswerDecoded);
}

} // namespace thermonator::eq3thermostat
