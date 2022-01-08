#include "UnknownStatusByte.hpp"

namespace thermonator::eq3thermostat {

UnknownStatusByte::UnknownStatusByte(unsigned char byte)
    : mValue(decodeByte(byte))
{
}

int UnknownStatusByte::value() const
{
    return mValue;
}

bool UnknownStatusByte::isValid() const
{
    return true;
}

int UnknownStatusByte::decodeByte(unsigned char byte)
{
    auto unknownStatusByte = static_cast<int>(byte);
    return unknownStatusByte;
}

QDebug operator<<(QDebug debug, const UnknownStatusByte &unknownStatusByte)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << unknownStatusByte.value() << " ???";

    return debug;
}

} // namespace thermonator::eq3thermostat
