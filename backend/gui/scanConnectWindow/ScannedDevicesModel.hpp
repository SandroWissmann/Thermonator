#ifndef THERMONATOR_GUI_SCANNEDDEVICESMODEL_HPP
#define THERMONATOR_GUI_SCANNEDDEVICESMODEL_HPP

#include <QAbstractListModel>
#include <QBluetoothDeviceInfo>
#include <QObject>
#include <QString>

#include <vector>

namespace thermonator::gui {

class ScannedDevicesModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum class DisplayRole { macAddress = Qt::UserRole + 1 };

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

private:
    bool indexInRange(const QModelIndex &index) const;

    QVariant dataMacAddress() const;

    std::vector<QBluetoothDeviceInfo> mDeviceInfos;
};
} // namespace thermonator::gui

Q_DECLARE_METATYPE(thermonator::gui::ScannedDevicesModel *)

#endif
