#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_THERMOSTATON_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_THERMOSTATON_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

41 3c 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 2 to 14: unused
Byte 1: temperature * 2 = 30.0°C. This is the signal for the thermostate
firmware to turn the thermostate on
Byte 0: request command "41"

*/

#include "Temperature.hpp"

#include <memory>

namespace thermonator::eq3thermostat::command {

class ThermostatOn : public QObject {
    Q_OBJECT
public:
    explicit ThermostatOn(QObject *parent = nullptr);

    ~ThermostatOn() = default;

    // Request encoding the command
    // triggers signal commandEncoded
    void encodeCommand();

signals:
    void commandEncoded(const QByteArray &command);

private:
    std::unique_ptr<Temperature> mTemperature;
};

} // namespace thermonator::eq3thermostat::command

#endif
