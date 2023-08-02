#include "macaddress.h"

MACAddress::MACAddress(const QVector<quint8> &address) : address(address)
{}


QString MACAddress::getAddressAsString() const {
    return QString::number(static_cast<int>(address[0]), 16).toLower() + ":" + QString::number(static_cast<int>(address[1]), 16).toLower() + ":" + QString::number(static_cast<int>(address[2]), 16).toLower() + ":" + QString::number(static_cast<int>(address[3]), 16).toLower() + ":" + QString::number(static_cast<int>(address[4]), 16).toLower() + ":" + QString::number(static_cast<int>(address[5]), 16).toLower() + ":" + QString::number(static_cast<int>(address[6]), 16).toLower() + ":" + QString::number(static_cast<int>(address[7]), 16).toLower();
}

QVector<quint8> MACAddress::getAddressAsArray() const {
    return address;
}

quint64 MACAddress::getAddressAsInt() const {
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

MACAddress MACAddress::getRandomAddress() {
    static QRandomGenerator* generator = new QRandomGenerator(2183193);
    QVector<quint8> addressArray;
    for (int i = 0; i < 8; i++) {
        addressArray.append(generator->generate() % 256);
    }
    return MACAddress(addressArray);
}
