#ifndef THERMONATOR_EQ3THERMOSTAT_TEMPERATUREOFFSET_HPP
#define THERMONATOR_EQ3THERMOSTAT_TEMPERATUREOFFSET_HPP

#include <QDebug>

namespace thermonator::eq3thermostat {

class TemperatureOffset {
public:
    TemperatureOffset() = default;
    explicit TemperatureOffset(unsigned char byte);

    // value is made valid during construction
    explicit TemperatureOffset(double value);

    // return value in %
    double value() const;

    // returns temperature as encoded byte
    // returns 0 if isInvalid() is true
    unsigned char encoded() const;

    // valid range -3.5 °C to 3.5 °C
    bool isValid() const;

private:
    static double decodeByte(unsigned char byte);
    static double makeValid(double value);

    double mValue{0};
};

inline bool operator==(const TemperatureOffset &lhs,
                       const TemperatureOffset &rhs)
{
    if (lhs.value() != rhs.value()) {
        return false;
    }
    return true;
}

inline bool operator!=(const TemperatureOffset &lhs,
                       const TemperatureOffset &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const TemperatureOffset &temperatureOffset);

} // namespace thermonator::eq3thermostat

#endif
