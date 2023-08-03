#include "host.h"
#include "router.h"
#include "src/management/packagedatabase.h"

map<Port, Process> Host::getProcessTable() const
{
    return processTable;
}

map<IPAddress, MACAddress> Host::getHostTable() const
{
    return hostTable;
}

map<QString, IPAddress> Host::getDomainTable() const
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
    return this->cables[destinationAddress];
}

Package Host::sendPackage(const Package &data, MACAddress destinationAddress){
    cables[destinationAddress]->receivePackage(data);
}

void Host::receivePackage(const Package &data){
    //TODO ADD PACKAGE TO DATABASE
}
