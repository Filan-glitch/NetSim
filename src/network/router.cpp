#include "cablenotfoundexception.h"
#include "router.h"
#include "src/protocols/headerutil.h"

IPAddress Router::getGlobalIpAddress() const
{
    return globalIpAddress;
}

NetworkCard Router::getNetworkCard() const
{
    return networkCard;
}

QMap<IPAddress, MACAddress> Router::getMacTable() const
{
    return macTable;
}

QMap<MACAddress, Router *> Router::getRouterCable() const
{
    return routerCable;
}

QMap<MACAddress, Host *> Router::getHostCable() const
{
    return hostCable;
}

QMap<Port, NATEntry> Router::getNAT() const
{
    return portToNAT;
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

void Router::addNATEntry(const NATEntry &entry, const Port &port)
{
    portToNAT[port] = entry;
    natToPort[entry] = port;
}

Router::Router() :
    macTable(QMap<IPAddress, MACAddress>()),
    routerCable(QMap<MACAddress, Router*>()),
    hostCable(QMap<MACAddress, Host*>()),
    portToNAT(QMap<Port, NATEntry>()),
    natToPort(QMap<NATEntry, Port>()),
    networkCard(NetworkCard(IPAddress::getRandomAddress(true), MACAddress::getRandomAddress())),
    globalIpAddress(IPAddress::getRandomAddress(false))
{
    networkCard.getNetworkAddress().getAddressAsArray()[3] = 1;
}

void Router::receivePackage(Package data)
{
    //Getting the macAddress
    IPAddress destIP = HeaderUtil::getIPAddressAsIPAddress(data, false);
    MACAddress destMAC = this->macTable[destIP];

    //NAT (PAT Port address Translation)
    if(destIP == this->globalIpAddress){
        NATEntry entry = portToNAT[HeaderUtil::getPortAsPort(data,false)];
        data.changePortAndIP(entry.getPortNumber(),entry.getIPAddress(),false);
        destMAC = this->macTable[entry.getIPAddress()];
    }
    else if(this->networkCard.getNetworkAddress().getAddressAsInt() != 0){
        NATEntry entry(HeaderUtil::getIPAddressAsIPAddress(data,true),HeaderUtil::getPortAsPort(data,true));
        data.changePortAndIP(natToPort[entry].getPortNumber(),this->globalIpAddress, true);
    }

    //Changing the Ethernet II Header
    data.changeEthernetHeader(this->networkCard.getPhysicalAddress(),destMAC);

    //Fragmenting the Package
    //QList<Package> fragments = IPv4::fragmentPackage(data,1500);
    QList<Package> fragments;
    fragments.append(data);

    //Getting the router/Host
    Router* nextRouter = this->routerCable[destMAC];
    if(nextRouter == nullptr){
        Host* destHost = this->hostCable[destMAC];
        if(destHost == nullptr){
            QString error = QString("Couldn't find a connection to MACAddress: %1").arg(destMAC.getAddressAsString());
            qFatal("%s", error.toStdString().c_str());
            throw CableNotFoundException(error);
        }
        for(const auto& element : fragments){
            destHost->receivePackage(element);
        }
    }
    else{
        for(const auto& element : fragments){
            nextRouter->receivePackage(element);
        }
    }
}
