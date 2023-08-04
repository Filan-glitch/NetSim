#ifndef HOST_H
#define HOST_H

#include <QString>
#include <QHash>
#include "src/models/process.h"
#include "src/models/ipaddress.h"
#include "src/models/macaddress.h"
#include "src/models/port.h"
#include "src/network/networkcard.h"
#include "src/network/router.h"

/**
 * This class represents the superclass host in a network simulation. It can either be implemented as a client or a server.
 * @brief The Host class represents a network host.
 */
class Host
{
private:
    QHash<Port, Process> processTable;
    QHash<IPAddress, MACAddress> hostTable;
    QHash<QString, IPAddress> domainTable;
    NetworkCard networkCard;

public:
    Host(const NetworkCard &networkCard);
    QHash<Port, Process> getProcessTable() const;
    QHash<IPAddress, MACAddress> getHostTable() const;
    QHash<QString, IPAddress> getDomainTable() const;
    NetworkCard getNetworkCard() const;
};

#endif // HOST_H
