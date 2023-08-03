#include "host.h"
#include "router.h"
#include "src/management/packagedatabase.h""

QHash<Port, Process> Host::getProcessTable() const
{
    return processTable;
}

QHash<IPAddress, MACAddress> Host::getHostTable() const
{
    return hostTable;
}

QHash<QString, IPAddress> Host::getDomainTable() const
{
    return domainTable;
}

NetworkCard Host::getNetworkCard() const
{
    return networkCard;
}

Host::Host(const NetworkCard &networkCard) :
    networkCard(networkCard)
{}

Router* Host::getRouterByMACAddress(MACAddress destinationAddress){
    return this->cables.value(destinationAddress);
}

Package Host::sendPackage(const Package &data, MACAddress destinationAddress){
    cables.value(destinationAddress)->receivePackage(data);
}

void Host::receivePackage(const Package &data){
    //TODO ADD PACKAGE TO DATABASE
}
