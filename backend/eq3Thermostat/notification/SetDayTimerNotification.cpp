#include "SetDayTimerNotification.hpp"

#include "../../utility/EnumToString.hpp"
#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

SetDayTimerNotification::SetDayTimerNotification(const DayOfWeek &dayOfWeek)
    : mDayOfWeek{dayOfWeek}
{
}

SetDayTimerNotification
SetDayTimerNotification::fromEncodedData(const QByteArray &data)
{
    qDebug() << Q_FUNC_INFO << "data:" << utility::toHexWithSpace(data);

    if (!dataIsValid(data)) {
        return SetDayTimerNotification{};
    }

    auto bytes = utility::toUChars(data);

    auto dayOfWeek = eq3thermostat::fromEncodedByte(bytes[2]);
    if (dayOfWeek == DayOfWeek::invalid) {
        qWarning() << Q_FUNC_INFO << "DayOfWeek is invalid";
        return SetDayTimerNotification{};
    }

    return SetDayTimerNotification{dayOfWeek};
}

DayOfWeek SetDayTimerNotification::dayOfWeek() const
{
    return mDayOfWeek;
}

bool SetDayTimerNotification::isValid() const
{
    if (mDayOfWeek == DayOfWeek::invalid) {
        return false;
    }
    return true;
}

bool SetDayTimerNotification::dataIsValid(const QByteArray &data)
{
    if (data.size() != 3) {
        qWarning() << Q_FUNC_INFO << "Answer has invalid length";
        return false;
    }
    if (static_cast<unsigned char>(data[0]) != 0x02) {
        qWarning() << Q_FUNC_INFO
                   << "Answer has invalid notification value in byte 0: "
                   << Qt::hex << static_cast<int>(data[0]);
        return false;
    }
    if (static_cast<unsigned char>(data[1]) != 0x02) {
        qWarning() << Q_FUNC_INFO
                   << "Answer has invalid notification value in byte 1: "
                   << Qt::hex << static_cast<int>(data[1]);
        return false;
    }
    return true;
}

} // namespace thermonator::eq3thermostat
