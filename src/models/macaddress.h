#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <QString>
#include <QRandomGenerator>
#include <QVector>

using namespace Qt;

class MACAddress
{
private:
    QVector<quint8> address;
public:
    MACAddress(const QVector<quint8> &address);

    MACAddress();;

    QString toString() const;

    QVector<quint8> getAddressAsArray() const;

    quint64 getAddressAsInt() const;

    static MACAddress getRandomAddress();

    bool operator<(const MACAddress& other) const;

    bool operator==(const MACAddress& other) const;
};



#endif // MACADDRESS_H
