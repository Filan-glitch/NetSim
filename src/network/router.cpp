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

void Router::receivePackage(const Package &data)
{
    //TODO Change Ethernet II Header


    //Fragmenting Package
    QList<Package> fragments = IPv4::fragmentPackage(data,1500);

    //Getting the macAddress
    IPAddress destIP = HeaderUtil::getIPAddressAsIPAddress(data, false);
    MACAddress destMAC = this->macTable[destIP];

    //NAT (PAT Port address Translation)
    if(destIP.getAddressAsInt() == this->globalIpAddress.getAddressAsInt()){
        NATEntry entry = portToNAT[HeaderUtil::getPortAsPort(data,false)];

        //TODO change package
        destMAC = this->macTable[entry.getIPAddress()];
    }
    else{
        NATEntry entry(HeaderUtil::getIPAddressAsIPAddress(data,true),HeaderUtil::getPortAsPort(data,true));
        natToPort[entry] = 50000 + natToPort.size();

        //TODO change package
    }

    //Changing the Ethernet II Header
    HeaderUtil::changeAttribute(data,HeaderType::MAC,"")

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
