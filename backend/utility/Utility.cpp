#include "Utility.hpp"

#include <algorithm>

namespace thermonator::utility {

QString toHexWithSpace(const QByteArray &byteArray)
{
    QString hex = byteArray.toHex();
    QString hexWithSpace;
    auto hexWithSpaceSize = hex.size() + hex.size() / 2;
    hexWithSpace.reserve(hexWithSpaceSize);

    for (auto i = 0; i < hex.size(); ++i) {
        if (i != 0 && i % 2 == 0) {
            hexWithSpace.append(' ');
        }
        hexWithSpace.append(hex[i]);
    }
    return hexWithSpace;
}

char hexToAscii(char hex)
{
    return char(hex - 0x30);
}

int encodeTemperature(double temperature)
{
    constexpr auto minTemperature = 5.0;
    constexpr auto maxTemperature = 29.5;

    temperature = std::clamp(temperature, minTemperature, maxTemperature);

    auto temperatureEncoded = static_cast<int>(temperature * 2);
    return temperatureEncoded;
}

} // namespace thermonator::utility
