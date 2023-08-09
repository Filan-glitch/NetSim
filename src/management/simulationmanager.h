#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include "src/network/client.h"
#include "src/network/router.h"
#include "src/network/server.h"
#include <QString>

class SimulationManager
{
public:
    SimulationManager(quint8 clientAmount, quint8 serverAmount, QList<QString> domains);
    quint8 getClientsAmount() const;
    quint8 getServerAmount() const;

    QList<Server>* getServer();
    QList<Client>* getClients();
    QList<Router>* getRouters();

private:
    QList<Server> server;
    QList<Client> clients;
    QList<Router> routers;
};

#endif // SIMULATIONMANAGER_H
