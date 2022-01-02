#ifndef THERMONATOR_EQ3THERMOSTAT_TYPES_STATUSFLAGS_HPP
#define THERMONATOR_EQ3THERMOSTAT_TYPES_STATUSFLAGS_HPP

#include <QDebug>

#include <bitset>

namespace thermonator::eq3thermostat::types {

/*
Status Notification Byte 2 flags:

Bit 0 is not set (mask 0x00) -> auto mode on
Bit 0 is set (mask 0x01) -> manual mode on
Bit 1 is set (mask 0x02) -> vacation mode on
Bit 2 is set (mask 0x04) -> boost on
Bit 3 is set (mask 0x08) -> daylightSummerTime (dst) on
Bit 4 is set (mask 0x10) -> open window detected
Bit 5 is set (mask 0x20) -> hardware buttons locked
Bit 6 is set (mask 0x40) -> unknown or unused?
Bit 7 is set (mask 0x80) -> indicates low battery

*/

class StatusFlags {
public:
    StatusFlags() = default;
    explicit StatusFlags(unsigned char byte);

    bool autoModeEnabled() const;
    bool manualModeEnabled() const;
    bool vacationModeEnabled() const;
    bool boostEnabled() const;
    bool daylightSummerTimeEnabled() const;
    bool openWindowModeEnabled() const;
    bool hardwareButtonsLocked() const;
    bool unknownEnabled() const;
    bool lowBatteryEnabled() const;

private:
    std::bitset<8> mBitset;
};

inline bool operator==(const StatusFlags &lhs, const StatusFlags &rhs)
{
    if (lhs.autoModeEnabled() != rhs.autoModeEnabled()) {
        return false;
    }
    if (lhs.vacationModeEnabled() != rhs.vacationModeEnabled()) {
        return false;
    }
    if (lhs.boostEnabled() != rhs.boostEnabled()) {
        return false;
    }
    if (lhs.daylightSummerTimeEnabled() != rhs.daylightSummerTimeEnabled()) {
        return false;
    }
    if (lhs.openWindowModeEnabled() != rhs.openWindowModeEnabled()) {
        return false;
    }
    if (lhs.hardwareButtonsLocked() != rhs.hardwareButtonsLocked()) {
        return false;
    }
    if (lhs.unknownEnabled() != rhs.unknownEnabled()) {
        return false;
    }
    if (lhs.lowBatteryEnabled() != rhs.lowBatteryEnabled()) {
        return false;
    }
    return true;
}

inline bool operator!=(const StatusFlags &lhs, const StatusFlags &rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const StatusFlags &statusFlags);

} // namespace thermonator::eq3thermostat::types

#endif
