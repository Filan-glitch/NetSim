#ifndef NETWORKCARD_H
#define NETWORKCARD_H

#include "src/models/ipv4address.h"
#include "src/models/macaddress.h"
#include "src/models/package.h"

//! \file networkcard.h
//! \ingroup NetSimNetworkCard
//! \brief Contains the Network Card class definition.

namespace NetSim {

//! \defgroup NetSimNetworkCard Network Card
//! \brief Provides functionalities related to networking interface cards.

/**
 * @class NetworkCard
 * @ingroup NetSimNetworkCard
 * @brief Represents a virtual network card with network and physical address
 * capabilities.
 *
 * The NetworkCard class is responsible for simulating the behavior of a network
 * interface card. It can add IP and MAC headers to a data package and provides
 * functionalities related to the network and physical addresses of the card.
 */
class NetworkCard {
public:
  //! @brief Default constructor.
  NetworkCard() = default;

  /**
   * @brief Constructs a NetworkCard object with the given network and physical
   * addresses.
   *
   * @param networkAddress IP address of the network card.
   * @param physicalAddress MAC address of the network card.
   */
  explicit NetworkCard(const IPv4Address &networkAddress,
                       const MACAddress &physicalAddress);

  /**
   * @brief Adds an IP header to the provided data package.
   *
   * @param data Data package to which the IP header should be added.
   * @param protocol Protocol number (e.g., TCP, UDP).
   * @param destinationAddress IP address of the destination.
   */
  void addIPHeader(Package &data, quint8 protocol,
                   const IPv4Address &destinationAddress);

  /**
   * @brief Adds a MAC header to the provided data package.
   *
   * @param data Data package to which the MAC header should be added.
   * @param destinationMACAddress MAC address of the destination.
   * @param etherType Ethertype value that indicates which protocol is
   * encapsulated in the payload.
   */
  void addMACHeader(Package &data, MACAddress destinationMACAddress,
                    quint16 etherType);

  //! Returns the network (IP) address of the network card.
  IPv4Address networkAddress() const;

  //! Returns the physical (MAC) address of the network card.
  MACAddress physicalAddress() const;

private:
  //! @brief IP address of the network card.
  IPv4Address m_networkAddress{};

  //! @brief MAC address of the network card.
  MACAddress m_physicalAddress{};
};
} // namespace NetSim

#endif // NETWORKCARD_H
