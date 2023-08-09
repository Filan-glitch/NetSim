#include "host.h"
#include "router.h"
#include "src/management/packagedatabase.h"

QMap<Port, Process> Host::getProcessTable() const
{
    return processTable;
}

QMap<IPAddress, MACAddress> Host::getHostTable() const
{
    return hostTable;
}

QMap<QString, IPAddress> Host::getDomainTable() const
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

void Host::sendPackage(const Package &data, MACAddress destinationAddress){
    cables[destinationAddress]->receivePackage(data);
}

void Host::receivePackage(const Package &data){
    //TODO ADD PACKAGE TO DATABASE
    PackageDatabase::instance()->packageList()->append(data);
}

void Host::addIPAddress(const IPAddress &ipAddress, const MACAddress &macAddress)
{
    hostTable[ipAddress] = macAddress;
}

void Host::addMACAddress(const MACAddress &macAddress, Router *router)
{
    cables[macAddress] = router;
}

void Host::addDomain(const QString &domain, const IPAddress &ipAddress)
{
    domainTable[domain] = ipAddress;
}
