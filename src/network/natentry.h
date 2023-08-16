#ifndef NATENTRY_H
#define NATENTRY_H

#include "src/models/ipaddress.h"
#include "src/models/port.h"

//! \file natentry.h
//! \ingroup NetSimNATEntry
//! \brief Contains the NAT Entry class definition.

namespace NetSim {

//! \defgroup NetSimNATEntry NAT Entry
//! \brief Provides the Network Address Translation (NAT) utilities for the
//! NetSim project.

/**
 * @class NATEntry
 * @ingroup NetSimNAT
 * @brief Represents an entry in the NAT table with an IP address and associated
 * port.
 *
 * The NATEntry class is a data structure representing a NAT table entry. It
 * associates an IP address with a specific port and provides utility functions
 * to access and compare them.
 */
class NATEntry {
public:
  /**
   * @brief Constructs a NATEntry with a specified IP address and port.
   * @param address The IP address associated with this NAT entry.
   * @param port The port associated with this NAT entry.
   */
  NATEntry(const IPAddress &address, const Port &port);

  //! @brief Default constructor.
  NATEntry() = default;

  //! @brief Retrieves the port associated with this NAT entry.
  Port port() const;

  //! @brief Retrieves the IP address associated with this NAT entry.
  IPAddress address() const;

  /**
   * @brief Compares two NAT entries based on their port numbers.
   * @param entry The NAT entry to compare with.
   * @return True if the current entry's port number is less than the provided
   * entry's port number.
   */
  bool operator<(const NATEntry &entry) const;

private:
  //! @brief The port associated with this NAT entry.
  Port m_port{};
  //! @brief The IP address associated with this NAT entry.
  IPAddress m_address{};
};
} // namespace NetSim

#endif // NATENTRY_H
