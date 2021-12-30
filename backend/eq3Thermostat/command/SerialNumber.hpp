#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_SERIALNUMBER_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_SERIALNUMBER_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 1 to 14: unused
Byte 0: request command "00"

*/

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
signals:
    void commandEncoded(const QByteArray &command);
};

} // namespace thermonator::eq3thermostat::command

#endif
