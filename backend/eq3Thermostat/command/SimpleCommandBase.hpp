#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_SIMPLECOMMANDBASE_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_SIMPLECOMMANDBASE_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

xx 00 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 1 to 14: unused
Byte 0: command byte which can be set by class.

*/

#include <QObject>

namespace thermonator::eq3thermostat::command {

class SimpleCommandBase : public QObject {
    Q_OBJECT
public:
    explicit SimpleCommandBase(char commandByte, QObject *parent = nullptr);

    virtual ~SimpleCommandBase() = default;

    // Request encoding the command
    // triggers signal commandEncoded
    void encodeCommand();
signals:
    void commandEncoded(const QByteArray &command);

private:
    char mCommandByte{0};
};

} // namespace thermonator::eq3thermostat::command

#endif
