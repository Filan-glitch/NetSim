#include "ipaddress.h"



IPAddress::IPAddress(const QVector<quint8> &address) : address(address) {

}

QString IPAddress::getAddressAsDecString() const {
    return QString::number(static_cast<int>(address[0])) + "." + QString::number(static_cast<int>(address[1])) + "." + QString::number(static_cast<int>(address[2])) + "." + QString::number(static_cast<int>(address[3]));
}

QVector<quint8> IPAddress::getAddressAsArray() const {
    return address;
}

quint32 IPAddress::getAddressAsInt() const{
    quint32 returnAddress = address[0];
    returnAddress = (returnAddress << 8) + address[1];
    returnAddress = (returnAddress << 8) + address[2];
    returnAddress = (returnAddress << 8) + address[3];
    return  returnAddress;
}

IPAddress IPAddress::getRandomAddress(bool isLocal) {
    static QRandomGenerator* generator = new QRandomGenerator(2183193);
    QVector<quint8> addressArray;
    for (int i = 0; i < 4; i++) {
        addressArray.append(generator->generate() % 256);
    }
    if(isLocal) addressArray[3] = 1;
    return IPAddress(addressArray);
}
