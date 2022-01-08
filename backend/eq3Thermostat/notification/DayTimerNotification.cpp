#include "DayTimerNotification.hpp"

#include "../../utility/EnumToString.hpp"
#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

DayTimerNotification::DayTimerNotification(
    DayOfWeek dayOfWeek, std::vector<DayTimerEntry> dayTimerEntries)
    : mDayOfWeek{dayOfWeek}, mDayTimerEntries{std::move(dayTimerEntries)}
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

    auto dayOfWeek = optDecodeDayOfWeek(bytes[1]);
    if (dayOfWeek == DayOfWeek::invalid) {
        return DayTimerNotification{};
    }

    auto optDayTimerEntries = optDecodeDayTimerEntries(bytes);
    if (!optDayTimerEntries) {
        return DayTimerNotification{};
    }

    return DayTimerNotification{dayOfWeek, *optDayTimerEntries};
}

std::vector<DayTimerEntry> DayTimerNotification::dayTimerEntries() const
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

DayOfWeek DayTimerNotification::optDecodeDayOfWeek(unsigned char byte)
{
    if (byte < 0x00 || byte > 0x06) {
        qWarning() << Q_FUNC_INFO
                   << "Answer has invalid day of week. value: " << Qt::hex
                   << static_cast<int>(byte);
        return DayOfWeek::invalid;
    }
    auto dayOfWeek = static_cast<DayOfWeek>(byte);
    qDebug() << Q_FUNC_INFO << "dayOfWeek" << utility::enumToString(dayOfWeek);
    return dayOfWeek;
}

std::optional<std::vector<DayTimerEntry>>
DayTimerNotification::optDecodeDayTimerEntries(
    const std::vector<unsigned char> &bytes)
{
    std::vector<DayTimerEntry> dayTimerEntries;
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

        DayTimerEntry dayTimerEntry{time, temperature};

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

double DayTimerNotification::decodeTemperature(unsigned char byte)
{
    auto temperature = static_cast<int>(byte) / 2.0;
    return temperature;
}

Time DayTimerNotification::decodeTime(unsigned char byte)
{
    auto minutesFromMidnight = static_cast<int>(byte) * 10;
    auto hour = minutesFromMidnight / 60;
    auto minutes = minutesFromMidnight - (hour * 60);
    Time time{hour, minutes};
    return time;
}

bool DayTimerNotification::timeIsAscendingInEntries(
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

QDebug operator<<(QDebug debug,
                  const DayTimerNotification &dayTimerNotification)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "dayOfWeek: "
                    << utility::enumToString(dayTimerNotification.dayOfWeek())
                    << '\n';
    debug.nospace() << "entries:\n";
    for (const auto &dayTimerEntry : dayTimerNotification.dayTimerEntries()) {
        debug.nospace() << dayTimerEntry;
    }

    return debug;
}

} // namespace thermonator::eq3thermostat
