#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include "src/network/client.h"
#include "src/network/router.h"
#include "src/network/server.h"
#include <QString>

class SimulationManager
{
public:
    SimulationManager(quint8 clientAmount, quint8 serverAmount);
    quint8 getClientsAmount() const;
    quint8 getServerAmount() const;

    QList<Server *> getServer() const;
    QList<Client *> getClients() const;
    QList<Router *> getRouters() const;

private:
    QList<Server*> server;
    QList<Client*> clients;
    QList<Router*> routers;
};

#endif // SIMULATIONMANAGER_H
