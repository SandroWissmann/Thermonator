#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_SETECOTEMPERATURE_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_SETECOTEMPERATURE_HPP

/*
Command:

0  Bytes

44 Values in hex

Byte 0: request command "44"

*/
#include <QByteArray>

namespace thermonator::eq3thermostat::types {

class SetEcoTemperatureCommand {
public:
    SetEcoTemperatureCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug,
                  const SetEcoTemperatureCommand &setEcoTemperatureCommand);

} // namespace thermonator::eq3thermostat::types

#endif
