#ifndef NETWORKCARD_H
#define NETWORKCARD_H

#include "../models/ipaddress.h"
#include "../models/macaddress.h"
#include "../models/package.h"



class NetworkCard
{
public:

    NetworkCard(const IPAddress &networkAddress, const MACAddress &physicalAddress):networkAddress(networkAddress), physicalAddress(physicalAddress){};

    void addIPHeader(Package& data);
    void addMACHeader(Package& data);
    void sentToRouter(Package& data);
private:
    IPAddress networkAddress;
    MACAddress physicalAddress;
};

#endif // NETWORKCARD_H
