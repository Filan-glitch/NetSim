#include "router.h"

IPAddress Router::getGlobalIpAddress() const
{
    return globalIpAddress;
}

NetworkCard Router::getNetworkCard() const
{
    return networkCard;
}

void Router::addIPAddress(const IPAddress &ipAddress, const MACAddress &macaddress)
{
    macTable[ipAddress] = macaddress;
}

void Router::addMACAddress(const MACAddress &macAddress, Router *router)
{
    routerCable[macAddress] = router;
}

void Router::addMACAddress(const MACAddress &macAddress, Host *host)
{
    hostCable[macAddress] = host;
}

Router::Router() : networkCard(NetworkCard(IPAddress::getRandomAddress(true), MACAddress::getRandomAddress())), globalIpAddress(IPAddress::getRandomAddress(false))
{
    networkCard.getNetworkAddress().getAddressAsArray()[3] = 1;
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
    routerCable[destinationAddress]->receivePackage(cachePackage.pop());
}

void Router::sendPackageToHost(MACAddress destinationAddress){
    hostCable[destinationAddress]->receivePackage(cachePackage.pop());
}
