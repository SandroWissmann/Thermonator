#ifndef THERMONATOR_EQ3THERMOSTAT_STATUS_HPP
#define THERMONATOR_EQ3THERMOSTAT_STATUS_HPP

#include "DateTime.hpp"
#include "OpenWindowInterval.hpp"
#include "StatusFlags.hpp"
#include "Temperature.hpp"
#include "TemperatureOffset.hpp"
#include "UnknownStatusByte.hpp"
#include "ValvePosition.hpp"
#include "WeekTimer.hpp"

namespace thermonator::eq3thermostat {

class Status {
public:
    Status() = default;

    Status(StatusFlags statusFlags, ValvePosition valvePosition,
           UnknownStatusByte unknownStatusByte, Temperature targetTemperature,
           DateTime holidayEndDateTime, Temperature openWindowTemperature,
           OpenWindowInterval openWindowInterval,
           Temperature comfortTemperature, Temperature ecoTemperature,
           TemperatureOffset temperatureOffset);

    static Status fromEncodedBytes(const std::array<unsigned char, 13> &bytes);

    bool isValid() const;

    StatusFlags statusFlags() const;
    ValvePosition valvePosition() const;
    UnknownStatusByte unknownStatusByte() const;
    Temperature targetTemperature() const;
    DateTime holidayEndDateTime() const;
    Temperature openWindowTemperature() const;
    OpenWindowInterval openWindowInterval() const;
    Temperature comfortTemperature() const;
    Temperature ecoTemperature() const;
    TemperatureOffset temperatureOffset() const;

private:
    StatusFlags mStatusFlags;
    ValvePosition mValvePosition;
    UnknownStatusByte mUnknownStatusByte;
    Temperature mTargetTemperature;
    DateTime mHolidayEndDateTime;
    Temperature mOpenWindowTemperature;
    OpenWindowInterval mOpenWindowInterval;
    Temperature mComfortTemperature;
    Temperature mEcoTemperature;
    TemperatureOffset mTemperatureOffset;
};

inline bool operator==(const Status &lhs, const Status &rhs)
{
    if (lhs.statusFlags() != rhs.statusFlags()) {
        return false;
    }
    if (lhs.valvePosition() != rhs.valvePosition()) {
        return false;
    }
    if (lhs.unknownStatusByte() != rhs.unknownStatusByte()) {
        return false;
    }
    if (lhs.targetTemperature() != rhs.targetTemperature()) {
        return false;
    }
    if (lhs.holidayEndDateTime() != rhs.holidayEndDateTime()) {
        return false;
    }
    if (lhs.openWindowTemperature() != rhs.openWindowTemperature()) {
        return false;
    }
    if (lhs.openWindowInterval() != rhs.openWindowInterval()) {
        return false;
    }
    if (lhs.comfortTemperature() != rhs.comfortTemperature()) {
        return false;
    }
    if (lhs.ecoTemperature() != rhs.ecoTemperature()) {
        return false;
    }
    if (lhs.temperatureOffset() != rhs.temperatureOffset()) {
        return false;
    }
    return true;
}

inline bool operator!=(const Status &lhs, const Status &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const Status &status);

} // namespace thermonator::eq3thermostat

#endif
