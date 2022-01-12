#include "DayOfWeek.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

DayOfWeek fromEncodedByte(unsigned char byte)
{
    if (byte < 0x00 || byte > 0x06) {
        qWarning() << Q_FUNC_INFO
                   << "Answer has invalid day of week. value: " << Qt::hex
                   << static_cast<int>(byte);
        return DayOfWeek::invalid;
    }
    auto dayOfWeek = static_cast<DayOfWeek>(byte);
    return dayOfWeek;
}

unsigned char encoded(DayOfWeek dayOfWeek)
{
    if (dayOfWeek == DayOfWeek::invalid) {
        qDebug() << Q_FUNC_INFO << "day of week is invalid";
        return 0;
    }
    return static_cast<unsigned char>(dayOfWeek);
}

} // namespace thermonator::eq3thermostat
