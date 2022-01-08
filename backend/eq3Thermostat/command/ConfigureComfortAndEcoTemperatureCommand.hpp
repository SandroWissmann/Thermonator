#ifndef THERMONATOR_EQ3THERMOSTAT_CONFIGURECOMFORTANDECOTEMPERATURECOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_CONFIGURECOMFORTANDECOTEMPERATURECOMMAND_HPP

/*
Command:

0  1  2  Bytes

11 2b 23 Values in hex

Byte 2: eco temperature * 2
Byte 1: comfort temperature * 2
Byte 0: request command "11"

For this example the bytes are decoded to this:

Byte 2: 0x23 -> 35/2.0 -> 17.5 °C
Byte 1: 0x2b -> 43/2.0 -> 21.5 °C
Byte 0: N/A

*/

#include <QByteArray>

namespace thermonator::eq3thermostat {

class Temperature;

class ConfigureComfortAndEcoTemperatureCommand {
public:
    ConfigureComfortAndEcoTemperatureCommand(
        const Temperature &comfortTemperature,
        const Temperature &ecoTemperature);

    QByteArray encoded() const;

private:
    static QByteArray encode(const Temperature &comfortTemperature,
                             const Temperature &ecoTemperature);

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug, const ConfigureComfortAndEcoTemperatureCommand
                                    &configureComfortAndEcoTemperatureCommand);

} // namespace thermonator::eq3thermostat

#endif
