#include "simulationmanager.h"

SimulationManager::SimulationManager(quint8 clientAmount, quint8 serverAmount)
{
    quint8* ipAddress;

    //Erstelle die Router
    for (auto i = 0; i <= serverAmount; i++)
    {
        routers.append(new Router());
    }

    //Erstelle die Clients
    for (quint8 i = 0; i < clientAmount; i++)
    {
        quint8* routerAddress = routers[0]->getNetworkCard()->getNetworkAddress()->getAddressAsArray();
        ipAddress =  new quint8[4];
        ipAddress[0] = *(routerAddress);
        ipAddress[1] = *(routerAddress+1);
        ipAddress[2] = *(routerAddress+2);
        ipAddress[3] = i+2;
        clients.append(new Client(new NetworkCard(new IPAddress(ipAddress), MACAddress::getRandomAddress())));
    }

    //Erstelle die Server
    for (auto i = 0; i < serverAmount; i++)
    {
        quint8* routerAddress = routers[i+1]->getNetworkCard()->getNetworkAddress()->getAddressAsArray();
        ipAddress =  new quint8[4];
        ipAddress[0] = *(routerAddress);
        ipAddress[1] = *(routerAddress+1);
        ipAddress[2] = *(routerAddress+2);
        ipAddress[3] = 2;
        server.append(new Server(new NetworkCard(new IPAddress(ipAddress), MACAddress::getRandomAddress())));
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

