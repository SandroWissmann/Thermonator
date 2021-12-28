#ifndef THERMONATOR_EQ3THERMOSTAT_EQ3THERMOSTAT_HPP
#define THERMONATOR_EQ3THERMOSTAT_EQ3THERMOSTAT_HPP

#include <QObject>
#include <QString>

namespace thermonator::eq3thermostat {

class Eq3Thermostat : public QObject {
    Q_OBJECT
    Q_PROPERTY(
        QString serialNumber READ serialNumber NOTIFY serialNumberChanged)
public:
    explicit Eq3Thermostat(QObject *parent = nullptr);

    ~Eq3Thermostat() = default;

    QString serialNumber() const;

public slots:
    void onSetSerialNumber(const QString &serialNumber);

signals:
    void serialNumberChanged();

private:
    QString mSerialNumber;
};

} // namespace thermonator::eq3thermostat

#endif
