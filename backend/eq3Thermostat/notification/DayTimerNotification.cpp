#include "DayTimerNotification.hpp"

#include "../../utility/EnumToString.hpp"
#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

DayTimerNotification::DayTimerNotification(
    DayOfWeek dayOfWeek, const DayTimerEntries &dayTimerEntries)
    : mDayOfWeek{dayOfWeek}, mDayTimerEntries{dayTimerEntries}
{
}

DayTimerNotification
DayTimerNotification::fromEncodedData(const QByteArray &data)
{
    qDebug() << Q_FUNC_INFO << "data:" << utility::toHexWithSpace(data);

    if (!dataIsValid(data)) {
        return DayTimerNotification{};
    }

    auto bytes = utility::toUChars(data);

    auto dayOfWeek = eq3thermostat::fromEncodedByte(bytes[1]);
    if (dayOfWeek == DayOfWeek::invalid) {
        qWarning() << Q_FUNC_INFO << "DayOfWeek is invalid";
        return DayTimerNotification{};
    }

    std::vector<unsigned char> dayTimerBytes{bytes.begin() + 2, bytes.end()};
    auto dayTimerEntries = DayTimerEntries::fromEncodedBytes(dayTimerBytes);
    if (!dayTimerEntries.isValid()) {
        qWarning() << Q_FUNC_INFO << "DayTimerNotification is invalid";
        return DayTimerNotification{};
    }

    return DayTimerNotification{dayOfWeek, dayTimerEntries};
}

DayTimerEntries DayTimerNotification::dayTimerEntries() const
{
    return mDayTimerEntries;
}

DayOfWeek DayTimerNotification::dayOfWeek() const
{
    return mDayOfWeek;
}

bool DayTimerNotification::isValid() const
{
    if (mDayOfWeek == DayOfWeek::invalid) {
        return false;
    }
    if (!mDayTimerEntries.isValid()) {
        return false;
    }
    return true;
}

bool DayTimerNotification::dataIsValid(const QByteArray &data)
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

QDebug operator<<(QDebug debug,
                  const DayTimerNotification &dayTimerNotification)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "dayOfWeek: "
                    << utility::enumToString(dayTimerNotification.dayOfWeek())
                    << '\n';
    debug.nospace() << dayTimerNotification.dayTimerEntries();

    return debug;
}

} // namespace thermonator::eq3thermostat
