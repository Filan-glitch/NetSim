#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QString>
#include <QTextStream>

class IPAddress
{
private:
    qint8* address;

public:
    IPAddress(qint8 address[4]);
    QString getAddressAsDecString() const {
        QString result;
        QTextStream(&result) << address[0] << "." << address[1] << "." << address[2] << "." << address[3];
        return result;
    }
    qint8* getAddressAsArray() const {
        return address;
    }
    qint32 getAddressAsInt() const{
        qint32 returnAddress = address[0];
        returnAddress = (returnAddress << 8) + address[1];
        returnAddress = (returnAddress << 8) + address[2];
        returnAddress = (returnAddress << 8) + address[3];
        return  returnAddress;
    }
};

#endif // IPADDRESS_H
