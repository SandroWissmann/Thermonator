#include "Controller.hpp"

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

void Controller::onAnswerReceived(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO;
    if (mLastCommandType == CommandType::SerialNumber) {
        mCommandSerialNumber->decodeAnswer(answer);
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

} // namespace thermonator::eq3thermostat
