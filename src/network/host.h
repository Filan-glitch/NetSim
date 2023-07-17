#ifndef HOST_H
#define HOST_H

#include <QString>
#include <QHash>
#include "../models/process.h"
#include "../models/ipaddress.h"
#include "../models/macaddress.h"
#include "../models/port.h"

/**
 * This class represents the superclass host in a network simulation. It can either be implemented as a client or a server.
 * @brief The Host class represents a network host.
 */
class Host
{
private:
    IPAddress ipAddress;
    QHash<Port, Process> processTable;
    QHash<MACAddress, IPAddress> hostTable;
    QHash<QString, IPAddress> domainTable;

public:
    Host(const IPAddress &ipAddress, const QHash<Port, Process> &processTable, const QHash<MACAddress, IPAddress> &hostTable, const QHash<QString, IPAddress> &domainTable);
};

#endif // HOST_H
