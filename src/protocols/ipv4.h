#ifndef IPV4_H
#define IPV4_H

#include "src/models/ipaddress.h"
#include "src/models/package.h"
#include <QDebug>
#include <QList>
#include <QString>
#include <QVector>

//! \file ipv4.h
//! \ingroup NetSimIPv4
//! \brief Contains the IPv4 class definition.

namespace NetSim {

//! \defgroup NetSimIPv4 IPv4
//! \brief Provides utilities for manipulating and creating IPv4 headers.

//! Enumeration representing IP Flags.
enum IPFlag { MF = 0, DF = 1 };

/**
 * @class IPv4
 * @ingroup NetSimIPv4
 * @brief A static class that provides methods to handle IPv4 headers and their
 * checksum.
 *
 * The IPv4 class offers functionalities to work with IPv4 headers. This
 * includes both the initialization of headers and the computation of the IPv4
 * checksum.
 */
class IPv4 {
public:
  /**
   * @brief Initializes an IPv4 header.
   *
   * @param id Identification for the IP packet.
   * @param DF Don't Fragment flag.
   * @param MF More Fragments flag.
   * @param fragmentOffset Offset for the fragment.
   * @param ttl Time to live.
   * @param protocol Protocol used.
   * @param sourceAddress IP address of the sender.
   * @param destinationAdress IP address of the receiver.
   * @param data Package data.
   */
  static void initHeader(quint16 id, bool DF, bool MF, quint16 fragmentOffset,
                         quint8 ttl, quint8 protocol,
                         const IPAddress &sourceAddress,
                         const IPAddress &destinationAdress, Package &data);

private:
  /**
   * @brief Calculates the IPv4 checksum for the given parameters.
   *
   * @param totalLength Total length of the IP packet.
   * @param id Identification for the IP packet.
   * @param flags IP flags.
   * @param fragOffset Offset for the fragment.
   * @param ttl Time to live.
   * @param protocol Protocol used.
   * @param srcAddress IP address of the sender.
   * @param destAddress IP address of the receiver.
   * @param data Package data.
   * @param dataLength Length of the data.
   * @retval quint16 Computed checksum.
   */
  static quint16 getIPv4Checksum(quint16 totalLength, quint16 id, quint8 flags,
                                 quint16 fragOffset, quint8 ttl,
                                 quint8 protocol,
                                 const QVector<quint8> &srcAddress,
                                 const QVector<quint8> &destAddress,
                                 const char *data, quint16 dataLength);

  /**
   * @brief Sets or clears the specified bit in the flags.
   *
   * @param flags Pointer to the flags.
   * @param set Boolean indicating whether to set (true) or clear (false) the
   * bit.
   * @param position Position of the bit to be set or cleared.
   */
  static void setFlag(quint8 *flags, bool set, quint8 position);
};
} // namespace NetSim

#endif // IPV4_H
