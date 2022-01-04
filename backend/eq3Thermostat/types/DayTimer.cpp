#include "DayTimer.hpp"

#include "../../utility/EnumToString.hpp"
#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::types {

DayTimer::DayTimer(DayOfWeek dayOfWeek,
                   std::vector<DayTimerEntry> dayTimerEntries)
    : mDayOfWeek{dayOfWeek}, mDayTimerEntries{std::move(dayTimerEntries)}
{
}

DayTimer DayTimer::fromEncodedData(const QByteArray &data)
{
    qDebug() << Q_FUNC_INFO << "data:" << utility::toHexWithSpace(data);

    if (!dataIsValid(data)) {
        return DayTimer{};
    }

    auto bytes = utility::toUChars(data);

    auto dayOfWeek = optDecodeDayOfWeek(bytes[1]);
    if (dayOfWeek == DayOfWeek::invalid) {
        return DayTimer{};
    }

    auto optDayTimerEntries = optDecodeDayTimerEntries(bytes);
    if (!optDayTimerEntries) {
        return DayTimer{};
    }

    return DayTimer{dayOfWeek, *optDayTimerEntries};
}

std::vector<DayTimerEntry> DayTimer::dayTimerEntries() const
{
    return mDayTimerEntries;
}

DayOfWeek DayTimer::dayOfWeek() const
{
    return mDayOfWeek;
}

bool DayTimer::isValid() const
{
    if (mDayOfWeek == DayOfWeek::invalid) {
        return false;
    }
    if (mDayTimerEntries.size() <= 0) {
        return false;
    }
    if (mDayTimerEntries.size() > 7) {
        return false;
    }
    if (mDayTimerEntries.back().time().hour() != 24) {
        return false;
    }
    if (mDayTimerEntries.back().time().minute() != 0) {
        return false;
    }
    if (!timeIsAscendingInEntries(mDayTimerEntries)) {
        return false;
    }
    for (const auto &dayTimerEntry : mDayTimerEntries) {
        if (!dayTimerEntry.isValid()) {
            return false;
        }
    }
    return true;
}

bool DayTimer::dataIsValid(const QByteArray &data)
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

DayOfWeek DayTimer::optDecodeDayOfWeek(unsigned char byte)
{
    if (byte < 0x00 || byte > 0x06) {
        qWarning() << Q_FUNC_INFO
                   << "Answer has invalid day of week. value: " << Qt::hex
                   << static_cast<int>(byte);
        return DayOfWeek::invalid;
    }
    auto dayOfWeek = static_cast<types::DayOfWeek>(byte);
    qDebug() << Q_FUNC_INFO << "dayOfWeek" << utility::enumToString(dayOfWeek);
    return dayOfWeek;
}

std::optional<std::vector<DayTimerEntry>>
DayTimer::optDecodeDayTimerEntries(const std::vector<unsigned char> &bytes)
{
    std::vector<types::DayTimerEntry> dayTimerEntries;
    constexpr auto possibleEntriesCount = 7;
    dayTimerEntries.reserve(possibleEntriesCount);

    for (auto it = bytes.begin() + 2; it != bytes.end(); it += 2) {
        auto temperatureEncoded = *it;
        auto timeEncoded = *(it + 1);

        if (temperatureEncoded == 0x00 && timeEncoded == 0x00) {
            break;
        }

        auto temperature = decodeTemperature(temperatureEncoded);
        auto time = decodeTime(timeEncoded);

        types::DayTimerEntry dayTimerEntry{time, temperature};

        if (!dayTimerEntry.isValid()) {
            qWarning() << Q_FUNC_INFO
                       << "Invalid types::DayTimerEntry:" << dayTimerEntry;
            return {};
        }
        else {
            qDebug() << Q_FUNC_INFO
                     << "Valid types::DayTimerEntry:" << dayTimerEntry;
            dayTimerEntries.emplace_back(dayTimerEntry);
        }
    }

    return {dayTimerEntries};
}

double DayTimer::decodeTemperature(unsigned char byte)
{
    auto temperature = static_cast<int>(byte) / 2.0;
    return temperature;
}

types::Time DayTimer::decodeTime(unsigned char byte)
{
    auto minutesFromMidnight = static_cast<int>(byte) * 10;
    auto hour = minutesFromMidnight / 60;
    auto minutes = minutesFromMidnight - (hour * 60);
    types::Time time{hour, minutes};
    return time;
}

bool DayTimer::timeIsAscendingInEntries(
    const std::vector<DayTimerEntry> &dayTimerEntries)
{
    int lastTimeInMinutes = 0;
    for (const auto &dayTimerEntry : dayTimerEntries) {
        auto timeInMinutes =
            dayTimerEntry.time().hour() * 60 + dayTimerEntry.time().minute();
        if (timeInMinutes < lastTimeInMinutes) {
            return false;
        }
        lastTimeInMinutes = timeInMinutes;
    }
    return true;
}

QDebug operator<<(QDebug debug, const DayTimer &dayTimer)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "dayOfWeek: "
                    << utility::enumToString(dayTimer.dayOfWeek()) << '\n';
    debug.nospace() << "entries:\n";
    for (const auto &dayTimerEntry : dayTimer.dayTimerEntries()) {
        debug.nospace() << dayTimerEntry;
    }

    return debug;
}

} // namespace thermonator::eq3thermostat::types
