#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_SERIALNUMBER_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_SERIALNUMBER_HPP

#include <QDebug>
#include <QString>

#include <array>

namespace thermonator::eq3thermostat::types {

class SerialNumber {
public:
    SerialNumber() = default;

    SerialNumber(const std::array<unsigned char, 10> &bytes);

    bool isValid() const;

    QString value() const;

private:
    static QString decodeBytes(const std::array<unsigned char, 10> &bytes);

    QString mValue;
    bool mIsValid{false};
};

inline bool operator==(const SerialNumber &lhs, const SerialNumber &rhs)
{
    if (lhs.value() != rhs.value()) {
        return false;
    }
    return true;
}

inline bool operator!=(const SerialNumber &lhs, const SerialNumber &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const SerialNumber &serialNumber);

} // namespace thermonator::eq3thermostat::types

#endif
