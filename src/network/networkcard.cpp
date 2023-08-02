#include "networkcard.h"

NetworkCard::NetworkCard(const IPAddress &networkAddress, const MACAddress &physicalAddress) : networkAddress(networkAddress), physicalAddress(physicalAddress){}

void NetworkCard::addIPHeader(Package &data)
{

}

void NetworkCard::addMACHeader(Package &data)
{

}

void NetworkCard::sentToRouter(Package &data)
{

}

IPAddress NetworkCard::getNetworkAddress() const
{
    return networkAddress;
}

MACAddress NetworkCard::getPhysicalAddress() const
{
    return physicalAddress;
}
