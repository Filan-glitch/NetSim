#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include "src/network/client.h"
#include "src/network/router.h"
#include "src/network/server.h"
#include <QString>

namespace NetSim {
class SimulationManager;
}

class SimulationManager {

public:
  explicit SimulationManager(quint8 clientAmount, quint8 serverAmount,
                             QList<QString> domains);

  quint8 clientsAmount() const;

  quint8 serversAmount() const;

  QList<Server> *servers();

  QList<Client> *clients();

  QList<Router> *routers();

  void setPackages(PackageTableModel *packages);

private:
  QList<Server> m_servers;

  QList<Client> m_clients;

  QList<Router> m_routers;
};

#endif // SIMULATIONMANAGER_H
