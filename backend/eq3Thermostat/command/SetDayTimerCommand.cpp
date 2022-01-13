#include "SetDayTimerCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

SetDayTimerCommand::SetDayTimerCommand(DayOfWeek dayOfWeek,
                                       const DayTimerEntries &dayTimerEntries)
    : mCommand{encode(dayOfWeek, dayTimerEntries)}
{
}

QByteArray SetDayTimerCommand::encoded() const
{
    return mCommand;
}

QByteArray SetDayTimerCommand::encode(DayOfWeek dayOfWeek,
                                      const DayTimerEntries &dayTimerEntries)
{
    QByteArray command;
    constexpr auto bytesCount = 16;
    command.reserve(bytesCount);
    command.append(QByteArray::fromHex("10"));
    command.append(eq3thermostat::encoded(dayOfWeek));

    auto dayTimerEntriesBytes = dayTimerEntries.encoded();

    for (const auto dayTimerEntriesByte : dayTimerEntriesBytes) {
        command.append(dayTimerEntriesByte);
    }

    Q_ASSERT(command.size() == bytesCount);
    return command;
}

QDebug operator<<(QDebug debug, const SetDayTimerCommand &setDayTimerCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SetDayTimerCommand: "
                    << utility::toHexWithSpace(setDayTimerCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat
