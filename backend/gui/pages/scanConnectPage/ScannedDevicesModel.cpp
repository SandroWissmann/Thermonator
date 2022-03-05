#include "ScannedDevicesModel.hpp"

#include <QBluetoothAddress>
#include <QBluetoothDeviceInfo>
#include <QColor>
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
    return static_cast<int>(mScannedDevices.size());
}

QVariant ScannedDevicesModel::data(const QModelIndex &index, int role) const
{
    if (!indexInRange(index)) {
        return QVariant{};
    }

    auto row = index.row();

    switch (static_cast<DisplayRole>(role)) {
    case DisplayRole::macAddress:
        return dataMacAddress(row);
    case DisplayRole::selected:
        return dataIsSelected(row);
    case DisplayRole::delegateBackgroundColor:
        return dataDelegateBackgroundColor(row);
    }
    return QVariant{};
}

QHash<int, QByteArray> ScannedDevicesModel::roleNames() const
{
    return QHash<int, QByteArray>{
        {static_cast<int>(DisplayRole::macAddress), "macAddress"},
        {static_cast<int>(DisplayRole::selected), "selected"},
        {static_cast<int>(DisplayRole::delegateBackgroundColor),
         "delegateBackgroundColor"}};
}

void ScannedDevicesModel::addDevice(const QBluetoothDeviceInfo &deviceInfo)
{
    auto macAddress = deviceInfo.address().toString();

    if (macAddressExists(macAddress)) {
        qWarning() << Q_FUNC_INFO << "Mac address exists: " << macAddress;
        return;
    }

    qDebug() << Q_FUNC_INFO << "New device with mac address: " << macAddress;

    auto pos = mScannedDevices.size();
    ScannedDevice scannedDevice{deviceInfo};
    beginInsertRows(QModelIndex{}, pos, pos);
    mScannedDevices.emplace_back(scannedDevice);
    endInsertRows();
}

bool ScannedDevicesModel::selectDevice(const QString &macAddress)
{
    auto existingDeviceIt = getDeviceItWithMacAddress(macAddress);

    if (existingDeviceIt == mScannedDevices.end()) {
        qWarning() << Q_FUNC_INFO
                   << "Mac address does not exists: " << macAddress;
        return false;
    }

    for (auto i = 0; i < mScannedDevices.size(); ++i) {
        if (!mScannedDevices[i].isSelected()) {
            continue;
        }
        mScannedDevices[i].setIsSelected(false);

        updateSelectRelatedRoles(i);
    }

    existingDeviceIt->setIsSelected(true);

    auto pos = std::distance(mScannedDevices.begin(), existingDeviceIt);
    updateSelectRelatedRoles(pos);
    return true;
}

void ScannedDevicesModel::resetDevices()
{
    beginResetModel();
    mScannedDevices.clear();
    endResetModel();
}

bool ScannedDevicesModel::indexInRange(const QModelIndex &index) const
{
    auto indexInRange = index.row() >= 0 &&
                        index.row() < static_cast<int>(mScannedDevices.size());
    return indexInRange;
}

QVariant ScannedDevicesModel::dataMacAddress(int row) const
{
    return mScannedDevices.at(row).macAddress();
}

QVariant ScannedDevicesModel::dataIsSelected(int row) const
{
    return mScannedDevices.at(row).isSelected();
}

QVariant ScannedDevicesModel::dataDelegateBackgroundColor(int row) const
{
    auto isSelected = mScannedDevices.at(row).isSelected();
    if (isSelected) {
        return QColor{"orange"};
    }
    return QColor{"white"};
}

bool ScannedDevicesModel::macAddressExists(const QString &macAddress) const
{
    auto deviceInfoIt = getDeviceItWithMacAddress(macAddress);

    if (deviceInfoIt != mScannedDevices.end()) {
        return true;
    }
    return false;
}

std::vector<ScannedDevice>::const_iterator
ScannedDevicesModel::getDeviceItWithMacAddress(const QString &macAddress) const
{
    auto deviceInfoIt =
        std::find_if(mScannedDevices.begin(), mScannedDevices.end(),
                     [macAddress](const auto &scannedDevice) {
                         return macAddress == scannedDevice.macAddress();
                     });
    return deviceInfoIt;
}

std::vector<ScannedDevice>::iterator
ScannedDevicesModel::getDeviceItWithMacAddress(const QString &macAddress)
{
    auto deviceInfoIt =
        std::find_if(mScannedDevices.begin(), mScannedDevices.end(),
                     [macAddress](const auto &scannedDevice) {
                         return macAddress == scannedDevice.macAddress();
                     });
    return deviceInfoIt;
}

void ScannedDevicesModel::updateSelectRelatedRoles(int pos)
{
    auto indexPos = index(pos, 0);
    emit dataChanged(indexPos, indexPos,
                     {static_cast<int>(DisplayRole::selected),
                      static_cast<int>(DisplayRole::delegateBackgroundColor)});
}

} // namespace thermonator::gui
