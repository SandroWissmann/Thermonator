#include "StatusFlags.hpp"

namespace thermonator::eq3thermostat::types {

StatusFlags::StatusFlags(unsigned char byte)
    : mBitset{static_cast<unsigned int>(byte)}
{
}

bool StatusFlags::autoModeEnabled() const
{
    return !manualModeEnabled();
}

bool StatusFlags::manualModeEnabled() const
{
    return mBitset[0];
}

bool StatusFlags::vacationModeEnabled() const
{
    return mBitset[1];
}

bool StatusFlags::boostEnabled() const
{
    return mBitset[2];
}

bool StatusFlags::daylightSummerTimeEnabled() const
{
    return mBitset[3];
}

bool StatusFlags::openWindowModeEnabled() const
{
    return mBitset[4];
}

bool StatusFlags::hardwareButtonsLocked() const
{
    return mBitset[5];
}

bool StatusFlags::unknownEnabled() const
{
    return mBitset[6];
}

bool StatusFlags::lowBatteryEnabled() const
{
    return mBitset[7];
}

QDebug operator<<(QDebug debug, const StatusFlags &statusFlags)
{
    QDebugStateSaver saver(debug);

    debug.nospace()
        << '\n'
        << "autoModeEnabled: " << statusFlags.autoModeEnabled() << '\n'
        << "manualModeEnabled: " << statusFlags.manualModeEnabled() << '\n'
        << "vacationModeEnabled: " << statusFlags.vacationModeEnabled() << '\n'
        << "boostEnabled: " << statusFlags.boostEnabled() << '\n'
        << "daylightSummerTimeEnabled: "
        << statusFlags.daylightSummerTimeEnabled() << '\n'
        << "openWindowModeEnabled: " << statusFlags.openWindowModeEnabled()
        << '\n'
        << "hardwareButtonsLocked: " << statusFlags.hardwareButtonsLocked()
        << '\n'
        << "unknownEnabled: " << statusFlags.unknownEnabled() << '\n'
        << "lowBatteryEnabled: " << statusFlags.lowBatteryEnabled();

    return debug;
}

} // namespace thermonator::eq3thermostat::types
