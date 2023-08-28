#ifndef MAC_H
#define MAC_H

#include "src/models/macaddress.h"
#include "src/models/package.h"
#include <QString>

//! \file mac.h
//! \ingroup NetSimMAC
//! \brief Contains the MAC class definition.

namespace NetSim {

//! \defgroup NetSimMAC MAC
//! \brief Provides classes and methods to handle MAC headers and their frame.

/**
 * @class MAC
 * @ingroup NetSimMAC
 * @brief A static class that provides methods to handle MAC headers and their
 * Frame Check Sequence (FCS).
 *
 * The MAC class offers functionalities to work with MAC headers. This includes
 * the initialization of headers and the computation of the Frame Check Sequence
 * (FCS).
 */
class MAC {
public:
  /**
   * @brief Initializes a MAC header.
   *
   * @param data The package data.
   * @param destMACAdress Destination MAC address.
   * @param srcMACAdress Source MAC address.
   * @param etherType Ethernet type.
   */
  static void initHeader(Package &data, const MACAddress &destMACAdress,
                         const MACAddress &srcMACAdress, quint16 etherType);

private:
  /**
   * @brief Calculates the Frame Check Sequence (FCS) for the given parameters.
   *
   * @param destMACAdress Destination MAC address.
   * @param srcMACAdress Source MAC address.
   * @param etherType Ethernet type.
   * @param data The package data.
   * @retval quint32 The computed FCS value.
   */
  static quint32 getFCS(const MACAddress &destMACAdress,
                        const MACAddress &srcMACAdress, quint16 etherType,
                        const Package &data);

  /**
   * @brief Calculates the CRC-32 checksum for the provided data.
   *
   * @param data The data for which the CRC-32 checksum is to be calculated.
   * @retval quint32 The computed CRC-32 checksum.
   */
  static quint32 calculateCRC32(const QByteArray &data);
};

} // namespace NetSim

#endif // MAC_H
