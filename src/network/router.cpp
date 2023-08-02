#include "router.h"

IPAddress *Router::getGlobalIpAddress() const
{
    return globalIpAddress;
}

NetworkCard *Router::getNetworkCard() const
{
    return networkCard;
}

Router::Router() : networkCard(new NetworkCard(IPAddress::getRandomAddress(), MACAddress::getRandomAddress())), globalIpAddress(IPAddress::getRandomAddress())
{}

void Router::addDomain(QString domain, IPAddress *ipAddress)
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
