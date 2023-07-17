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
};

#endif // IPADDRESS_H
