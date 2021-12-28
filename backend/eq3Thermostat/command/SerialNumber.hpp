#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_SERIALNUMBER_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_SERIALNUMBER_HPP

#include <QObject>

namespace thermonator::eq3thermostat::command {

class SerialNumber : public QObject {
    Q_OBJECT
public:
    explicit SerialNumber(QObject *parent = nullptr);

    ~SerialNumber() = default;

    // Request encoding the command
    // triggers signal commandEncoded
    void encodeCommand();

    // Request decoding the answer
    // triggers signal answerDecoded
    void decodeAnswer(const QByteArray &answer);

signals:
    void commandEncoded(const QByteArray &command);

    void answerDecoded(const QString &serialNumber);

private:
    char hexToAscii(char hex);
};

} // namespace thermonator::eq3thermostat::command

#endif
