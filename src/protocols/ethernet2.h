#ifndef ETHERNET2_H
#define ETHERNET2_H

#include "src/models/macaddress.h"
#include "src/models/package.h"
#include <QString>

//! \file ethernet2.h
//! \ingroup NetSimETHERNET2
//! \brief Contains the ETHERNET2 class definition.

namespace NetSim {

//! \defgroup NetSimETHERNET2 ETHERNET2
//! \brief Provides classes and methods to handle ETHERNET2 headers and their frame.

/**
 * @class Ethernet2
 * @ingroup NetSimETHERNET2
 * @brief A static class that provides methods to handle ETHERNET2 headers
 *
 * The Ethernet2 class offers functionalities to work with Ethernet2 headers. This includes
 * the initialization of headers.
 */
class Ethernet2 {
public:
  /**
   * @brief Initializes a Ethernet2 header.
   *
   * @param data The package data.
   * @param destMACAdress Destination MAC address.
   * @param srcMACAdress Source MAC address.
   * @param etherType Ethernet type.
   */
  static void initHeader(Package &data, const MACAddress &destMACAdress,
                         const MACAddress &srcMACAdress, quint16 etherType);

};

} // namespace NetSim

#endif // ETHERNET2_H
