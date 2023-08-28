#ifndef UDP_H
#define UDP_H

#include "src/models/package.h"
#include "src/models/port.h"
#include <QString>

//! \file udp.h
//! \ingroup NetSimUDP
//! \brief Contains the UDP class definition.

namespace NetSim {

//! \defgroup NetSimUDP UDP
//! \brief Provides utilities for working with UDP headers.

/**
 * @class UDP
 * @ingroup NetSimUDP
 * @brief A static class providing methods for initializing UDP headers.
 *
 * The UDP class offers functionalities to work with UDP headers, including
 * the initialization of headers and the computation of the UDP checksum.
 */
class UDP {
public:
  /**
   * @brief Initializes a UDP header.
   *
   * @param sourcePort Source port.
   * @param destinationPort Destination port.
   * @param data The package data.
   */
  static void initHeader(const Port &sourcePort, const Port &destinationPort,
                         Package &data);

private:
  /**
   * @brief Calculates the UDP checksum for the provided data.
   *
   * @param data UDP payload data.
   * @param length Length of the UDP payload data.
   * @param sourcePort Source port.
   * @param destinationPort Destination port.
   * @retval quint16 The computed UDP checksum.
   */
  static quint16 getChecksum(const char *data, quint16 length,
                             quint16 sourcePort, quint16 destinationPort);

  /**
   * @brief Handles overflow for the checksum computation.
   *
   * @param checksum The current computed checksum.
   * @retval quint16 Adjusted checksum after overflow handling.
   */
  static quint16 overflowHandling(quint16 checksum);
};

} // namespace NetSim

#endif // UDP_H
