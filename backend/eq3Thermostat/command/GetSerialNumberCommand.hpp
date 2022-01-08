#ifndef THERMONATOR_EQ3THERMOSTAT_GETSERIALNUMBERCOMMAND_HPP
#define THERMONATOR_EQ3THERMOSTAT_GETSERIALNUMBERCOMMAND_HPP

/*
Command:

0   Bytes

00  Values in hex


Byte 0: request command "00"

*/

#include <QByteArray>

namespace thermonator::eq3thermostat {

class GetSerialNumberCommand {
public:
    GetSerialNumberCommand();

    QByteArray encoded() const;

private:
    static QByteArray encode();

    QByteArray mCommand{};
};

QDebug operator<<(QDebug debug,
                  const GetSerialNumberCommand &getSerialNumberCommand);

} // namespace thermonator::eq3thermostat

#endif
