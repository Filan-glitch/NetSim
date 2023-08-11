#ifndef HOST_H
#define HOST_H

#include <QString>
#include "src/management/packagetablemodel.h"
#include "src/models/process.h"
#include "src/models/ipaddress.h"
#include "src/models/macaddress.h"
#include "src/network/networkcard.h"
#include <QMap>

/**
 * This class represents the superclass host in a network simulation. It can either be implemented as a client or a server.
 * @brief The Host class represents a network host.
 */

class Router;

class Host
{
private:
    QMap<Port, Process> processTable;

    QMap<IPAddress, MACAddress> hostTable;

    QMap<QString, IPAddress> domainTable;

    QMap<MACAddress, Router*> cables;

    NetworkCard networkCard;

    PackageTableModel* packages;

public:
    Host(const NetworkCard &networkCard);

    QMap<Port, Process> getProcessTable() const;

    QMap<IPAddress, MACAddress> getHostTable() const;

    QMap<QString, IPAddress> getDomainTable() const;

    QMap<MACAddress, Router*> getCables() const;

    NetworkCard getNetworkCard() const;

    Router* getRouterByMACAddress(const MACAddress &destinationAddress);

    void sendPackage(Package &data, const MACAddress &destinationAddress);

    virtual void receivePackage(Package data) = 0;

    void addProcess(const Port &port, const Process &process);

    void addIPAddress(const IPAddress &ipAddress, const MACAddress &macAddress);

    void addMACAddress(const MACAddress &macAddress, Router* router);

    void addDomain(const QString &domain, const IPAddress &ipAddress);

    PackageTableModel *getPackages() const;

    void setPackages(PackageTableModel *packages);

    Process& getProcessByName(const QString &name);

    void setHostOfProcesses(Host* host);
};

#endif // HOST_H
