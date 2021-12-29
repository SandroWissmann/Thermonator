#include "Controller.hpp"

#include "command/DateTime.hpp"
#include "command/SerialNumber.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

Controller::Controller(QObject *parent) : QObject{parent}
{
    mCommandSerialNumber = std::make_unique<command::SerialNumber>(this);

    connect(mCommandSerialNumber.get(), &command::SerialNumber::commandEncoded,
            this, &Controller::onSerialNumberCommandEncoded);

    connect(mCommandSerialNumber.get(), &command::SerialNumber::answerDecoded,
            this, &Controller::onSerialNumberAnswerDecoded);

    mCommandDateTime = std::make_unique<command::DateTime>(this);

    connect(mCommandDateTime.get(), &command::DateTime::commandEncoded, this,
            &Controller::onDateTimeCommandEncoded);

    connect(mCommandDateTime.get(), &command::DateTime::answerDecoded, this,
            &Controller::onDateTimeAnswerDecoded);
}

// declaration has to be in cpp to make std::unique_ptr member forward
// declaration work
Controller::~Controller() = default;

void Controller::requestSerialNumber()
{
    qDebug() << Q_FUNC_INFO;
    mLastCommandType = CommandType::SerialNumber;
    mCommandSerialNumber->encodeCommand();
}

void Controller::setCurrentDateTime()
{
    qDebug() << Q_FUNC_INFO;
    mLastCommandType = CommandType::DateTime;
    mCommandDateTime->encodeCommand();
}

void Controller::onAnswerReceived(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO;
    switch (mLastCommandType) {
    case CommandType::SerialNumber:
        mCommandSerialNumber->decodeAnswer(answer);
        break;
    case CommandType::DateTime:
        mCommandDateTime->decodeAnswer(answer);
        break;
    case CommandType::Unknown:
        qDebug() << Q_FUNC_INFO << "CommandType::Unknown";
        break;
    }
}

void Controller::onSerialNumberCommandEncoded(const QByteArray &command)
{
    qDebug() << Q_FUNC_INFO;
    emit commandRequested(command);
}

void Controller::onSerialNumberAnswerDecoded(const QString &serialNumber)
{
    qDebug() << Q_FUNC_INFO;
    emit serialNumberReceived(serialNumber);
}

void Controller::onDateTimeCommandEncoded(const QByteArray &command)
{
    qDebug() << Q_FUNC_INFO;
    emit commandRequested(command);
}

void Controller::onDateTimeAnswerDecoded(
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
