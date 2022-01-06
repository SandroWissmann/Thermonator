#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_SETCOMFORTTEMPERATURE_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_SETCOMFORTTEMPERATURE_HPP

/*
Command:

0  Bytes

43 Values in hex

Byte 0: request command "43"

*/
#include <QByteArray>

namespace thermonator::eq3thermostat::types {

class SetComfortTemperatureCommand {
public:
    SetComfortTemperatureCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug
operator<<(QDebug debug,
           const SetComfortTemperatureCommand &setComfortTemperatureCommand);

} // namespace thermonator::eq3thermostat::types

#endif
