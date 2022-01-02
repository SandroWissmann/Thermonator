#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_DATE_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_DATE_HPP

#include <QDate>
#include <QDebug>

namespace thermonator::eq3thermostat::types {

class Date {
public:
    Date() = default;
    Date(unsigned char yearByte, unsigned char monthByte,
         unsigned char dayByte);

    int year() const;
    int month() const;
    int day() const;

    bool isValid() const;

    QDate value() const;

private:
    static int decodeYear(unsigned char byte);
    static int decodeMonth(unsigned char byte);
    static int decodeDay(unsigned char byte);

    QDate mDate;
};

inline bool operator==(const Date &lhs, const Date &rhs)
{
    if (lhs.value() != rhs.value()) {
        return false;
    }
    return true;
}

inline bool operator!=(const Date &lhs, const Date &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const Date &date);

} // namespace thermonator::eq3thermostat::types

#endif
