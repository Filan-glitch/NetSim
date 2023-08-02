#include "networkcard.h"

IPAddress NetworkCard::getNetworkAddress() const
{
    return networkAddress;
}

MACAddress NetworkCard::getPhysicalAddress() const
{
    return physicalAddress;
}
