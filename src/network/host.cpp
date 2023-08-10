#include "cablenotfoundexception.h"
#include "host.h"
#include "router.h"

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

QMap<MACAddress, Router *> Host::getCables() const
{
    return cables;
}

NetworkCard Host::getNetworkCard() const
{
    return networkCard;
}

PackageTableModel *Host::getPackages() const
{
    return packages;
}

void Host::setPackages(PackageTableModel *packages)
{
    this->packages = packages;
}

Process &Host::getProcessByName(const QString &name)
{
    for(auto& process : processTable) {
        if(process.getName() == name) {
            return process;
        }
    }
    throw std::runtime_error("Process not found");
}

void Host::setHostOfProcesses(Host *host)
{
    for(auto& process : processTable) {
        process.setHost(host);
    }
}

Host::Host(const NetworkCard &networkCard) :
    processTable(QMap<Port, Process>()),
    hostTable(QMap<IPAddress, MACAddress>()),
    domainTable(QMap<QString, IPAddress>()),
    cables(QMap<MACAddress, Router*>()),
    networkCard(networkCard)
{
    Process http(80, "HTTP");
    Process dns(53, "DNS");
    addProcess(http.getSocket().getSourcePort().getPortNumber(), http);
    addProcess(dns.getSocket().getSourcePort().getPortNumber(), dns);
}

Router* Host::getRouterByMACAddress(const MACAddress &destinationAddress){
    if(cables[destinationAddress] != nullptr){
        return cables[destinationAddress];
    }else{
        throw CableNotFoundException("Cable not found in: Host::getRouterByMACAddress");
    }

}

void Host::sendPackage(Package &data, const MACAddress &destinationAddress){
    cables[destinationAddress]->receivePackage(data);
}

void Host::addProcess(const Port &port, const Process &process)
{
    processTable[port] = process;
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
