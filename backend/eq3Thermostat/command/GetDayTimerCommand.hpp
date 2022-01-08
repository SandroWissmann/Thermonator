#ifndef THERMONATOR_EQ3THERMOSTAT_GETDAYTIMERCOMMANDCOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_GETDAYTIMERCOMMANDCOMMAND_HPP

/*
Command:

0  1  Bytes

20 01 in hex

Byte 1: day of the week from 00 = saturday to 06 = friday
Byte 0: request command "20"

For this example the bytes are decoded to this:

Byte 1: 0x01 -> sunday
Byte 0: N/A

*/

#include <QByteArray>

#include "../types/DayOfWeek.hpp"

namespace thermonator::eq3thermostat {

class GetDayTimerCommand {
public:
    GetDayTimerCommand(DayOfWeek dayOfWeek);

    QByteArray encoded() const;

private:
    static QByteArray encode(DayOfWeek dayOfWeek);

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug, const GetDayTimerCommand &getDayTimerCommand);

} // namespace thermonator::eq3thermostat

#endif
