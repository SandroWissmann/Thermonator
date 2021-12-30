#include "StatusNotification.hpp"

#include "../../utility/Utility.hpp"

#include <QDebug>

#include <bitset>

namespace thermonator::eq3thermostat::answer {

StatusNotification::StatusNotification(QObject *parent) : QObject{parent}
{
}

void StatusNotification::decodeAnswer(const QByteArray &answer)
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

StatusNotification::Flags StatusNotification::decodeFlags(char flagsByte)
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

int StatusNotification::decodeValvePosition(char valvePositionByte)
{
    auto valvePosition = static_cast<int>(valvePositionByte);
    return valvePosition;
}

int StatusNotification::decodeUnknown(char unknownByte)
{
    auto unknown = static_cast<int>(unknownByte);
    return unknown;
}

double StatusNotification::decodeTargetTemperature(char targetTemperatureByte)
{
    auto targetTemperature = (static_cast<int>(targetTemperatureByte) / 2.0);
    return targetTemperature;
}

int StatusNotification::decodeDay(char dayByte)
{
    auto day = static_cast<int>(dayByte);
    return day;
}

int StatusNotification::decodeYear(char yearByte)
{
    auto year = static_cast<int>(yearByte) + 2000;
    return year;
}

int StatusNotification::decodeMonth(char monthByte)
{
    auto month = static_cast<int>(monthByte);
    return month;
}

StatusNotification::Time StatusNotification::decodeTime(char timeByte)
{
    Time time;
    time.hour = static_cast<int>(timeByte) / 2;
    time.minute = (static_cast<int>(timeByte) % 2) * 30;
    return time;
}

double
StatusNotification::decodeOpenWindowTemperature(char openWindowTemperatureByte)
{
    auto openWindowTemperature =
        (static_cast<int>(openWindowTemperatureByte) / 2.0);
    return openWindowTemperature;
}

int StatusNotification::decodeOpenWindowInterval(char openWindowIntervalByte)
{
    auto openWindowInterval = static_cast<int>(openWindowIntervalByte) * 5;
    return openWindowInterval;
}

double StatusNotification::decodeComfortTemperature(char comfortTemperatureByte)
{
    auto comfortTemperature = (static_cast<int>(comfortTemperatureByte) / 2.0);
    return comfortTemperature;
}

double StatusNotification::decodeEcoTemperature(char ecoTemperatureByte)
{
    auto ecoTemperature = (static_cast<int>(ecoTemperatureByte) / 2.0);
    return ecoTemperature;
}

double StatusNotification::decodeTemperatureOffset(char temperatureOffsetByte)
{
    auto temperatureOffset =
        (static_cast<int>(temperatureOffsetByte) - 7) / 2.0;
    return temperatureOffset;
}

} // namespace thermonator::eq3thermostat::answer
