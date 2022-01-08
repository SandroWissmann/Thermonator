#ifndef THERMONATOR_EQ3THERMOSTAT_CONFIGUREOPENWINDOWMODECOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_CONFIGUREOPENWINDOWMODECOMMAND_HPP

/*
Command:

0  1  2  Bytes

14 19 0c Values in hex

Byte 2: open window interval 1 = 5 mins
Byte 1: open window temperature * 2
Byte 0: request command "14"

For this example the bytes are decoded to this:

Byte 2: 0x0c -> 12*5 -> 60 Min
Byte 1: 0x19 -> 25/2.0 -> 12.5 °C
Byte 0: N/A

*/

#include <QByteArray>

namespace thermonator::eq3thermostat {

class Temperature;
class OpenWindowInterval;

class ConfigureOpenWindowModeCommand {
public:
    ConfigureOpenWindowModeCommand(
        const Temperature &openWindowTemperature,
        const OpenWindowInterval &openWindowInterval);

    QByteArray encoded() const;

private:
    static QByteArray encode(const Temperature &openWindowTemperature,
                             const OpenWindowInterval &openWindowInterval);

    QByteArray mCommand{};
};

QDebug operator<<(
    QDebug debug,
    const ConfigureOpenWindowModeCommand &configureOpenWindowModeCommand);

} // namespace thermonator::eq3thermostat

#endif
