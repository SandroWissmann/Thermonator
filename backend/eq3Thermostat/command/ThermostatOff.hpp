#ifndef THERMONATOR_EQ3THERMOSTAT_COMMAND_THERMOSTATOFF_HPP
#define THERMONATOR_EQ3THERMOSTAT_COMMAND_THERMOSTATOFF_HPP

/*
Command:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

41 09 00 00 00 00 00 00 00 00 00 00 00 00 00 Values in hex

Byte 2 to 14: unused
Byte 1: temperature * 2 = 4.5°C. This is the signal for the thermostate
firmware to turn the thermostate off
Byte 0: request command "41"

*/

#include <QObject>

#include <memory>

namespace thermonator::eq3thermostat::command {

class Temperature;

class ThermostatOff : public QObject {
    Q_OBJECT
public:
    explicit ThermostatOff(QObject *parent = nullptr);

    ~ThermostatOff();

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
