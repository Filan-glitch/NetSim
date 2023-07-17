#include "host.h"

Host::Host(const IPAddress &ipAddress, const QHash<Port, Process> &processTable, const QHash<MACAddress, IPAddress> &hostTable, const QHash<QString, IPAddress> &domainTable) : ipAddress(ipAddress),
    processTable(processTable),
    hostTable(hostTable),
    domainTable(domainTable)
{}
