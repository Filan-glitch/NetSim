#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QRandomGenerator>
#include <QString>
#include <QTextStream>
#include <QVector>

class IPAddress
{
private:
    QVector<quint8> address;

public:
    IPAddress();
    IPAddress(const QVector<quint8> &address);

    IPAddress(){};

    QString getAddressAsDecString() const;

    QVector<quint8> getAddressAsArray() const;

    quint32 getAddressAsInt() const;

    static IPAddress getRandomAddress(bool isLocal = false);

    bool operator<(const IPAddress& other)const{
        return getAddressAsInt() < other.getAddressAsInt();
    }
};

#endif // IPADDRESS_H
