#ifndef NETWORKCARD_H
#define NETWORKCARD_H

#include <src/models/macaddress.cpp>
#include <src/models/package.h>



class networkCard
{
public:

    networkCard(MACAddress address):physicalAddress(address){

    }

    void addIPHeader(Package& data);
    void addMACHeader(Package& data);
    void sentToRouter(Package& data);
private:
    MACAddress physicalAddress;
};

#endif // NETWORKCARD_H
