#ifndef HEADERUTIL_H
#define HEADERUTIL_H

#include "src/software/01_application_layer/dns.h"
#include "src/software/03_network_layer/ipv4.h"
#include "src/software/00_common/package.h"
#include "src/software/02_transport_layer/tcp.h"
#include <QString>

//! \file headerutil.h
//! \ingroup NetSimHeaderUtil
//! \brief Contains the HeaderUtil class definition.

namespace NetSim {

//! \defgroup NetSimHeaderUtil NetSim HeaderUtil
//! \brief Provides functionality to convert header data to string
//! representations.

/**
 * @class HeaderUtil
 * @ingroup NetSimHeaderUtil
 * @brief A static class that provides methods to convert header data to string.
 *
 * The HeaderUtil class contains static methods that can convert header data to
 * string representations to be displayed in the UI.
 */
class HeaderUtil {
public:
  /**
   * @brief Extracts the MAC Address from a given package.
   *
   * This method extracts the MAC address from a given package and converts it
   * to a string representation. The MAC address can be either the source or the
   * destination address.
   *
   * @param data The package to extract the MAC address from.
   * @param src Whether the source or the destination MAC address should be
   * extracted.
   * @return QString The string representation of the MAC address.
   */
  static QString getMacAddress(const Package &data, bool src);

  /**
   * @brief Extracts the EtherType from a given package.
   *
   * This method extracts the EtherType from a given package and converts it to
   * a string representation.
   *
   * @param data The package to extract the EtherType from.
   * @return QString The string representation of the EtherType.
   */
  static QString getEtherType(const Package &data);

  /**
   * @brief Extracts the IP header length from a given package.
   *
   * This method extracts the IP version from a given package and converts it to
   * a string representation.
   *
   * @param data The package to extract the IP header length from.
   * @return QString The string representation of the IP header length.
   */
  static QString getIPHeaderLength(const Package &data);

  /**
   * @brief Extracts the IP Type of Service from a given package.
   *
   * This method extracts the IP Type of Service from a given package and
   * converts it to a string representation.
   *
   * @param data The package to extract the IP Type of Service from.
   * @return QString The string representation of the IP Type of Service.
   */
  static QString getIPTOS(const Package &data);

  /**
   * @brief Extracts the IP Total Length from a given package.
   *
   * This method extracts the IP Total Length from a given package and converts
   * it to a string representation.
   *
   * @param data The package to extract the IP Total Length from.
   * @return QString The string representation of the IP Total Length.
   */
  static QString getIPTotalLength(const Package &data);

  /**
   * @brief Extracts the IP Identification from a given package.
   *
   * This method extracts the IP Identification from a given package and
   * converts it to a string representation.
   *
   * @param data The package to extract the IP Identification from.
   * @return QString The string representation of the IP Identification.
   */
  static QString getIPIdentification(const Package &data);

  /**
   * @brief Extracts the IP TTL from a given package.
   *
   * This method extracts the IP TTL from a given package and converts it to a
   * string representation.
   *
   * @param data The package to extract the IP TTL from.
   * @return QString The string representation of the IP TTL.
   */
  static QString getIPTTL(const Package &data);

  /**
   * @brief Extracts the IP Protocol from a given package.
   *
   * This method extracts the IP Protocol from a given package and converts it
   * to a string representation.
   *
   * @param data The package to extract the IP Protocol from.
   * @return QString The string representation of the IP Protocol.
   */
  static QString getIPAddress(const Package &data, bool src);

  /**
   * @brief Extracts the IP Flags from a given package.
   *
   * This method extracts the IP Flags from a given package and converts it to a
   * string representation.
   *
   * @param data The package to extract the IP Flags from.
   * @return QString The string representation of the IP Flags.
   */
  static QString getIPFlags(const Package &data);

  /**
   * @brief Extracts a specific IP Flag from a given package.
   *
   * This method extracts a specific IP Flag from a given package and converts
   * it to a string representation.
   *
   * @param data The package to extract the IP Flag from.
   * @param flagName The name of the IP Flag to extract.
   * @return QString The string representation of the IP Flag.
   */
  static QString getIPFlag(const Package &data, const IPFlag &flagName);

  /**
   * @brief Extracts the IP Next Protocol from a given package.
   *
   * This method extracts the IP next protocol from a given package and converts
   * it to a string representation.
   *
   * @param data The package to extract the IP next protocol from.
   * @return QString The string representation of the IP next protocol.
   */
  static QString getIPNextProtocol(const Package &data);

  /**
   * @brief Extracts the IP Checksum from a given package.
   *
   * This method extracts the IP Checksum from a given package and converts it
   * to a string representation.
   *
   * @param data The package to extract the IP Checksum from.
   * @return QString The string representation of the IP Checksum.
   */
  static QString getIPChecksum(const Package &data);

  /**
   * @brief Extracts the IP Fragment Offset from a given package.
   *
   * This method extacts the IP Fragment Offset from a given package and
   * converts it to a string representation.
   *
   * @param data The package to extract the IP Fragment Offset from.
   * @return QString The string representation of the IP Fragment Offset.
   */
  static QString getIPFragmentOffset(const Package &data);

