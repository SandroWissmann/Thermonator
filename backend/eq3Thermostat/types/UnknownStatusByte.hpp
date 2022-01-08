#ifndef THERMONATOR_EQ3THERMOSTAT_UNKNOWNSTATUSBYTE_HPP
#define THERMONATOR_EQ3THERMOSTAT_UNKNOWNSTATUSBYTE_HPP

#include <QDebug>

namespace thermonator::eq3thermostat {

class UnknownStatusByte {
public:
    UnknownStatusByte() = default;
    explicit UnknownStatusByte(unsigned char byte);

    // return value
    int value() const;

    // placeholder. Since we dont know what it is all is valid
    bool isValid() const;

private:
    static int decodeByte(unsigned char byte);

    int mValue{0};
};

inline bool operator==(const UnknownStatusByte &lhs,
                       const UnknownStatusByte &rhs)
{
    if (lhs.value() != rhs.value()) {
        return false;
    }
    return true;
}

inline bool operator!=(const UnknownStatusByte &lhs,
                       const UnknownStatusByte &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const UnknownStatusByte &unknownStatusByte);

} // namespace thermonator::eq3thermostat

#endif
