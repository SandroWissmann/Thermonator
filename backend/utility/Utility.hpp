#ifndef THERMONATOR_UTILITY_UTILITY_HPP
#define THERMONATOR_UTILITY_UTILITY_HPP

#include <QByteArray>
#include <QString>

namespace thermonator::utility {

// Returns string with Hex values separated bye bytes
// e.g. 01 92 00 00 82 75 81 60 67 64 66 63 67 64 ae
QString toHexWithSpace(const QByteArray &byteArray);

char hexToAscii(char hex);

std::vector<unsigned char> toUChars(const QByteArray &byteArray);

} // namespace thermonator::utility

#endif