  /**
   * @brief Extracts the Port from a given package.
   *
   * This method extracts the Port from a given package and converts it to a
   * string representation. The method automatically checks if the package is
   * send by UDP or TCP and returns the correct port. The port can either be the
   * source or the destination port.
   *
   * @param data The package to extract the port from.
   * @param src Whether the source or the destination port should be extracted.
   * @return QString The string representation of the port.
   */
  static QString getPort(const Package &data, bool src);

  /**
   * @brief Extracts the TCP Flags from a given package.
   *
   * This method extracts the TCP Flags from a given package and converts it to
   * a string representation.
   *
   * @param data The package to extract the TCP Flags from.
   * @return QString The string representation of the TCP Flags.
   */
  static QString getTCPFlags(const Package &data);

  /**
   * @brief Extracts a specific TCP Flag from a given package.
   *
   * This method extracts a specific TCP Flag from a given package and converts
   * it to a string representation.
   *
   * @param data The package to extract the TCP Flag from.
   * @param flagName The name of the TCP Flag to extract.
   * @return QString The string representation of the TCP Flag.
   */
  static QString getTCPFlag(const Package &data, const TCPFlag &flagName);

  /**
   * @brief Extracts the TCP Sequence Number from a given package.
   *
   * This method extracts the TCP Sequence Number from a given package and
   * converts it to a string representation.
   *
   * @param data The package to extract the TCP Sequence Number from.
   * @return QString The string representation of the TCP Sequence Number.
   */
  static QString getTCPSequenceNumber(const Package &data);

  /**
   * @brief Extracts the TCP Acknowledgement Number from a given package.
   *
   * This method extracts the TCP Acknowledgement Number from a given package
   * and converts it to a string representation.
   *
   * @param data The package to extract the TCP Acknowledgement Number from.
   * @return QString The string representation of the TCP Acknowledgement
   * Number.
   */
  static QString getTCPAcknowledgementNumber(const Package &data);

  /**
   * @brief Extracts the TCP Header Length from a given package.
   *
   * This method extracts the TCP Header Length from a given package and
   * converts it to a string representation.
   *
   * @param data The package to extract the TCP Header Length from.
   * @return QString The string representation of the TCP Header Length.
   */
  static QString getTCPHeaderLength(const Package &data);

  /**
   * @brief Extracts the TCP Window from a given package.
   *
   * This method extracts the TCP Window from a given package and converts it to
   * a string representation.
   *
   * @param data The package to extract the TCP Window from.
   * @return QString The string representation of the TCP Window.
   */
  static QString getTCPWindow(const Package &data);

  /**
   * @brief Extracts the TCP Checksum from a given package.
   *
   * This method extracts the TCP Checksum from a given package and converts it
   * to a string representation.
   *
   * @param data The package to extract the TCP Checksum from.
   * @return QString The string representation of the TCP Checksum.
   */
  static QString getTCPChecksum(const Package &data);

  /**
   * @brief Extracts the TCP Urgent Pointer from a given package.
   *
   * This method extracts the TCP Urgent Pointer from a given package and
   * converts it to a string representation.
   *
   * @param data The package to extract the TCP Urgent Pointer from.
   * @return QString The string representation of the TCP Urgent Pointer.
   */
  static QString getTCPUrgentPointer(const Package &data);

  /**
   * @brief Extracts the UDP Checksum from a given package.
   *
   * This method extracts the UDP Checksum from a given package and converts it
   * to a string representation.
   *
   * @param data The package to extract the UDP Checksum from.
   * @return QString The string representation of the UDP Checksum.
   */
  static QString getUDPChecksum(const Package &data);

  /**
   * @brief Extracts the UDP Length from a given package.
   *
   * This method extracts the UDP Length from a given package and converts it to
   * a string representation.
   *
   * @param data The package to extract the UDP Length from.
   * @return QString The string representation of the UDP Length.
   */
  static QString getUDPLength(const Package &data);

  /**
   * @brief Extracts a specific HTTP Attribute from a given package.
   *
   * This method extracts a specific HTTP Attribute from a given package and
   * converts it to a string representation.
   *
   * @param data The package to extract the HTTP Attribute from.
   * @param attributeName The name of the HTTP Attribute to extract.
   * @return QString The string representation of the HTTP Attribute.
   */
  static QString getHTTPAttribute(const Package &data,
                                  const QString &attributeName);

  /**
   * @brief Extracts if the package is a response or request.
   *
   * This method extracts if the package is a response or request and returns
   * the specific boolean.
   *
   * @param data The package to analyze.
   * @return bool Returns true if the given package is a http response.
   */
  static bool getHTTPIsResponse(const Package &data);

  /**
   * @brief Extracts if the package is a request or response.
   *
   * This method extracts if the package is a request or response and returns
   * the specific boolean.
   *
   * @param data The package to analyze.
   * @return bool Returns true if the given package is a http request.
   */
  static bool getHTTPIsRequest(const Package &data);

