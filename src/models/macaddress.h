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

    MACAddress(){
        address << 0 << 0 << 0 << 0 << 0 << 0;
    };

    QString toString() const;
    QVector<quint8> getAddressAsArray() const;
    quint64 getAddressAsInt() const;

    static MACAddress getRandomAddress();

    bool operator<(const MACAddress& other) const{
        return getAddressAsInt() < other.getAddressAsInt();
    }

    bool operator==(const MACAddress& other) const{
        return this->getAddressAsInt() == other.getAddressAsInt();
    }
};



#endif // MACADDRESS_H
