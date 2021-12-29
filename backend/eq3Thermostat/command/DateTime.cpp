#include "DateTime.hpp"

#include "../../utility/Utility.hpp"

#include <QDateTime>
#include <QDebug>

#include <bitset>

namespace thermonator::eq3thermostat::command {

DateTime::DateTime(QObject *parent) : QObject{parent}
{
}

void DateTime::encodeCommand()
{
    qDebug() << Q_FUNC_INFO;
    auto currentDateTime = QDateTime::currentDateTime();

    qDebug() << Q_FUNC_INFO << "currentDateTime:" << currentDateTime;
    auto currentYear = currentDateTime.toString("yy").toInt();
    auto currentMonth = currentDateTime.toString("MM").toInt();
    auto currentDay = currentDateTime.toString("dd").toInt();
    auto currentHour = currentDateTime.toString("hh").toInt();
    auto currentMinute = currentDateTime.toString("mm").toInt();
    auto currentSecond = currentDateTime.toString("ss").toInt();

    QByteArray command;
    constexpr auto bytesCount = 15;
    command.reserve(bytesCount);

    command.append(QByteArray::fromHex("03"));
    command.append(currentYear);
    command.append(currentMonth);
    command.append(currentDay);
    command.append(currentHour);
    command.append(currentMinute);
    command.append(currentSecond);

    command.append(QByteArray::fromHex("0000000000000000"));

    qDebug() << Q_FUNC_INFO << "command:" << utility::toHexWithSpace(command);
    emit commandEncoded(command);
}

void DateTime::decodeAnswer(const QByteArray &answer)
{
    qDebug() << Q_FUNC_INFO << "answer:" << utility::toHexWithSpace(answer);

    // postion 0 and 1 are fixed values not used
    auto flags = decodeFlags(answer.at(2));
    qDebug() << Q_FUNC_INFO << "autoModeEnabled:" << flags.autoModeEnabled;
    qDebug() << Q_FUNC_INFO << "manualModeEnabled:" << flags.manualModeEnabled;
    qDebug() << Q_FUNC_INFO
             << "vacationModeEnabled:" << flags.vacationModeEnabled;
    qDebug() << Q_FUNC_INFO << "boostEnabled:" << flags.boostEnabled;
    qDebug() << Q_FUNC_INFO
             << "daylightSummerTimeEnabled:" << flags.daylightSummerTimeEnabled;
    qDebug() << Q_FUNC_INFO
             << "openWindowModeEnabled:" << flags.openWindowModeEnabled;
    qDebug() << Q_FUNC_INFO
             << "hardwareButtonsLocked:" << flags.hardwareButtonsLocked;
    qDebug() << Q_FUNC_INFO << "unknownEnabled:" << flags.unknownEnabled;
    qDebug() << Q_FUNC_INFO << "lowBatteryEnabled:" << flags.lowBatteryEnabled;

    auto valvePosition = decodeValvePosition(answer.at(3));
    qDebug() << Q_FUNC_INFO << "valvePosition:" << valvePosition;

    auto unknown = decodeUnknown(answer.at(4));
    qDebug() << Q_FUNC_INFO << "unknown:" << unknown;

    auto targetTemperature = decodeTargetTemperature(answer.at(5));
    qDebug() << Q_FUNC_INFO << "targetTemperature:" << targetTemperature;

    auto day = decodeDay(answer.at(6));
    qDebug() << Q_FUNC_INFO << "day:" << day;

    auto year = decodeYear(answer.at(7));
    qDebug() << Q_FUNC_INFO << "year:" << year;

    auto month = decodeMonth(answer.at(8));
    qDebug() << Q_FUNC_INFO << "month:" << month;

    auto time = decodeTime(answer.at(9));
    qDebug() << Q_FUNC_INFO << "hour:" << time.hour;
    qDebug() << Q_FUNC_INFO << "minute:" << time.minute;

    auto openWindowTemperature = decodeOpenWindowTemperature(answer.at(10));
    qDebug() << Q_FUNC_INFO
             << "openWindowTemperature:" << openWindowTemperature;

    auto openWindowInterval = decodeOpenWindowInterval(answer.at(11));
    qDebug() << Q_FUNC_INFO << "openWindowInterval:" << openWindowInterval;

    auto comfortTemperature = decodeComfortTemperature(answer.at(12));
    qDebug() << Q_FUNC_INFO << "comfortTemperature:" << comfortTemperature;

    auto ecoTemperature = decodeEcoTemperature(answer.at(13));
    qDebug() << Q_FUNC_INFO << "ecoTemperature:" << ecoTemperature;

    auto temperatureOffset = decodeTemperatureOffset(answer.at(14));
    qDebug() << Q_FUNC_INFO << "temperatureOffset:" << temperatureOffset;

    emit answerDecoded(temperatureOffset, ecoTemperature, comfortTemperature,
                       openWindowInterval, openWindowTemperature, time.minute,
                       time.hour, day, month, year, targetTemperature,
                       valvePosition, flags.autoModeEnabled,
                       flags.manualModeEnabled, flags.vacationModeEnabled,
                       flags.boostEnabled, flags.daylightSummerTimeEnabled,
                       flags.openWindowModeEnabled, flags.hardwareButtonsLocked,
                       flags.unknownEnabled, flags.lowBatteryEnabled);
}

DateTime::Flags DateTime::decodeFlags(char flagsByte)
{
    auto flagsUInt = static_cast<unsigned long long>(flagsByte);

    std::bitset<8> flagsBitset{flagsUInt};
    Flags flags;
    if (flagsBitset[0] == true) {
        flags.autoModeEnabled = false;
        flags.manualModeEnabled = true;
    }
    else {
        flags.autoModeEnabled = true;
        flags.manualModeEnabled = false;
    }
    flags.vacationModeEnabled = flagsBitset[1];
    flags.boostEnabled = flagsBitset[2];
    flags.daylightSummerTimeEnabled = flagsBitset[3];
    flags.openWindowModeEnabled = flagsBitset[4];
    flags.hardwareButtonsLocked = flagsBitset[5];
    flags.unknownEnabled = flagsBitset[6];
    flags.lowBatteryEnabled = flagsBitset[7];

    return flags;
}

int DateTime::decodeValvePosition(char valvePositionByte)
{
    auto valvePosition = static_cast<int>(valvePositionByte);
    return valvePosition;
}

int DateTime::decodeUnknown(char unknownByte)
{
    auto unknown = static_cast<int>(unknownByte);
    return unknown;
}

double DateTime::decodeTargetTemperature(char targetTemperatureByte)
{
    auto targetTemperature = (static_cast<int>(targetTemperatureByte) / 2.0);
    return targetTemperature;
}

int DateTime::decodeDay(char dayByte)
{
    auto day = static_cast<int>(dayByte);
    return day;
}

int DateTime::decodeYear(char yearByte)
{
    auto year = static_cast<int>(yearByte) + 2000;
    return year;
}

int DateTime::decodeMonth(char monthByte)
{
    auto month = static_cast<int>(monthByte);
    return month;
}

DateTime::Time DateTime::decodeTime(char timeByte)
{
    Time time;
    time.hour = static_cast<int>(timeByte) / 2;
    time.minute = (static_cast<int>(timeByte) % 2) * 30;
    return time;
}

double DateTime::decodeOpenWindowTemperature(char openWindowTemperatureByte)
{
    auto openWindowTemperature =
        (static_cast<int>(openWindowTemperatureByte) / 2.0);
    return openWindowTemperature;
}

int DateTime::decodeOpenWindowInterval(char openWindowIntervalByte)
{
    auto openWindowInterval = static_cast<int>(openWindowIntervalByte) * 5;
    return openWindowInterval;
}

double DateTime::decodeComfortTemperature(char comfortTemperatureByte)
{
    auto comfortTemperature = (static_cast<int>(comfortTemperatureByte) / 2.0);
    return comfortTemperature;
}

double DateTime::decodeEcoTemperature(char ecoTemperatureByte)
{
    auto ecoTemperature = (static_cast<int>(ecoTemperatureByte) / 2.0);
    return ecoTemperature;
}

double DateTime::decodeTemperatureOffset(char temperatureOffsetByte)
{
    auto temperatureOffset =
        (static_cast<int>(temperatureOffsetByte) - 7) / 2.0;
    return temperatureOffset;
}

} // namespace thermonator::eq3thermostat::command
