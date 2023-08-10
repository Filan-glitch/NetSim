#include "networkcard.h"
#include "qdatetime.h"
#include "src/protocols/mac.h"
#include "src/protocols/ipv4.h"

NetworkCard::NetworkCard(const IPAddress &networkAddress, const MACAddress &physicalAddress) : networkAddress(networkAddress), physicalAddress(physicalAddress){}

void NetworkCard::addIPHeader(Package &data, quint8 protocol,const IPAddress &destinationAddress)
{
    QTime seed;
    QRandomGenerator rnd(seed.msecsSinceStartOfDay());
    quint16 id = rnd.generate();

    IPv4::initHeader(id,
        false,
        false,
        0,
        4,
        protocol,
        getNetworkAddress(),
        destinationAddress,
        data);
}

void NetworkCard::addMACHeader(Package &data, MACAddress destinationMACAddress, quint16 etherType)
{
    MAC::initHeader(data, destinationMACAddress, this->getPhysicalAddress(), etherType);
}

Package NetworkCard::sentToRouter(Package &data)
{
    return data;
}

IPAddress NetworkCard::getNetworkAddress() const
{
    return networkAddress;
}

MACAddress NetworkCard::getPhysicalAddress() const
{
    return physicalAddress;
}
