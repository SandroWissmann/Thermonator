#include "SerialNumberNotificationData.hpp"

#include "../../utility/Utility.hpp"

#include <algorithm>

namespace thermonator::eq3thermostat::types {

SerialNumberNotificationData::SerialNumberNotificationData(
    unsigned char unknownByte1, const SerialNumber &serialNumber,
    unsigned char unknownByte14)
    : mUnknownByte1{unknownByte1}, mSerialNumber{serialNumber},
      mUnknownByte14{unknownByte14}
{
}

SerialNumberNotificationData
SerialNumberNotificationData::fromEncodedData(const QByteArray &data)
{
    qDebug() << Q_FUNC_INFO << "data:" << utility::toHexWithSpace(data);

    auto bytes = utility::toUChars(data);

    if (data.size() != 15) {
        qDebug() << Q_FUNC_INFO << "data has wrong size";
        return SerialNumberNotificationData{};
    }
    if (data.at(0) != 0x01) {
        qDebug() << Q_FUNC_INFO
                 << "first byte of data has wrong value: " << Qt::hex
                 << static_cast<int>(data.at(0));
        return SerialNumberNotificationData{};
    }

    auto unknownByte1 = static_cast<unsigned char>(data.at(1));

    std::array<unsigned char, 10> serialNumberBytes;
    std::copy_n(bytes.begin() + 4, 10, serialNumberBytes.begin());

    SerialNumber serialNumber{serialNumberBytes};
    if (!serialNumber.isValid()) {
        qDebug() << Q_FUNC_INFO
                 << "serial number is invalid. value:" << serialNumber;
        return SerialNumberNotificationData{};
    }

    auto unknownByte14 = static_cast<unsigned char>(data.at(14));

    SerialNumberNotificationData serialNumberNotificationData{
        unknownByte1, serialNumber, unknownByte14};
    return serialNumberNotificationData;
}

bool SerialNumberNotificationData::isValid() const
{
    if (!mSerialNumber.isValid()) {
        return false;
    }
    return true;
}

SerialNumber SerialNumberNotificationData::serialNumber() const
{
    return mSerialNumber;
}

unsigned char SerialNumberNotificationData::unknownByte1() const
{
    return mUnknownByte1;
}

unsigned char SerialNumberNotificationData::unknownByte14() const
{
    return mUnknownByte14;
}

QDebug
operator<<(QDebug debug,
           const SerialNumberNotificationData &serialNumberNotificationData)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "unknownByte1: " << Qt::hex
                    << static_cast<unsigned int>(
                           serialNumberNotificationData.unknownByte1())
                    << '\n'
                    << "serialNumber: "
                    << serialNumberNotificationData.serialNumber() << '\n'
                    << "unknownByte14: " << Qt::hex
                    << static_cast<unsigned int>(
                           serialNumberNotificationData.unknownByte14());

    return debug;
}

} // namespace thermonator::eq3thermostat::types
