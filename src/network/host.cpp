#include "host.h"

QHash<Port, Process> Host::getProcessTable() const
{
    return processTable;
}

QHash<IPAddress, MACAddress> Host::getHostTable() const
{
    return hostTable;
}

QHash<QString, IPAddress> Host::getDomainTable() const
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
