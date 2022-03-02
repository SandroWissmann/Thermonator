#include "ScannedDevicesModel.hpp"

#include <QBluetoothAddress>
#include <QDebug>

#include <algorithm>

namespace thermonator::gui {

ScannedDevicesModel::ScannedDevicesModel(QObject *parent)
    : QAbstractListModel{parent}
{
    qRegisterMetaType<thermonator::gui::ScannedDevicesModel *>();
}

int ScannedDevicesModel::rowCount(const QModelIndex &parent) const
{
    return static_cast<int>(mDeviceInfos.size());
}

QVariant ScannedDevicesModel::data(const QModelIndex &index, int role) const
{
    if (!indexInRange(index)) {
        return QVariant{};
    }

    auto row = index.row();

    switch (static_cast<DisplayRole>(role)) {
    case DisplayRole::macAddress:
        return mDeviceInfos.at(row).address().toString();
    }
    return QVariant{};
}

QHash<int, QByteArray> ScannedDevicesModel::roleNames() const
{
    return QHash<int, QByteArray>{
        {static_cast<int>(DisplayRole::macAddress), "macAddress"}};
}

void ScannedDevicesModel::addDevice(const QBluetoothDeviceInfo &deviceInfo)
{
    auto deviceInfoIt =
        std::find(mDeviceInfos.begin(), mDeviceInfos.end(), deviceInfo);

    if (deviceInfoIt != mDeviceInfos.end()) {
        return;
    }

    qDebug() << Q_FUNC_INFO
             << "New device with mac address: " << deviceInfo.address();

    mDeviceInfos.emplace_back(deviceInfo);

    auto row = mDeviceInfos.size() - 1;
    auto index = createIndex(row, 0);
    emit dataChanged(index, index, {static_cast<int>(DisplayRole::macAddress)});
}

void ScannedDevicesModel::resetDevices()
{
    beginResetModel();
    mDeviceInfos.clear();
    endResetModel();
}

bool ScannedDevicesModel::indexInRange(const QModelIndex &index) const
{
    auto indexInRange =
        index.row() >= 0 && index.row() < static_cast<int>(mDeviceInfos.size());
    return indexInRange;
}

} // namespace thermonator::gui
