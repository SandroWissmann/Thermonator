#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_OPENWINDOWINTERVAL_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_OPENWINDOWINTERVAL_HPP

#include <QDebug>

namespace thermonator::eq3thermostat::types {

class OpenWindowInterval {
public:
    OpenWindowInterval() = default;
    explicit OpenWindowInterval(unsigned char byte);

    // return value in min
    int value() const;

    // valid range 0 min to 60 min
    bool isValid() const;

private:
    static int decodeByte(unsigned char byte);

    int mValue{0};
};

inline bool operator==(const OpenWindowInterval &lhs,
                       const OpenWindowInterval &rhs)
{
    if (lhs.value() != rhs.value()) {
        return false;
    }
    return true;
}

inline bool operator!=(const OpenWindowInterval &lhs,
                       const OpenWindowInterval &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const OpenWindowInterval &openWindowInterval);

} // namespace thermonator::eq3thermostat::types

#endif