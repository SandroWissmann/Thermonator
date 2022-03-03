#ifndef THERMONATOR_GUI_SCANNEDDEVICESMODEL_HPP
#define THERMONATOR_GUI_SCANNEDDEVICESMODEL_HPP

#include "ScannedDevice.hpp"

#include <QAbstractListModel>
#include <QObject>
#include <QString>

#include <vector>

class QBluetoothDeviceInfo;

namespace thermonator::gui {

class ScannedDevicesModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum class DisplayRole {
        macAddress = Qt::UserRole + 1,
        // only one device can be selected at a time
        selected,
        delegateBackgroundColor
    };

    explicit ScannedDevicesModel(QObject *parent = nullptr);

    ScannedDevicesModel(const ScannedDevicesModel &) = delete;
    ScannedDevicesModel &operator=(const ScannedDevicesModel &) = delete;
    ScannedDevicesModel(ScannedDevicesModel &&) = delete;
    ScannedDevicesModel &operator=(ScannedDevicesModel &&) = delete;
    ~ScannedDevicesModel() = default;

    int rowCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addDevice(const QBluetoothDeviceInfo &deviceInfo);
    void resetDevices();

    bool selectDevice(const QString &macAddress);

private:
    bool indexInRange(const QModelIndex &index) const;

    QVariant dataMacAddress(int row) const;
    QVariant dataIsSelected(int row) const;
    QVariant dataDelegateBackgroundColor(int row) const;

    bool macAddressExists(const QString &macAddress) const;

    std::vector<ScannedDevice>::const_iterator
    getDeviceItWithMacAddress(const QString &macAddress) const;

    std::vector<ScannedDevice>::iterator
    getDeviceItWithMacAddress(const QString &macAddress);

    void updateSelectRelatedRoles(int pos);

    std::vector<ScannedDevice> mScannedDevices;
};
} // namespace thermonator::gui

Q_DECLARE_METATYPE(thermonator::gui::ScannedDevicesModel *)

#endif
