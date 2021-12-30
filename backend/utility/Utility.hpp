#ifndef THERMONATOR_UTILITY_UTILITY_HPP
#define THERMONATOR_UTILITY_UTILITY_HPP

#include <QByteArray>
#include <QString>

namespace thermonator::utility {

// Returns string with Hex values separated bye bytes
// e.g. 01 92 00 00 82 75 81 60 67 64 66 63 67 64 ae
QString toHexWithSpace(const QByteArray &byteArray);

char hexToAscii(char hex);

// Input temperature gets clamped to the range 5.0 - 29.5.
// Input is rounded to be in 0.5 Steps
// Output encoded = input * 2
int encodeTemperature(double temperature);

} // namespace thermonator::utility

#endif
