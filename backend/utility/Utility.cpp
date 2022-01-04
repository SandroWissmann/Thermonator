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

std::vector<unsigned char> toUChars(const QByteArray &byteArray)
{
    std::vector<unsigned char> charArray;
    charArray.reserve(charArray.size());

    for (const auto &byte : byteArray) {
        charArray.emplace_back(static_cast<unsigned char>(byte));
    }
    return charArray;
}

} // namespace thermonator::utility
