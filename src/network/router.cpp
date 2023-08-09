#include "cablenotfoundexception.h"
#include "router.h"

#include <src/protocols/headerutil.h>

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

void Router::receivePackage(Package data)
{
    //Getting the macAddress
    IPAddress destIP = HeaderUtil::getIPAddressAsIPAddress(data, false);
    MACAddress destMAC = this->macTable[destIP];

    //NAT (PAT Port address Translation)
    if(destIP.getAddressAsInt() == this->globalIpAddress.getAddressAsInt()){
        NATEntry entry = portToNAT[HeaderUtil::getPortAsPort(data,false)];
        data.changePortAndIP(entry.getPortNumber(),entry.getIPAddress(),false);
        destMAC = this->macTable[entry.getIPAddress()];
    }
    else if(this->networkCard.getNetworkAddress().getAddressAsInt() != 0){
        NATEntry entry(HeaderUtil::getIPAddressAsIPAddress(data,true),HeaderUtil::getPortAsPort(data,true));
        int port = 50000 + natToPort.size();
        if(!natToPort.contains(entry) && !portToNAT.contains(port)){
            natToPort[entry] = port;
            portToNAT[port] = entry;
        }
        data.changePortAndIP(natToPort[entry].getPortNumber(),this->globalIpAddress, true);
    }

    //Changing the Ethernet II Header
     data.changeEthernetHeader(this->networkCard.getPhysicalAddress(),destMAC);

     //Fragmenting the Package
     QList<Package> fragments = IPv4::fragmentPackage(data,1500);

    //Getting the router/Host
    Router* nextRouter = this->routerCable[destMAC];
    if(nextRouter == nullptr){
        Host* destHost = this->hostCable[destMAC];
        if(destHost == nullptr){
            QString error = "Couldn't find a connection to MACAddress: ";
            error.append(destMAC.getAddressAsString());
            qDebug() << error;
            throw CableNotFoundException(error);
        }
        for(auto& element : fragments){
            destHost->receivePackage(element);
        }
    }
    else{
        for(auto& element : fragments){
            nextRouter->receivePackage(element);
        }
    }
}
