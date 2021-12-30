#include "Controller.hpp"

#include "answer/SerialNumberNotification.hpp"
#include "answer/StatusNotification.hpp"
#include "command/DateTime.hpp"
#include "command/SerialNumber.hpp"
#include "command/Temperature.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

Controller::Controller(QObject *parent) : QObject{parent}
{
    mCommandSerialNumber = std::make_unique<command::SerialNumber>(this);

    connect(mCommandSerialNumber.get(), &command::SerialNumber::commandEncoded,
            this, &Controller::commandRequested);

    mCommandDateTime = std::make_unique<command::DateTime>(this);

    connect(mCommandDateTime.get(), &command::DateTime::commandEncoded, this,
            &Controller::commandRequested);

    mCommandTemperature = std::make_unique<command::Temperature>(this);

    connect(mCommandTemperature.get(), &command::Temperature::commandEncoded,
            this, &Controller::commandRequested);

    mAnswerSerialNumberNotification =
        std::make_unique<answer::SerialNumberNotification>(this);

    connect(mAnswerSerialNumberNotification.get(),
            &answer::SerialNumberNotification::answerDecoded, this,
            &Controller::onSerialNumberAnswerDecoded);

    mAnswerStatusNotification =
        std::make_unique<answer::StatusNotification>(this);

    connect(mAnswerStatusNotification.get(),
            &answer::StatusNotification::answerDecoded, this,
            &Controller::onStatusAnswerDecoded);
}

// declaration has to be in cpp to make std::unique_ptr member forward
// declaration work
Controller::~Controller() = default;

void Controller::requestSerialNumber()
{
    qDebug() << Q_FUNC_INFO;
    if (mWaitForAnswer) {
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
        return;
    }
    mLastCommandType = CommandType::Temperature;
    mWaitForAnswer = true;
    mCommandTemperature->encodeCommand(temperature);
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
        qDebug() << Q_FUNC_INFO << "decode as StatusNotification";
        mAnswerStatusNotification->decodeAnswer(answer);
        break;
    case CommandType::Temperature:
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

} // namespace thermonator::eq3thermostat
