#include "simulationmanager.h"

SimulationManager::SimulationManager(quint8 clientAmount, quint8 serverAmount, QList<QString> domains)
{
    //Erstelle die Router
    for (auto i = 0; i <= serverAmount; i++)
    {
        routers.append(Router());
    }

    //Erstelle die Clients
    for (quint8 i = 0; i < clientAmount; i++)
    {
        QVector<quint8> routerAddress = routers[0].getNetworkCard().getNetworkAddress().getAddressAsArray();
        routerAddress[3] = i+2;
        clients.append(Client(NetworkCard(IPAddress(routerAddress), MACAddress::getRandomAddress())));
    }

    //DNS Server
    server.append(Server(NetworkCard(IPAddress::getRandomAddress(), MACAddress::getRandomAddress()), "dns.beispiel.de"));

    //Erstelle die Server
    for (auto i = 0; i < serverAmount; i++)
    {
        QVector<quint8> routerAddress = routers[i+1].getNetworkCard().getNetworkAddress().getAddressAsArray();
        routerAddress[3] = 2;
        server.append(Server(NetworkCard(IPAddress(routerAddress), MACAddress::getRandomAddress()), domains[i]));
    }


    //Cables erstellen
    for (auto& client : clients)
    {
        for (auto& router : routers) {
            client.addIPAddress(router.getNetworkCard().getNetworkAddress(), router.getNetworkCard().getPhysicalAddress()); //DNS Server
        }
        client.addMACAddress(routers[0].getNetworkCard().getPhysicalAddress(), &routers[0]);
    }

    for (int i{0}; auto& server : server)
    {
        for (auto& router : routers) {
            server.addIPAddress(router.getNetworkCard().getNetworkAddress(), router.getNetworkCard().getPhysicalAddress()); //DNS Server
        }
        server.addMACAddress(routers[i].getNetworkCard().getPhysicalAddress(), &routers[i]);
    }

    for (auto& router : routers) {
        routers[0].addIPAddress(router.getNetworkCard().getNetworkAddress(), router.getNetworkCard().getPhysicalAddress()); //DNS Server
    }

    routers[0].addIPAddress(server[0].getNetworkCard().getNetworkAddress(), server[0].getNetworkCard().getPhysicalAddress());
    routers[0].addMACAddress(server[0].getNetworkCard().getPhysicalAddress(), &server[0]);

    for (auto i = 0; i < clientAmount; i++) {
        routers[0].addMACAddress(clients[i].getNetworkCard().getPhysicalAddress(), &clients[i]);
    }

    for (auto i = 0; i < serverAmount; i++) {
        routers[0].addMACAddress(routers[i + 1].getNetworkCard().getPhysicalAddress(), &server[i + 1]);
    }

    for (int i{0}; auto& router : routers)
    {
        if (i == 0) {
            i++;
            continue;
        }
        for (auto& router2 : routers) {
            router.addIPAddress(router2.getNetworkCard().getNetworkAddress(), router2.getNetworkCard().getPhysicalAddress()); //DNS Server
        }
        router.addMACAddress(routers[0].getNetworkCard().getPhysicalAddress(), &routers[0]);
        router.addMACAddress(server[i].getNetworkCard().getPhysicalAddress(), &server[i]);
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

