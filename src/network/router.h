#ifndef ROUTER_H
#define ROUTER_H

#include "host.h"
#include "natentry.h"
#include "src/models/ipv4address.h"
#include "src/network/networkcard.h"
#include <QHash>
#include <QStack>
#include <QString>

//! \file router.h
//! \ingroup NetSimRouter
//! \brief Contains the Router class definition.

namespace NetSim {

class Host;

//! \defgroup NetSimRouter Router
//! \brief Provides functionalities related to routing packets between networks.

/**
 * @class Router
 * @ingroup NetSimRouter
 * @brief Represents a virtual router with capability to forward packages.
 *
 * The Router class is responsible for simulating the behavior of a network
 * router. It holds information about connected devices and routes packages
 * accordingly.
 */
class Router {
public:
  /**
   * @brief Default constructor.
   */
  Router() = default;

  /**
   * @brief Receives a package and forwards it accordingly.
   *
   * @param data The data package to be processed and forwarded.
   */
  void receivePackage(Package data);

  //! Returns the global IP address of the router.
  IPv4Address globalIpAddress() const;

  //! Returns the network card associated with the router.
  NetworkCard networkCard() const;

  //! Returns the MAC address table mapping IP addresses to MAC addresses.
  QMap<IPv4Address, MACAddress> macTable() const;

  //! Returns the mapping between MAC addresses and connected routers.
  QMap<MACAddress, Router *> routerCable() const;

  //! Returns the mapping between MAC addresses and connected hosts.
  QMap<MACAddress, Host *> hostCable() const;

  //! Returns the mapping of NAT entries and associated ports.
  QMap<Port, NATEntry> NAT() const;

  /**
   * @brief Adds an IP address and its associated MAC address to the router's
   * table.
   *
   * @param ipAddress The IP address to be added.
   * @param macaddress The associated MAC address.
   */
  void addIPAddress(const IPv4Address &ipAddress, const MACAddress &macaddress);

  /**
   * @brief Adds a MAC address and its associated router to the router's table.
   *
   * @param macAddress The MAC address to be added.
   * @param router The associated router.
   */
  void addMACAddress(const MACAddress &macAddress, Router *router);

  /**
   * @brief Adds a MAC address and its associated host to the router's table.
   *
   * @param macAddress The MAC address to be added.
   * @param host The associated host.
   */
  void addMACAddress(const MACAddress &macAddress, Host *host);

  /**
   * @brief Adds a NAT entry and its associated port to the router's NAT table.
   *
   * @param entry The NAT entry to be added.
   * @param port The associated port.
   */
  void addNATEntry(const NATEntry &entry, const Port &port);

private:
  //! @brief Mapping of IP addresses to their associated MAC addresses.
  QMap<IPv4Address, MACAddress> m_macTable{};

  //! @brief Mapping of MAC addresses to connected routers.
  QMap<MACAddress, Router *> m_routerCable{};

  //! @brief Mapping of MAC addresses to connected hosts.
  QMap<MACAddress, Host *> m_hostCable{};

  //! @brief Mapping of ports to their associated NAT entries.
  QMap<Port, NATEntry> m_portToNAT{};

  //! @brief Mapping of NAT entries to their associated ports.
  QMap<NATEntry, Port> m_natToPort{};

  //! @brief The network card associated with the router.
  NetworkCard m_networkCard{NetworkCard(IPv4Address::getRandomAddress(true),
                                        MACAddress::getRandomAddress())};

  //! @brief The global IP address of the router.
  IPv4Address m_globalIpAddress{IPv4Address::getRandomAddress(false)};
};
} // namespace NetSim

#endif // ROUTER_H
