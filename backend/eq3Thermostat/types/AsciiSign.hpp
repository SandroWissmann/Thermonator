#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_ASCIISIGN_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_ASCIISIGN_HPP

#include <QDebug>

namespace thermonator::eq3thermostat::types {

class AsciiSign {
public:
    AsciiSign() = default;
    AsciiSign(unsigned char byte);

    char value() const;

private:
    char toAscii(unsigned char byte);

    char mSign{0};
};

inline bool operator==(const AsciiSign &lhs, const AsciiSign &rhs)
{
    if (lhs.value() != rhs.value()) {
        return false;
    }
    return true;
}

inline bool operator!=(const AsciiSign &lhs, const AsciiSign &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const AsciiSign &asciiSign);

} // namespace thermonator::eq3thermostat::types

#endif
