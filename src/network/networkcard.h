#ifndef NETWORKCARD_H
#define NETWORKCARD_H

#include "src/models/ipaddress.h"
#include "src/models/macaddress.h"
#include "src/models/package.h"



class NetworkCard
{
public:

    NetworkCard(const IPAddress &networkAddress, const MACAddress &physicalAddress);;

    void addIPHeader(Package &data, quint8 protocol,const IPAddress &destinationAddress);
    void addMACHeader(Package &data, MACAddress destinationMACAddress, quint16 dataLength);
    Package sentToRouter(Package& data);
    IPAddress getNetworkAddress() const;
    MACAddress getPhysicalAddress() const;

private:
    IPAddress networkAddress;
    MACAddress physicalAddress;
};

#endif // NETWORKCARD_H
