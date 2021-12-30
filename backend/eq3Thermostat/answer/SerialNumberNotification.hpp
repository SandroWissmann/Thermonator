#ifndef THERMONATOR_EQ3THERMOSTAT_ANSWER_SERIALNUMBER_HPP
#define THERMONATOR_EQ3THERMOSTAT_ANSWER_SERIALNUMBER_HPP

/*
Answer:

0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 Bytes

01 6e 00 00 7f 75 81 60 66 61 66 64 61 64 9b Values in hex
             |  |  |  |  |  |  |  |  |  |
             |  |  |  |  |  |  |  |  |  |
             O  E  Q  0  6  1  6  4  1  4

Byte 15: Unknown
Byte 4 to 13: Serial Number in ascii, calculate (hex - 0x30)
Byte 3: Empty / Unknown
Byte 2: Empty / Unknown
Byte 1: Unknown
Byte 0: Unknown

For this example the bytes are decoded to this:

Byte 15: Unknown
Byte 4 to 13: 7f 75 81 60 66 61 66 64 61 64 -> OEQ0616414
Byte 3: Empty / Unknown
Byte 2: Empty / Unknown
Byte 1: Unknown
Byte 0: Unknown

The serial number can be found behind the batteris of the thermostate.

*/

#include <QObject>

namespace thermonator::eq3thermostat::answer {

class SerialNumberNotification : public QObject {
    Q_OBJECT
public:
    explicit SerialNumberNotification(QObject *parent = nullptr);

    ~SerialNumberNotification() = default;

    // Request decoding the answer
    // triggers signal answerDecoded
    void decodeAnswer(const QByteArray &answer);

signals:
    void answerDecoded(const QString &serialNumber);
};

} // namespace thermonator::eq3thermostat::answer

#endif
