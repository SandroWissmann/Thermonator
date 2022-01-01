#include "DayTimerNotification.hpp"

#include "../types/DayTimer.hpp"
#include "../types/Time.hpp"

#include "../../utility/EnumToString.hpp"
#include "../../utility/Utility.hpp"

#include <QDebug>

namespace thermonator::eq3thermostat::answer {

DayTimerNotification::DayTimerNotification(QObject *parent) : QObject{parent}
{
}

void DayTimerNotification::decodeAnswer(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO << "answer:" << utility::toHexWithSpace(answer);
    if (!answerIsValid(answer)) {
        emit answerNotDecodedable();
        return;
    }

    auto optDayOfWeek = optDecodeDayOfWeek(answer[1]);
    if (!optDayOfWeek) {
        emit answerNotDecodedable();
        return;
    }

    auto optDayTimer = optDecodeDayTimer(answer);
    if (!optDayTimer) {
        emit answerNotDecodedable();
        return;
    }

    emit answerDecoded(*optDayOfWeek, *optDayTimer);
}

bool DayTimerNotification::answerIsValid(const QByteArray &answer)
{
    if (answer.size() != 16) {
        qWarning() << Q_FUNC_INFO << "Answer has invalid length";
        return false;
    }
    if (answer[0] != 0x21) {
        qWarning() << Q_FUNC_INFO
                   << "Answer has invalid notification value: " << Qt::hex
                   << static_cast<int>(answer[1]);
        return false;
    }
    return true;
}

std::optional<types::DayOfWeek>
DayTimerNotification::optDecodeDayOfWeek(char dayOfWeekEncoded)
{
    if (dayOfWeekEncoded < 0x00 || dayOfWeekEncoded > 0x06) {
        qWarning() << Q_FUNC_INFO << "Answer has invalid day of week. value: "
                   << dayOfWeekEncoded;
        return {};
    }
    auto dayOfWeek = static_cast<types::DayOfWeek>(dayOfWeekEncoded);
    qDebug() << Q_FUNC_INFO << "dayOfWeek" << utility::enumToString(dayOfWeek);
    return {dayOfWeek};
}

std::optional<types::DayTimer>
DayTimerNotification::optDecodeDayTimer(const QByteArray &answer)
{
    std::vector<types::DayTimerEntry> dayTimerEntries;
    constexpr auto possibleEntriesCount = 7;
    dayTimerEntries.reserve(possibleEntriesCount);

    for (auto it = answer.begin() + 2; it != answer.end(); it += 2) {
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
            qWarning() << Q_FUNC_INFO
                       << "Valid types::DayTimerEntry:" << dayTimerEntry;
            dayTimerEntries.emplace_back(dayTimerEntry);
        }
    }

    types::DayTimer dayTimer{dayTimerEntries};

    if (!dayTimer.isValid()) {
        qWarning() << Q_FUNC_INFO << "Invalid types::DayTimer" << dayTimer;
        return {};
    }
    return {dayTimer};
}

double DayTimerNotification::decodeTemperature(char temperatureEncoded)
{
    auto temperature = static_cast<int>(temperatureEncoded) / 2.0;
    return temperature;
}

types::Time DayTimerNotification::decodeTime(char timeEncoded)
{
    uchar uTimeEncoded = static_cast<uchar>(timeEncoded);
    auto minutesFromMidnight = static_cast<int>(uTimeEncoded) * 10;
    auto hour = minutesFromMidnight / 60;
    auto minutes = minutesFromMidnight - (hour * 60);
    types::Time time{hour, minutes};
    return time;
}

} // namespace thermonator::eq3thermostat::answer
