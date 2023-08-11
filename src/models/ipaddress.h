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

    QString toString() const;

    QVector<quint8> getAddressAsArray() const;

    quint32 getAddressAsInt() const;

    static IPAddress getRandomAddress(bool isLocal = false);

    bool operator<(const IPAddress& other)const;

    bool operator==(const IPAddress& other);
};

#endif // IPADDRESS_H
