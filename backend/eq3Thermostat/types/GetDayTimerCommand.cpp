#include "GetDayTimerCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

GetDayTimerCommand::GetDayTimerCommand(DayOfWeek dayOfWeek)
    : mCommand{encode(dayOfWeek)}
{
}

QByteArray GetDayTimerCommand::encoded() const
{
    return mCommand;
}

QByteArray GetDayTimerCommand::encode(DayOfWeek dayOfWeek)
{
    QByteArray command;
    constexpr auto bytesCount = 2;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("20"));
    command.append(thermonator::eq3thermostat::types::encoded(dayOfWeek));
    return command;
}

QDebug operator<<(QDebug debug, const GetDayTimerCommand &getDayTimerCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "GetDayTimerCommand: "
                    << utility::toHexWithSpace(getDayTimerCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat::types
