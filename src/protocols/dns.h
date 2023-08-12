#ifndef DNS_H
#define DNS_H

#include "src/models/dnsentry.h"
#include "src/models/package.h"

//! \file dns.h
//! \ingroup NetSimDNS
//! \brief Contains the DNS class definition and related enumerations.

namespace NetSim {

//! \defgroup NetSimDNS NetSim DNS
//! \brief Provides functionality related to DNS data manipulation in packages.

/**
 * @enum DNSFlag
 * @ingroup NetSimDNS
 * @brief Flags used in DNS packets to determine various states and responses.
 */
enum DNSFlag {
  REPLY_CODE = 0,
  NON_AUTHENTICATED_DATA = 4,
  ANSWER_AUTHENTICATED = 5,
  RECURSION_AVAILABLE = 7,
  RECURSION_DESIRED = 8,
  TRUNCATED = 9,
  AUTHORITATIVE = 10,
  OPCODE = 11,
  RESPONSE = 15
};

/**
 * @class DNS
 * @ingroup NetSimDNS
 * @brief Provides utility methods to initialize DNS request and response data
 * in packages.
 */
class DNS {
public:
  /**
   * @brief Initializes a DNS request package with the given queries.
   *
   * @param data The package to which the DNS request data will be added.
   * @param queries A list of DNS queries to be added to the request.
   */
  static void initDNSRequest(Package &data, const QList<DNSEntry> queries);

  /**
   * @brief Initializes a DNS response package with the given queries and
   * answers.
   *
   * @param data The package to which the DNS response data will be added.
   * @param queries A list of original DNS queries.
   * @param answers A list of DNS answers for the corresponding queries.
   * @param nxDomain A flag to indicate if the domain in query does not exist.
   */
  static void initDNSResponse(Package &data, const QList<DNSEntry> queries,
                              const QList<DNSEntry> answers, bool nxDomain);

private:
  /**
   * @brief Sets or clears a specific flag in the flags parameter based on the
   * position.
   *
   * @param flags Pointer to the flags value.
   * @param set True to set the flag, False to clear the flag.
   * @param position The position of the flag to set or clear.
   */
  static void setFlag(quint16 *flags, bool set, quint8 position);

  /**
   * @brief Converts a QString into a QVector of bytes.
   *
   * @param string The QString to be converted.
   * @retval QVector<quint8> The byte array representation of the string.
   */
  static QVector<quint8> stringToArray(const QString &string);
};

} // namespace NetSim

#endif // DNS_H
