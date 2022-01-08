#ifndef THERMONATOR_EQ3THERMOSTAT_DAYOFWEEK_HPP
#define THERMONATOR_EQ3THERMOSTAT_DAYOFWEEK_HPP

#include <QObject>

namespace thermonator::eq3thermostat {

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

// if value is invalid we return 0 == saturday and log a warning
unsigned char encoded(DayOfWeek dayOfWeek);

} // namespace thermonator::eq3thermostat

#endif
