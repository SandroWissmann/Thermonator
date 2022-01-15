#include "SerialNumberNotification.hpp"

#include "../../utility/Utility.hpp"

#include <algorithm>

namespace thermonator::eq3thermostat {

SerialNumberNotification::SerialNumberNotification(
    unsigned char unknownByte1, const SerialNumber &serialNumber,
    unsigned char unknownByte14)
    : mUnknownByte1{unknownByte1}, mSerialNumber{serialNumber},
      mUnknownByte14{unknownByte14}
{
}

SerialNumberNotification
SerialNumberNotification::fromEncodedData(const QByteArray &data)
{
    qDebug() << Q_FUNC_INFO << "data:" << utility::toHexWithSpace(data);

    auto bytes = utility::toUChars(data);

    if (data.size() != 15) {
        qDebug() << Q_FUNC_INFO << "data has wrong size";
        return SerialNumberNotification{};
    }
    if (data.at(0) != 0x01) {
        qDebug() << Q_FUNC_INFO
                 << "first byte of data has wrong value: " << Qt::hex
                 << static_cast<int>(data.at(0));
        return SerialNumberNotification{};
    }

    auto unknownByte1 = static_cast<unsigned char>(data.at(1));

    std::array<unsigned char, 10> serialNumberBytes;
    std::copy_n(bytes.begin() + 4, serialNumberBytes.size(),
                serialNumberBytes.begin());

    SerialNumber serialNumber{serialNumberBytes};
    if (!serialNumber.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "serial number is invalid. value:" << serialNumber;
        return SerialNumberNotification{};
    }

    auto unknownByte14 = static_cast<unsigned char>(data.at(14));

    SerialNumberNotification serialNumberNotification{
        unknownByte1, serialNumber, unknownByte14};
    return serialNumberNotification;
}

bool SerialNumberNotification::isValid() const
{
    if (!mSerialNumber.isValid()) {
        return false;
    }
    return true;
}

SerialNumber SerialNumberNotification::serialNumber() const
{
    return mSerialNumber;
}

unsigned char SerialNumberNotification::unknownByte1() const
{
    return mUnknownByte1;
}

unsigned char SerialNumberNotification::unknownByte14() const
{
    return mUnknownByte14;
}

} // namespace thermonator::eq3thermostat
