#include "simulationmanager.h"

SimulationManager::SimulationManager(quint8 clientAmount, quint8 serverAmount, QList<QString> domains)
{
    //Erstelle die Router
    for (auto i = 0; i <= serverAmount; i++)
    {
        routers.append(Router());
    }

    //DNS Server
    server.append(Server(NetworkCard(IPAddress::getRandomAddress(), MACAddress::getRandomAddress()), "dns.beispiel.de",""));

    //Erstelle die Clients
    for (quint8 i = 0; i < clientAmount; i++)
    {
        QVector<quint8> routerAddress = routers[0].getNetworkCard().getNetworkAddress().getAddressAsArray();
        routerAddress[3] = i+2;
        clients.append(Client(NetworkCard(IPAddress(routerAddress), MACAddress::getRandomAddress())));
        clients[i].addDomain("dns.beispiel.de", server.constFirst().getNetworkCard().getNetworkAddress());
    }

    //Erstelle die Server
    const QString html = "<!DOCTYPE html>\n<html>\n\t<header len=\"de\">\n\t\t<meta charset=\"utf.8\">\n\t</head>\n\t<body>\n\t\t<a>r.mtdv.me/videos/exampleVideo</a>\n\t</body>\n</html>";
    for (auto i = 0; i < serverAmount; i++)
    {
        QVector<quint8> routerAddress = routers[i+1].getNetworkCard().getNetworkAddress().getAddressAsArray();
        routerAddress[3] = 2;
        server.append(Server(NetworkCard(IPAddress(routerAddress), MACAddress::getRandomAddress()), domains[i],html));
    }

    //Cables erstellen
    int i = 0;
    for (auto& client : clients)
    {
        for (auto& router : routers) {
            if(i == 0) {
                i++;
                continue;
            }
            client.addIPAddress(router.getGlobalIpAddress(), routers[0].getNetworkCard().getPhysicalAddress());
            i++;
        }
        client.addIPAddress(server[0].getNetworkCard().getNetworkAddress(), routers[0].getNetworkCard().getPhysicalAddress());
        client.addMACAddress(routers.constFirst().getNetworkCard().getPhysicalAddress(), &routers[0]);
        routers[0].addIPAddress(client.getNetworkCard().getNetworkAddress(), client.getNetworkCard().getPhysicalAddress());
        routers[0].addMACAddress(client.getNetworkCard().getPhysicalAddress(), &client);
    }

    i = 0;
    for (auto& server : server)
    {
        server.addIPAddress(routers[0].getGlobalIpAddress(), routers[i].getNetworkCard().getPhysicalAddress());
        server.addMACAddress(routers[i].getNetworkCard().getPhysicalAddress(), &routers[i]);
        i++;
    }

    i = 0;
    for(auto& router : routers) {
        if (i == 0) {
            i++;
            continue;
        }

        routers[0].addIPAddress(router.getGlobalIpAddress(), router.getNetworkCard().getPhysicalAddress());
        routers[0].addMACAddress(router.getNetworkCard().getPhysicalAddress(), &router);
        router.addIPAddress(routers[0].getGlobalIpAddress(), routers[0].getNetworkCard().getPhysicalAddress());
        router.addIPAddress(server[i].getNetworkCard().getNetworkAddress(), server[i].getNetworkCard().getPhysicalAddress());
        router.addMACAddress(routers[0].getNetworkCard().getPhysicalAddress(), &routers[0]);
        router.addMACAddress(server[i].getNetworkCard().getPhysicalAddress(), &server[i]);
        server[0].addDomain(domains[i-1], router.getGlobalIpAddress());
        i++;
    }

    routers[0].addIPAddress(server[0].getNetworkCard().getNetworkAddress(), server[0].getNetworkCard().getPhysicalAddress());
    routers[0].addMACAddress(server[0].getNetworkCard().getPhysicalAddress(), &server[0]);

    //NAT Tables
    i = 0;
    for (auto& router : routers) {
        if (i == 0) {
            i++;
            continue;
        }
        router.addNATEntry(NATEntry(server[i].getNetworkCard().getNetworkAddress(), server[i].getProcessByName("HTTP").getSocket().getSourcePort()), Port(80));
        router.addNATEntry(NATEntry(server[i].getNetworkCard().getNetworkAddress(), server[i].getProcessByName("DNS").getSocket().getSourcePort()), Port(53));
        i++;
    }

    i = 0;
    for (auto& client : clients) {
        routers[0].addNATEntry(NATEntry(client.getNetworkCard().getNetworkAddress(), client.getProcessByName("HTTP").getSocket().getSourcePort()), Port(50000 + i++));
        routers[0].addNATEntry(NATEntry(client.getNetworkCard().getNetworkAddress(), client.getProcessByName("DNS").getSocket().getSourcePort()), Port(50000 + i++));
    }

    //Host Pointer
    for(int i = 0; i < clients.size(); i++) {
        clients[i].setHostOfProcesses(&clients[i]);
    }

    for(int i = 0; i < server.size(); i++) {
        server[i].setHostOfProcesses(&server[i]);
    }
}

quint8 SimulationManager::getClientsAmount() const
{
    return static_cast<quint8>(clients.size());
}

quint8 SimulationManager::getServerAmount() const
{
    return static_cast<quint8>(server.size() - 1);
}

QList<Server>* SimulationManager::getServer()
{
    return &server;
}

QList<Client>* SimulationManager::getClients()
{
    return &clients;
}

QList<Router>* SimulationManager::getRouters()
{
    return &routers;
}

void SimulationManager::setPackages(PackageTableModel *packages)
{
    for(auto& client : clients)
    {
        client.setPackages(packages);
    }
    for(auto& server : server)
    {
        server.setPackages(packages);
    }
}

