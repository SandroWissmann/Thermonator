#include "AsciiSign.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

AsciiSign::AsciiSign(unsigned char byte) : mSign{toAscii(byte)}
{
}

char AsciiSign::toAscii(unsigned char byte)
{
    return static_cast<char>(byte - 0x30);
}

char AsciiSign::value() const
{
    return mSign;
}

QDebug operator<<(QDebug debug, const AsciiSign &asciiSign)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << asciiSign.value();

    return debug;
}

} // namespace thermonator::eq3thermostat
