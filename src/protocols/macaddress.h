#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <QString>

using namespace Qt;

class MACAddress
{
private:
    qint8* address;
public:
    MACAddress(qint8 address[8]);
    QString getAddressAsHexString() const {
        return QString::number(address[0], 16).toLower() + ":" + QString::number(address[1], 16).toLower() + ":" + QString::number(address[2], 16).toLower() + ":" + QString::number(address[3], 16).toLower() + ":" + QString::number(address[4], 16).toLower() + ":" + QString::number(address[5], 16).toLower() + ":" + QString::number(address[6], 16).toLower() + ":" + QString::number(address[7], 16).toLower();
    }
    qint8* getAddressAsArray() const {
        return address;
    }
};

#endif // MACADDRESS_H
