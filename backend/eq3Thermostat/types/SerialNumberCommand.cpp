#include "SerialNumberCommand.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

SerialNumberCommand::SerialNumberCommand() : mCommand{encode()}
{
}

QByteArray SerialNumberCommand::encoded() const
{
    return mCommand;
}

QByteArray SerialNumberCommand::encode()
{
    QByteArray command;
    constexpr auto bytesCount = 1;
    command.reserve(bytesCount);
    command.append(static_cast<int>(0x00));

    return command;
}

QDebug operator<<(QDebug debug, const SerialNumberCommand &serialNumberCommand)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "SerialNumberCommand: "
                    << utility::toHexWithSpace(serialNumberCommand.encoded());

    return debug;
}

} // namespace thermonator::eq3thermostat::types
