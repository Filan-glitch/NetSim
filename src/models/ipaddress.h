#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QString>
#include <QTextStream>

class IPAddress
{
private:
    quint8* address;

public:
    IPAddress(quint8* address);
    QString getAddressAsDecString() const {
        QString result;
        QTextStream(&result) << address[0] << "." << address[1] << "." << address[2] << "." << address[3];
        return result;
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
