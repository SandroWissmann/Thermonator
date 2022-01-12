#include "DayTimerEntries.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat {

DayTimerEntries::DayTimerEntries(std::vector<DayTimerEntry> entries)
    : mEntries{entries}
{
}

DayTimerEntries
DayTimerEntries::fromEncodedBytes(const std::vector<unsigned char> &bytes)
{
    constexpr auto expectdSize = 14;
    if (bytes.size() != expectdSize) {
        qWarning() << Q_FUNC_INFO << "Invalid count of bytes: " << bytes.size();
        return DayTimerEntries{};
    }

    std::vector<DayTimerEntry> dayTimerEntries;
    constexpr auto possibleEntriesCount = expectdSize / 2;
    dayTimerEntries.reserve(possibleEntriesCount);

    for (auto it = bytes.begin(); it != bytes.end(); it += 2) {
        auto temperatureByte = *it;
        auto timeByte = *(it + 1);

        if (temperatureByte == 0x00 && timeByte == 0x00) {
            break;
        }

        std::vector<unsigned char> entryBytes{it, it + 2};
        auto dayTimerEntry = DayTimerEntry::fromEncodedBytes(entryBytes);

        if (!dayTimerEntry.isValid()) {
            qWarning() << Q_FUNC_INFO
                       << "Invalid DayTimerEntry:" << dayTimerEntry;
            return DayTimerEntries{};
        }
        else {
            qDebug() << Q_FUNC_INFO << "Valid DayTimerEntry:" << dayTimerEntry;
            dayTimerEntries.emplace_back(dayTimerEntry);
        }
    }

    return DayTimerEntries{dayTimerEntries};
}

std::vector<DayTimerEntry> DayTimerEntries::DayTimerEntries::entries() const
{
    return mEntries;
}

bool DayTimerEntries::isValid() const
{
    if (mEntries.size() <= 0) {
        return false;
    }
    if (mEntries.size() > 7) {
        return false;
    }
    if (!mEntries.empty()) {
        auto lastEntry = mEntries.back();
        auto lastTime = lastEntry.time();

        if (lastTime.hour() != 24) {
            return false;
        }
        if (lastTime.minute() != 0) {
            return false;
        }
    }
    if (!timeIsAscendingInEntries(mEntries)) {
        return false;
    }
    for (const auto &entry : mEntries) {
        if (!entry.isValid()) {
            return false;
        }
    }
    return true;
}

bool DayTimerEntries::timeIsAscendingInEntries(
    const std::vector<DayTimerEntry> &entries)
{
    int lastTimeInMinutes = 0;
    for (const auto &entry : entries) {
        auto timeInMinutes = entry.time().hour() * 60 + entry.time().minute();
        if (timeInMinutes < lastTimeInMinutes) {
            return false;
        }
        lastTimeInMinutes = timeInMinutes;
    }
    return true;
}

QDebug operator<<(QDebug debug, const DayTimerEntries &dayTimerEntries)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "entries:\n";
    for (const auto &entry : dayTimerEntries.entries()) {
        debug.nospace() << entry;
    }

    return debug;
}

} // namespace thermonator::eq3thermostat
