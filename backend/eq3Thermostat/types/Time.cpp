#include "Time.hpp"

#include <QDebug>
#include <QTime>

namespace thermonator::eq3thermostat {

Time::Time(int hour, int minute) : mHour{hour}, mMinute{minute}
{
}

Time Time::fromEncodedByte(unsigned char byte)
{
    auto hour = static_cast<int>(byte) / 2;
    auto minute = (static_cast<int>(byte) % 2) * 30;
    Time time{hour, minute};
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
