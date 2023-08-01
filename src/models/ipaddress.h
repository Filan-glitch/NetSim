#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QString>
#include <QTextStream>

class IPAddress
{
private:
    quint8* address;

public:
    IPAddress(quint8* address) : address(address) {}

    ~IPAddress() {
        delete[] address;
    }

    QString getAddressAsDecString() const {
        return QString::number(static_cast<int>(address[0])) + "." + QString::number(static_cast<int>(address[1])) + "." + QString::number(static_cast<int>(address[2])) + "." + QString::number(static_cast<int>(address[3]));
    }

    quint8* getAddressAsArray() const {
        return address;
    }

    quint32 getAddressAsInt() const{
        quint32 returnAddress = address[0];
        returnAddress = (returnAddress << 8) + address[1];
        returnAddress = (returnAddress << 8) + address[2];
        returnAddress = (returnAddress << 8) + address[3];
        return  returnAddress;
    }
};

#endif // IPADDRESS_H
