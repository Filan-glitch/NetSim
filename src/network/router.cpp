#include "router.h"

IPAddress Router::getGlobalIpAddress() const
{
    return globalIpAddress;
}

NetworkCard Router::getNetworkCard() const
{
    return networkCard;
}

Router::Router() : networkCard(NetworkCard(IPAddress::getRandomAddress(true), MACAddress::getRandomAddress())), globalIpAddress(IPAddress::getRandomAddress(false))
{
    networkCard.getNetworkAddress().getAddressAsArray()[3] = 1;
}

void Router::addDomain(const QString &domain, const IPAddress &ipAddress)
{
    domainTable.insert(domain, ipAddress);
}

bool Router::initializeServerConnection()
{
    return false;
}

void Router::getPackage()
{
    
}

void Router::forwardPackage()
{
    
}
