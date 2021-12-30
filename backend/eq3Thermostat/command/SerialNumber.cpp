#include "SerialNumber.hpp"

namespace thermonator::eq3thermostat::command {

SerialNumber::SerialNumber(QObject *parent) : SimpleCommandBase{0x00, parent}
{
}

} // namespace thermonator::eq3thermostat::command
