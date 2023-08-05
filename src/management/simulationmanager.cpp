#include "simulationmanager.h"

SimulationManager::SimulationManager(quint8 clientAmount, quint8 serverAmount)
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
    server.append(Server(NetworkCard(IPAddress::getRandomAddress(), MACAddress::getRandomAddress())));

    //Erstelle die Server
    for (auto i = 0; i < serverAmount; i++)
    {
        QVector<quint8> routerAddress = routers[i+1].getNetworkCard().getNetworkAddress().getAddressAsArray();
        routerAddress[3] = 2;
        server.append(Server(NetworkCard(IPAddress(routerAddress), MACAddress::getRandomAddress())));
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

QList<Server> SimulationManager::getServer() const
{
    return server;
}

QList<Client> SimulationManager::getClients() const
{
    return clients;
}

QList<Router> SimulationManager::getRouters() const
{
    return routers;
}

