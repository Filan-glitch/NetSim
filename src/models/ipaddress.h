#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QRandomGenerator>
#include <QString>
#include <QTextStream>

class IPAddress
{
private:
    quint8* address;

public:
    IPAddress(quint8* address);

    ~IPAddress();

    QString getAddressAsDecString() const;

    quint8* getAddressAsArray() const;

    quint32 getAddressAsInt() const;

    static IPAddress* getRandomAddress();
};

#endif // IPADDRESS_H
