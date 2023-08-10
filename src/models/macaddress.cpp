#include "macaddress.h"

MACAddress::MACAddress(const QVector<quint8> &address) : address(address)
{}

MACAddress::MACAddress(){
    address << 0 << 0 << 0 << 0 << 0 << 0;
}


QString MACAddress::toString() const {
    return QString::number(static_cast<int>(address[0]), 16).toLower() + ":" + QString::number(static_cast<int>(address[1]), 16).toLower() + ":" + QString::number(static_cast<int>(address[2]), 16).toLower() + ":" + QString::number(static_cast<int>(address[3]), 16).toLower() + ":" + QString::number(static_cast<int>(address[4]), 16).toLower() + ":" + QString::number(static_cast<int>(address[5]), 16).toLower();
}

QVector<quint8> MACAddress::getAddressAsArray() const {
    return address;
}

quint64 MACAddress::getAddressAsInt() const {
    quint64 returnAddress = address[0];
    returnAddress = (returnAddress << 8) + address[1];
    returnAddress = (returnAddress << 8) + address[2];
    returnAddress = (returnAddress << 8) + address[3];
    returnAddress = (returnAddress << 8) + address[4];
    returnAddress = (returnAddress << 8) + address[5];
    return  returnAddress;
}

MACAddress MACAddress::getRandomAddress() {
    static QRandomGenerator* generator = new QRandomGenerator(2183193);
    QVector<quint8> addressArray;
    for (int i = 0; i < 6; i++) {
        addressArray.append(generator->generate() % 256);
    }
    return MACAddress(addressArray);
}

bool MACAddress::operator<(const MACAddress &other) const{
    return getAddressAsInt() < other.getAddressAsInt();
}

bool MACAddress::operator==(const MACAddress &other) const{
    return this->getAddressAsInt() == other.getAddressAsInt();
}
