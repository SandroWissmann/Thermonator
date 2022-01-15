#include "StatusNotification.hpp"

#include "../../utility/Utility.hpp"

#include <algorithm>
#include <array>

namespace thermonator::eq3thermostat {

StatusNotification::StatusNotification(const Status &status)

    : mStatus{status}
{
}

StatusNotification StatusNotification::fromEncodedData(const QByteArray &data)
{
    qDebug() << Q_FUNC_INFO << "data:" << utility::toHexWithSpace(data);

    auto bytes = utility::toUChars(data);

    if (data.size() != 15) {
        qDebug() << Q_FUNC_INFO << "data has wrong size";
        return StatusNotification{};
    }
    if (data.at(0) != 0x02) {
        qDebug() << Q_FUNC_INFO
                 << "first byte of data has wrong value: " << Qt::hex
                 << static_cast<int>(data.at(0));
        return StatusNotification{};
    }
    if (data.at(1) != 0x01) {
        qDebug() << Q_FUNC_INFO
                 << "second byte of data has wrong value: " << Qt::hex
                 << static_cast<int>(data.at(1));
        return StatusNotification{};
    }

    std::array<unsigned char, 13> statusBytes;
    std::copy_n(bytes.begin() + 2, statusBytes.size(), statusBytes.begin());
    auto status = Status::fromEncodedBytes(statusBytes);

    if (!status.isValid()) {
        qDebug() << Q_FUNC_INFO << "status is invalid. value:" << status;
        return StatusNotification{};
    }

    StatusNotification statusNotification{status};
    return statusNotification;
}

bool StatusNotification::isValid() const
{
    if (!mStatus.isValid()) {
        return false;
    }
    return true;
}

Status StatusNotification::status() const
{
    return mStatus;
}

} // namespace thermonator::eq3thermostat
