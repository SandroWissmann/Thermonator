#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_SWITCHTOCOMFORTTEMPERATURE_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_SWITCHTOCOMFORTTEMPERATURE_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

43 00 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 1 to 14: unused
Byte 0: request command "43"

*/

#include "SimpleCommandBase.hpp"

namespace thermonator::eq3thermostat::command {

class SwitchToComfortTemperature : public SimpleCommandBase {
    Q_OBJECT
public:
    explicit SwitchToComfortTemperature(QObject *parent = nullptr);

    ~SwitchToComfortTemperature() override = default;
};

} // namespace thermonator::eq3thermostat::command

#endif
