#include "ipaddress.h"



IPAddress::IPAddress(quint8 *address) : address(address) {}

IPAddress::~IPAddress() {
    delete[] address;
}

QString IPAddress::getAddressAsDecString() const {
    return QString::number(static_cast<int>(address[0])) + "." + QString::number(static_cast<int>(address[1])) + "." + QString::number(static_cast<int>(address[2])) + "." + QString::number(static_cast<int>(address[3]));
}

quint8 *IPAddress::getAddressAsArray() const {
    return address;
}

quint32 IPAddress::getAddressAsInt() const{
    quint32 returnAddress = address[0];
    returnAddress = (returnAddress << 8) + address[1];
    returnAddress = (returnAddress << 8) + address[2];
    returnAddress = (returnAddress << 8) + address[3];
    return  returnAddress;
}

IPAddress *IPAddress::getRandomAddress() {
    static QRandomGenerator* generator = new QRandomGenerator(2183193);
    quint8* addressArray = new quint8[4];
    for (int i = 0; i < 3; i++) {
        addressArray[i] = generator->generate() % 256;
    }
    addressArray[3] = 1;
    return new IPAddress(addressArray);
}
