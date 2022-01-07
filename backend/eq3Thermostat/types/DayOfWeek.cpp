#include "DayOfWeek.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

unsigned char encoded(DayOfWeek dayOfWeek)
{
    if (dayOfWeek == DayOfWeek::invalid) {
        qDebug() << Q_FUNC_INFO << "day of week is invalid";
        return 0;
    }
    return static_cast<unsigned char>(dayOfWeek);
}

} // namespace thermonator::eq3thermostat::types
