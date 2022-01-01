#include "Time.hpp"

#include <QDebug>
#include <QTime>

namespace thermonator::eq3thermostat::types {

Time::Time(int hour, int minute) : mHour{hour}, mMinute{minute}
{
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

    debug.nospace() << '(' << time.hour() << '/' << time.minute() << ')';

    return debug;
}

} // namespace thermonator::eq3thermostat::types
