#include "Time.hpp"

#include <QDebug>
#include <QTime>

namespace thermonator::eq3thermostat {

Time::Time(int hour, int minute) : mHour{hour}, mMinute{minute}
{
}

Time Time::fromEncodedByte(unsigned char byte)
{
    auto minutesFromMidnight = static_cast<int>(byte) * 10;
    auto hour = minutesFromMidnight / 60;
    auto minutes = minutesFromMidnight - (hour * 60);
    Time time{hour, minutes};
    return time;
}

int Time::hour() const
{
    return mHour;
}

int Time::minute() const
{
    return mMinute;
}

unsigned char Time::encoded() const
{
    if (!isValid()) {
        return 0;
    }
    auto minutesFromMidnight = mHour * 60 + mMinute;
    auto byte = static_cast<unsigned char>(minutesFromMidnight / 10);
    return byte;
}

bool Time::isValid() const
{
    if (QTime::isValid(mHour, mMinute, 0)) {
        return true;
    }
    // this case is invalid for QTime but we need it for the thermostat
    if (mHour == 24 && mMinute == 0) {
        return true;
    }
    return false;
}

QDebug operator<<(QDebug debug, const Time &time)
{
    QDebugStateSaver saver(debug);

    auto formatedHour =
        QStringLiteral("%1").arg(time.hour(), 2, 10, QLatin1Char('0'));
    auto formatedMinute =
        QStringLiteral("%1").arg(time.minute(), 2, 10, QLatin1Char('0'));

    debug.nospace() << '(' << formatedHour << ':' << formatedMinute << ')';

    return debug;
}

} // namespace thermonator::eq3thermostat
