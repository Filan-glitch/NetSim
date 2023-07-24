#ifndef HOST_H
#define HOST_H

#include <QString>
#include <QHash>
#include "../models/process.h"
#include "../models/ipaddress.h"
#include "../models/macaddress.h"
#include "../models/port.h"
#include "../network/networkcard.h"

/**
 * This class represents the superclass host in a network simulation. It can either be implemented as a client or a server.
 * @brief The Host class represents a network host.
 */
class Host
{
private:
    QHash<Port, Process> processTable;
    QHash<MACAddress, IPAddress> hostTable;
    QHash<QString, IPAddress> domainTable;
    NetworkCard networkCard;

public:
    Host(const QHash<Port, Process> &processTable, const QHash<MACAddress, IPAddress> &hostTable, const QHash<QString, IPAddress> &domainTable, const NetworkCard &networkCard);
};

#endif // HOST_H
