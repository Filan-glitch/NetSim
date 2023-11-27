#ifndef HOST_H
#define HOST_H

#include "src/management/packagetablemodel.h"
#include "src/models/ipv4address.h"
#include "src/models/macaddress.h"
#include "src/models/process.h"
#include "src/network/networkcard.h"
#include <QMap>
#include <QString>

//! \file host.h
//! \ingroup NetSimHost
//! \brief The Host class implements a host in the network.

namespace NetSim {

//! \defgroup NetSimHost Host
//! \brief The Host class implements a host in the network.

class Router;

/**
 * @class Host
 * @ingroup NetSim
 * @brief Represents a network host that can communicate through routers.
 *
 * A host maintains various tables to map processes to ports, IP addresses to
 * MAC addresses, and domain names to IP addresses. It can also maintain cables
 * connected to routers.
 */
class Host {
public:
  //! @brief The default constructor.
  Host() = default;

  /**
   * @brief Constructor that initializes a host with a network card.
   * @param networkCard The network card associated with this host.
   */
  Host(const NetworkCard &networkCard);

  /**
   * @brief Retrieve the process table.
   * @retval QMap<Port, Process> The table mapping ports to processes.
   */
  QMap<Port, Process> processTable() const;

  /**
   * @brief Retrieve the host table.
   * @retval QMap<IPAddress, MACAddress> The table mapping IP addresses to MAC
   * addresses.
   */
  QMap<IPv4Address, MACAddress> hostTable() const;

  /**
   * @brief Retrieve the domain table.
   * @retval QMap<QString, IPAddress> The table mapping domain names to IP
   * addresses.
   */
  QMap<QString, IPv4Address> domainTable() const;

  /**
   * @brief Retrieve the cables table.
   * @retval QMap<MACAddress, Router *> The table mapping MAC addresses to
   * routers.
   */
  QMap<MACAddress, Router *> cables() const;

  /** @brief Retrieve the network card.
   *  @retval NetworkCard The associated network card.
   */
  NetworkCard networkCard() const;

  /**
   * @brief Retrieves the router by its MAC address.
   * @param destinationAddress The MAC address of the router to retrieve.
   * @retval Router* Pointer to the associated router.
   * @throws CableNotFoundException If the MAC address does not map to any
   * router.
   */
  Router *getRouterByMACAddress(const MACAddress &destinationAddress);

  /**
   * @brief Send a package to a destination MAC address.
   * @param data The package to send.
   * @param destinationAddress The MAC address of the destination.
   */
  void sendPackage(Package &data, const MACAddress &destinationAddress);

  /**
   * @brief Pure virtual function to receive a package. Must be implemented in
   * derived classes.
   * @param data The received package.
   */
  virtual void receivePackage(Package data) = 0;

  /**
   * @brief Adds a process to the process table.
   * @param process The process to add.
   */
  void addProcess(const Process &process);

  /**
   * @brief Adds an IP address to MAC address resolution to the ARP table.
   * @param ipAddress The IP address to add.
   * @param macAddress The MAC address to add.
   */
  void addIPAddress(const IPv4Address &ipAddress, const MACAddress &macAddress);

  /**
   * @brief Adds a MAC address to router pointer to the cables table.
   * @param macAddress The MAC address to add.
   * @param router The router to add.
   */
  void addMACAddress(const MACAddress &macAddress, Router *router);

  /**
   * @brief Adds a domain to IP address resolution to the DNS table.
   * @param domain The domain to add.
   * @param ipAddress The IP address to add.
   */
  void addDomain(const QString &domain, const IPv4Address &ipAddress);

  /**
   * @brief Get all the packages associated with this host.
   * @retval PackageTableModel* Pointer to the package table model.
   */
  PackageTableModel *packages() const;

  /**
   * @brief Set the packages for this host.
   * @param packages Pointer to the new package table model.
   */
  void setPackages(PackageTableModel *packages);

  /**
   * @brief Retrieves a process by its name.
   * @param name The name of the process to retrieve.
   * @retval Process& A reference to the retrieved process.
   * @throws std::runtime_error If no process with the given name is found.
   */
  Process &getProcessByName(const QString &name);

  /**
   * @brief Set the host for all processes.
   * @param host Pointer to the new host.
   */
  void setHostOfProcesses(Host *host);

private:
  //! @brief The Map that maps ports to processes.
  QMap<Port, Process> m_processTable{};

  //! @brief The Map that maps IP addresses to MAC addresses.
  QMap<IPv4Address, MACAddress> m_hostTable{};

  //! @brief The Map that maps domain names to IP addresses.
  QMap<QString, IPv4Address> m_domainTable{};

  //! @brief The Map that maps MAC addresses to routers pointer to call receive
  //! function
  QMap<MACAddress, Router *> m_cables{};

  //! @brief The network card of the host.
  NetworkCard m_networkCard{};

  //! @brief A pointer to the table model to add incoming packages to the table.
  PackageTableModel *m_packages{nullptr};
};
} // namespace NetSim

#endif // HOST_H
