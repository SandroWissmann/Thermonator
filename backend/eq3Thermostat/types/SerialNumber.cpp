#include "SerialNumber.hpp"

#include "AsciiSign.hpp"

#include <algorithm>

namespace thermonator::eq3thermostat {

SerialNumber::SerialNumber(const std::array<unsigned char, 10> &bytes)
    : mValue{decodeBytes(bytes)}, mIsValid{true}
{
}

bool SerialNumber::isValid() const
{
    return mIsValid;
}

QString SerialNumber::value() const
{
    return mValue;
}

QString SerialNumber::decodeBytes(const std::array<unsigned char, 10> &bytes)
{
    QString serialNumber;
    serialNumber.reserve(bytes.size());

    for (const auto &byte : bytes) {
        AsciiSign asciiSign{byte};
        serialNumber.push_back(QChar{asciiSign.value()});
    }
    return serialNumber;
}

QDebug operator<<(QDebug debug, const SerialNumber &serialNumber)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << serialNumber.value();

    return debug;
}

} // namespace thermonator::eq3thermostat
