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

using namespace std;

class Router;

class Host
{
private:
    map<Port, Process> processTable;
    map<IPAddress, MACAddress> hostTable;
    map<QString, IPAddress> domainTable;
    map<MACAddress, Router*> cables;
    NetworkCard networkCard;

public:
    Host(const NetworkCard &networkCard);
    map<Port, Process> getProcessTable() const;
    map<IPAddress, MACAddress> getHostTable() const;
    map<QString, IPAddress> getDomainTable() const;
    NetworkCard getNetworkCard() const;
    Router* getRouterByMACAddress(MACAddress destinationAddress);
    Package sendPackage(const Package &data, MACAddress destinationAddress);
    void receivePackage(const Package &data);
};

#endif // HOST_H
