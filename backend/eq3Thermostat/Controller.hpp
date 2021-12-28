#ifndef THERMONATOR_EQ3THERMOSTAT_CONTROLLER_HPP
#define THERMONATOR_EQ3THERMOSTAT_CONTROLLER_HPP

#include <QObject>

#include <memory>

namespace thermonator::eq3thermostat {

namespace command {
class SerialNumber;
}

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    Q_INVOKABLE
    void requestSerialNumber();

public slots:
    void onAnswerReceived(const QByteArray &answer);
signals:
    void commandRequested(const QByteArray &command);

    void serialNumberReceived(const QString &serialNumber);

private slots:
    void onSerialNumberCommandEncoded(const QByteArray &command);
    void onSerialNumberAnswerDecoded(const QString &serialNumber);

private:
    enum class CommandType { Undefined, SerialNumber };

    CommandType mLastCommandType{CommandType::Undefined};

    std::unique_ptr<command::SerialNumber> mCommandSerialNumber;
};

} // namespace thermonator::eq3thermostat

#endif
