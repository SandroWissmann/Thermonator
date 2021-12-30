#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_BOOSTON_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_BOOSTON_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

45 ff 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 2 to 14: unused
Byte 1: value > 0 turns on the boost. So we send ff for Boost on
Byte 0: request command "45"

*/

#include <QObject>

#include <memory>

namespace thermonator::eq3thermostat::command {

class BoostControl;

class BoostOn : public QObject {
    Q_OBJECT
public:
    explicit BoostOn(QObject *parent = nullptr);

    ~BoostOn();

    // Request encoding the command
    // triggers signal commandEncoded
    void encodeCommand();

signals:
    void commandEncoded(const QByteArray &command);

private:
    std::unique_ptr<BoostControl> mBoostControl;
};

} // namespace thermonator::eq3thermostat::command

#endif