  /**
   * @brief Extracts the DNS ID from a given package.
   *
   * This method extracts the DNS ID from a given package and converts it to a
   * string representation.
   *
   * @param data The package to extract the DNS ID from.
   * @return QString The string representation of the DNS ID.
   */
  static QString getDNSID(const Package &data);

  /**
   * @brief Extracts the DNS Flags from a given package.
   *
   * This method extracts the DNS Flags from a given package and converts it to
   * a string representation.
   *
   * @param data The package to extract the DNS Flags from.
   * @return QString The string representation of the DNS Flags.
   */
  static QString getDNSFlags(const Package &data);

  /**
   * @brief Extracts a specific DNS Flag from a given package.
   *
   * This method extracts a specific DNS Flag from a given package and converts
   * it to a string representation.
   *
   * @param data The package to extract the DNS Flag from.
   * @param flagName The name of the DNS Flag to extract.
   * @return QString The string representation of the DNS Flag.
   */
  static QString getDNSFlag(const Package &data, const DNSFlag &flagName);

  /**
   * @brief Extracts the DNS Question Count from a given package.
   *
   * This method extracts the DNS Question Count from a given package and
   * converts it to a string representation.
   *
   * @param data The package to extract the DNS Question Count from.
   * @return QString The string representation of the DNS Question Count.
   */
  static QString getDNSQuestions(const Package &data);

  /**
   * @brief Extracts the DNS Answer Count from a given package.
   *
   * This method extracts the DNS Answer Count from a given package and converts
   * it to a string representation.
   *
   * @param data The package to extract the DNS Answer Count from.
   * @return QString The string representation of the DNS Answer Count.
   */
  static QString getDNSAnswerRRs(const Package &data);

  /**
   * @brief Extracts the DNS Query at the given index from a given package.
   *
   * This method extacts the DNS Query at the given index from a given package
   * and converts it to a string representation. It is possible to request
   * specific data, in this case only this data will be returned. As default
   * full data will be returned.
   *
   * @param data The package to extract the DNS Query from.
   * @param index The index of the DNS Query to extract.
   * @param attr The RRAttribute to extract.
   * @return QString The string representation of the DNS Query.
   */
  static QString getDNSQuery(const Package &data, int index,
                             const RRAttribute &attr = RRAttribute::FULL_DATA);

  /**
   * @brief Extracts the DNS Answer at the given index from a given package.
   *
   * This method extacts the DNS Answer at the given index from a given package
   * and converts it to a string representation. It is possible to request
   * specific data, in this case only this data will be returned. As default
   * full data will be returned.
   *
   * @param data The package to extract the DNS Answer from.
   * @param index The index of the DNS Answer to extract.
   * @param attr The RRAttribute to extract.
   * @return QString The string representation of the DNS Answer.
   */
  static QString getDNSAnswer(const Package &data, int index,
                              const RRAttribute &attr = RRAttribute::FULL_DATA);

  /**
   * @brief Extracts the IP Address of the DNS Answer at the given index from a
   * given package.
   *
   * This method extracts the IP Address of the DNS Answer at the given index
   * from a given package and converts it to a reusable format.
   *
   * @param data The package to extract the IP Address from.
   * @param index The index of the DNS Answer to extract.
   * @return IPAddress The IP Address of the DNS Answer.
   */
  static IPAddress getDNSAnswerIPAddress(const Package &data, int index);

  /**
   * @brief Extracts the Port of the DNS Answer at the given index from a given
   * package.
   *
   * This method extracts the Port of the DNS Answer at the given index from a
   * given package and converts it to a reusable format.
   *
   * @param data The package to extract the Port from.
   * @param index The index of the DNS Answer to extract.
   * @return Port The Port of the DNS Answer.
   */
  static QString getPackageLength(const Package &data);

  /**
   * @brief Extracts the Package Top Protocol.
   *
   * This method analyzes the given package and extracts the top level protocol.
   *
   * @param data The package to analyze.
   * @return HeaderType The top level protocol.
   */
  static HeaderType getTopProtocol(const Package &data);

  /**
   * @brief Extracts the IP Address of the IP Protocol from the given package.
   *
   * This method extracts the IP Address of the IP Protocol from the given
   * package and converts it to a reusable format.
   *
   * @param data The package to extract the IP Address from.
   * @param src True if the source IP Address should be extracted, false if the
   * destination IP Address should be extracted.
   * @return IPAddress The IP Address of the IP Protocol.
   */
  static IPAddress getIPAddressAsIPAddress(const Package &data, bool src);

  /**
   * @brief Extracts the Port of the TCP Protocol from the given package.
   *
   * This method extracts the Port of the TCP Protocol from the given package
   * and converts it to a reusable format.
   *
   * @param data The package to extract the Port from.
   * @param src True if the source Port should be extracted, false if the
   * destination Port should be extracted.
   * @return Port The Port of the TCP Protocol.
   */
  static Port getPortAsPort(const Package &data, bool src);
};
} // namespace NetSim

#endif // HEADERUTIL_H
