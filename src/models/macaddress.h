#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <QString>
#include <QRandomGenerator>

using namespace Qt;

class MACAddress
{
private:
    quint8* address;
public:
    MACAddress(quint8 *address) : address(address)
    {}

    QString getAddressAsString() const {
        return QString::number(address[0], 16).toLower() + ":" + QString::number(address[1], 16).toLower() + ":" + QString::number(address[2], 16).toLower() + ":" + QString::number(address[3], 16).toLower() + ":" + QString::number(address[4], 16).toLower() + ":" + QString::number(address[5], 16).toLower() + ":" + QString::number(address[6], 16).toLower() + ":" + QString::number(address[7], 16).toLower();
    }
    quint8* getAddressAsArray() const {
        return address;
    }
    quint64 getAddressAsInt() const {
        quint64 returnInt = address[7];
        returnInt = (returnInt << 8) + address[6];
        returnInt = (returnInt << 8) + address[5];
        returnInt = (returnInt << 8) + address[4];
        returnInt = (returnInt << 8) + address[3];
        returnInt = (returnInt << 8) + address[2];
        returnInt = (returnInt << 8) + address[1];
        returnInt = (returnInt << 8) + address[0];
        return returnInt;
    }

    static MACAddress getRandomAddress() {
        quint8* addressArray = new quint8[8];
        QRandomGenerator randomGenerator;
        for (int i = 0; i < 8; i++) {
            addressArray[i] = randomGenerator.generate() % 256;
        }
        return MACAddress(addressArray);
    }
};



#endif // MACADDRESS_H
