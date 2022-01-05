#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_DAYOFWEEK_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_DAYOFWEEK_HPP

#include <QObject>

namespace thermonator::eq3thermostat::types {

class DayOfWeekQEnum {
    Q_GADGET
public:
    enum class Value {
        saturday,
        sunday,
        monday,
        tuesday,
        wednesday,
        thursday,
        friday,
        invalid
    };
    Q_ENUM(Value)

private:
    explicit DayOfWeekQEnum();
};

typedef DayOfWeekQEnum::Value DayOfWeek;

} // namespace thermonator::eq3thermostat::types

#endif