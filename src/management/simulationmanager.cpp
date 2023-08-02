#include "simulationmanager.h"

SimulationManager::SimulationManager(quint8 clientAmount, quint8 serverAmount)
{
    //Erstelle die Clients
    for (quint8 i = 0; i < clientAmount; i++)
    {
        quint8 ipAddress[4] = {192, 168, 178, i};
        clients.append(new Client(NetworkCard(IPAddress(ipAddress), MACAddress::getRandomAddress())));
    }

    //Erstelle die Server
    for (auto i = 0; i < serverAmount; i++)
    {
        quint8 ipAddress[4] = {216, 188, 21, 2};
        server.append(new Server(NetworkCard(IPAddress(ipAddress), MACAddress::getRandomAddress())));
    }

    //Erstelle die Router
    for (auto i = 0; i <= serverAmount; i++)
    {
        routers.append(new Router());
    }
}

quint8 SimulationManager::getClientsAmount() const
{
    return static_cast<quint8>(clients.size());
}

quint8 SimulationManager::getServerAmount() const
{
    return static_cast<quint8>(server.size());
}

QList<Server *> SimulationManager::getServer() const
{
    return server;
}

QList<Client *> SimulationManager::getClients() const
{
    return clients;
}

QList<Router *> SimulationManager::getRouters() const
{
    return routers;
}

