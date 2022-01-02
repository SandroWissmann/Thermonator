#include "DateTime.hpp"

namespace thermonator::eq3thermostat::types {

DateTime::DateTime(unsigned char yearByte, unsigned char monthByte,
                   unsigned char dayByte, unsigned char timeByte)
    : mDate{yearByte, monthByte, dayByte}, mTime{
                                               Time::fromEncodedByte(timeByte)}
{
}

int DateTime::year() const
{
    return mDate.year();
}

int DateTime::month() const
{
    return mDate.month();
}

int DateTime::day() const
{
    return mDate.day();
}

int DateTime::hour() const
{
    return mTime.hour();
}

int DateTime::minute() const
{
    return mTime.minute();
}

Date DateTime::date() const
{
    return mDate;
}

Time DateTime::time() const
{
    return mTime;
}

bool DateTime::isValid() const
{
    if (!mDate.isValid()) {
        return false;
    }
    if (!mTime.isValid()) {
        return false;
    }
    return true;
}

QDebug operator<<(QDebug debug, const DateTime &dateTime)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << dateTime.date() << dateTime.time();

    return debug;
}

} // namespace thermonator::eq3thermostat::types
