#ifndef DNSENTRY_H
#define DNSENTRY_H

#include "src/models/rawdata.h"

//! \file dnsentry.h
//! \ingroup NetSimDNSEntry
//! \brief Contains the DNSEntry class definition.

namespace NetSim {

//! Enumeration to represent various Resource Record attributes.
enum RRAttribute { FULL_DATA, NAME, TYPE, CLASS, TTL, DATA_LENGTH, DATA };

//! \defgroup NetSimDNSEntry DNS Entry
//! \brief Represents a DNS Resource Record.

/**
 * @class DNSEntry
 * @ingroup NetSimDNSEntry
 * @brief Represents a DNS entry (Resource Record).
 *
 * This class provides a representation of a DNS entry or Resource Record (RR).
 * A Resource Record contains data related to a specific domain name and can
 * include the type of the record, its class, a time-to-live, and the data
 * itself.
 */
class DNSEntry {
public:
  //! @brief Default constructor.
  DNSEntry() = default;

  DNSEntry(const RawData& data);

  DNSEntry(const RawData& name, const RawData& type, const RawData& dnsClass);

  DNSEntry(const QString& name, quint16 type, quint16 dnsClass, quint32 ttl, quint16 rDataLength, const RawData& rData);

  //! @brief Returns the domain name.
  QString name() const;

  //! @brief Returns the type of the DNS entry.
  quint16 type() const;

  //! @brief Returns the class of the DNS entry.
  quint16 dnsClass() const;

  //! @brief Returns the time-to-live value.
  quint32 ttl() const;

  //! @brief Returns the length of the data.
  quint16 rDataLength() const;

  //! @brief Returns the rdata associated with the entry.
  RawData rData() const;

  //! @brief Returns the data associated with the entry.
  RawData data() const;

private:
  static RawData stringToRawData(const QString& string);
  static QString rawDataToString(const RawData& data);

  //! @brief The data associated with the entry.
  RawData m_data{};
};
} // namespace NetSim

#endif // DNSENTRY_H
