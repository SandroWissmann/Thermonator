#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_DAYTIMER_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_DAYTIMER_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

20 01 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 2 to 14: unused
Byte 1: day of the week from 00 = saturday to 06 = friday
Byte 0: request command "20"

For this example the bytes are decoded to this:

Byte 2 to 14: N/A
Byte 1: 0x01 -> sunday
Byte 0: N/A

*/

#include "../types/DayOfWeek.hpp"

#include <QObject>

namespace thermonator::eq3thermostat::command {

class DayTimer : public QObject {
    Q_OBJECT
public:
    explicit DayTimer(QObject *parent = nullptr);

    ~DayTimer() = default;

    // Request encoding the command
    // triggers signal commandEncoded
    void encodeCommand(types::DayOfWeek dayOfWeek);

signals:
    void commandEncoded(const QByteArray &command);
};

} // namespace thermonator::eq3thermostat::command

#endif
