#ifndef HOST_H
#define HOST_H

#include <QString>
#include <QHash>
#include "src/models/process.h"
#include "src/models/ipaddress.h"
#include "src/models/macaddress.h"
#include "src/models/port.h"
#include "src/network/networkcard.h"

/**
 * This class represents the superclass host in a network simulation. It can either be implemented as a client or a server.
 * @brief The Host class represents a network host.
 */

class Router;

class Host
{
private:
    QHash<Port, Process> processTable;
    QHash< IPAddress, MACAddress> hostTable;
    QHash<QString, IPAddress> domainTable;
    QHash<MACAddress, Router*> cables;
    NetworkCard networkCard;

public:
    Host(const NetworkCard &networkCard);
    QHash<Port, Process> getProcessTable() const;
    QHash<IPAddress, MACAddress> getHostTable() const;
    QHash<QString, IPAddress> getDomainTable() const;
    NetworkCard getNetworkCard() const;
    Router* getRouterByMACAddress(MACAddress destinationAddress);
    Package sendPackage(const Package &data, MACAddress destinationAddress);
    void receivePackage(const Package &data);
};

#endif // HOST_H
