#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_TEMPERATURE_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_TEMPERATURE_HPP

#include <QDebug>

namespace thermonator::eq3thermostat::types {

class Temperature {
public:
    Temperature() = default;
    explicit Temperature(unsigned char byte);

    // return value in %
    double value() const;

    // valid range 5.0 °C to 29.5 °C
    bool isValid() const;

private:
    static double decodeByte(unsigned char byte);

    double mValue{0};
};

inline bool operator==(const Temperature &lhs, const Temperature &rhs)
{
    if (lhs.value() != rhs.value()) {
        return false;
    }
    return true;
}

inline bool operator!=(const Temperature &lhs, const Temperature &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const Temperature &temperature);

} // namespace thermonator::eq3thermostat::types

#endif
