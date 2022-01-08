#ifndef THERMONATOR_EQ3THERMOSTAT_VALVEPOSITION_HPP
#define THERMONATOR_EQ3THERMOSTAT_VALVEPOSITION_HPP

#include <QDebug>

namespace thermonator::eq3thermostat {

class ValvePosition {
public:
    ValvePosition() = default;
    explicit ValvePosition(unsigned char byte);

    // return value in %
    double value() const;

    // valid range 0 to 100 %
    bool isValid() const;

private:
    static int decodeByte(unsigned char byte);

    int mValue{0};
};

inline bool operator==(const ValvePosition &lhs, const ValvePosition &rhs)
{
    if (lhs.value() != rhs.value()) {
        return false;
    }
    return true;
}

inline bool operator!=(const ValvePosition &lhs, const ValvePosition &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const ValvePosition &valvePosition);

} // namespace thermonator::eq3thermostat

#endif
