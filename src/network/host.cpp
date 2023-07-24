#include "host.h"

Host::Host(const QHash<Port, Process> &processTable, const QHash<MACAddress, IPAddress> &hostTable, const QHash<QString, IPAddress> &domainTable, const NetworkCard &networkCard) :
    processTable(processTable),
    hostTable(hostTable),
    domainTable(domainTable),
    networkCard(networkCard)
{}
