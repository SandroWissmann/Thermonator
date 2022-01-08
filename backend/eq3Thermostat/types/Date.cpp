#include "Date.hpp"

namespace thermonator::eq3thermostat {

Date::Date(unsigned char yearByte, unsigned char monthByte,
           unsigned char dayByte)
    : mDate{decodeYear(yearByte), decodeMonth(monthByte), decodeDay(dayByte)}
{
}

int Date::year() const
{
    return mDate.year();
}

int Date::month() const
{
    return mDate.month();
}

int Date::day() const
{
    return mDate.day();
}

bool Date::isValid() const
{
    return mDate.isValid();
}

QDate Date::value() const
{
    return mDate;
}

int Date::decodeYear(unsigned char byte)
{
    auto year = static_cast<int>(byte) + 2000;
    return year;
}

int Date::decodeMonth(unsigned char byte)
{
    auto month = static_cast<int>(byte);
    return month;
}

int Date::decodeDay(unsigned char byte)
{
    auto day = static_cast<int>(byte);
    return day;
}

QDebug operator<<(QDebug debug, const Date &date)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << date.value();

    return debug;
}

} // namespace thermonator::eq3thermostat
