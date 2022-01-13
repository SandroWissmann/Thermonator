#include "GetDayTimerNotification.hpp"

#include "../../utility/EnumToString.hpp"
#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

GetDayTimerNotification::GetDayTimerNotification(const DayTimer &dayTimer)
    : mDayTimer{dayTimer}
{
}

GetDayTimerNotification
GetDayTimerNotification::fromEncodedData(const QByteArray &data)
{
    qDebug() << Q_FUNC_INFO << "data:" << utility::toHexWithSpace(data);

    if (!dataIsValid(data)) {
        return GetDayTimerNotification{};
    }

    auto bytes = utility::toUChars(data);

    auto dayOfWeek = eq3thermostat::fromEncodedByte(bytes[1]);
    if (dayOfWeek == DayOfWeek::invalid) {
        qWarning() << Q_FUNC_INFO << "DayOfWeek is invalid";
        return GetDayTimerNotification{};
    }

    std::vector<unsigned char> dayTimerBytes{bytes.begin() + 2, bytes.end()};
    auto dayTimerEntries = DayTimerEntries::fromEncodedBytes(dayTimerBytes);
    if (!dayTimerEntries.isValid()) {
        qWarning() << Q_FUNC_INFO << "DayTimerNotification is invalid";
        return GetDayTimerNotification{};
    }

    DayTimer dayTimer{dayOfWeek, dayTimerEntries};

    return GetDayTimerNotification{dayTimer};
}

DayTimer GetDayTimerNotification::dayTimer() const
{
    return mDayTimer;
}

bool GetDayTimerNotification::isValid() const
{
    if (mDayTimer.isValid()) {
        return false;
    }
    return true;
}

bool GetDayTimerNotification::dataIsValid(const QByteArray &data)
{
    if (data.size() != 16) {
        qWarning() << Q_FUNC_INFO << "Answer has invalid length";
        return false;
    }
    if (static_cast<unsigned char>(data[0]) != 0x21) {
        qWarning() << Q_FUNC_INFO
                   << "Answer has invalid notification value: " << Qt::hex
                   << static_cast<int>(data[0]);
        return false;
    }
    return true;
}

} // namespace thermonator::eq3thermostat
