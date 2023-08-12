#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include "src/network/client.h"
#include "src/network/router.h"
#include "src/network/server.h"
#include <QString>

//! \file simulationmanager.h
//! \ingroup NetSimSimulation
//! \brief Contains the SimulationManager class definition.

namespace NetSim {

//! \defgroup NetSimSimulation NetSim Simulation Management
//! \brief Provides utilities to manage and simulate a network with clients,
//! servers, and routers.

/**
 * @class SimulationManager
 * @ingroup NetSimSimulation
 * @brief Manages and simulates a network consisting of clients, servers, and
 * routers.
 *
 * The SimulationManager class serves as a core component to create and manage
 * the various entities in the network such as clients, servers, and routers. It
 * also integrates with the PackageTableModel to simulate packet flow through
 * the network.
 */
class SimulationManager {

public:
  /**
   * @brief Constructs a new simulation manager with the specified amounts of
   * clients and servers, and domains.
   *
   * @param clientAmount Number of clients.
   * @param serverAmount Number of servers.
   * @param domains List of domain names.
   */
  explicit SimulationManager(quint8 clientAmount, quint8 serverAmount,
                             QList<QString> domains);

  /**
   * @brief Retrieves the number of clients.
   *
   * @retval quint8 Amount of clients.
   */
  quint8 clientsAmount() const;

  /**
   * @brief Retrieves the number of servers.
   *
   * @retval quint8 Amount of servers.
   */
  quint8 serversAmount() const;

  /**
   * @brief Provides access to the list of servers.
   *
   * @retval QList<Server>* Pointer to the list of servers.
   */
  QList<Server> *servers();

  /**
   * @brief Provides access to the list of clients.
   *
   * @retval QList<Client>* Pointer to the list of clients.
   */
  QList<Client> *clients();

  /**
   * @brief Provides access to the list of routers.
   *
   * @retval QList<Router>* Pointer to the list of routers.
   */
  QList<Router> *routers();

  /**
   * @brief Integrates with a PackageTableModel to simulate packet flow.
   *
   * @param packages Pointer to a PackageTableModel.
   */
  void setPackages(PackageTableModel *packages);

private:
  //! @brief A list storing all the `Server` objects in the simulation.
  QList<Server> m_servers;

  //! @brief A list storing all the `Client` objects in the simulation.
  QList<Client> m_clients;

  //! @brief A list storing all the `Router` objects in the simulation.
  QList<Router> m_routers;
};
} // namespace NetSim

#endif // SIMULATIONMANAGER_H
