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
    domainTable[domain] = ipAddress;
}

bool Router::initializeServerConnection()
{
    return false;
}

void Router::receivePackage(const Package &data)
{
    cachePackage.push(data);
}

void Router::sendPackageToRouter(MACAddress destinationAddress){
    //routerCable[destinationAddress]->receivePackage(cachePackage.pop());
}

void Router::sendPackageToHost(MACAddress destinationAddress){
    //hostCable[destinationAddress]->receivePackage(cachePackage.pop());
}
