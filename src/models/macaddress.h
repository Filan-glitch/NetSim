#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <QString>
#include <QRandomGenerator>

using namespace Qt;

class MACAddress
{
private:
    quint8* address;
public:
    MACAddress(quint8 *address);

    ~MACAddress();

    QString getAddressAsString() const;
    quint8* getAddressAsArray() const;
    quint64 getAddressAsInt() const;

    static MACAddress* getRandomAddress();
};



#endif // MACADDRESS_H
