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

  /**
   * @brief Constructs a new DNSEntry.
   *
   * @param name Domain name.
   * @param type Type of the DNS entry.
   * @param dnsClass Class of the DNS entry.
   * @param ttl Time-to-live value.
   * @param data The data associated with the entry.
   */
  DNSEntry(const RawData &name, const RawData &type, const  RawData& dnsClass, const RawData& ttl = RawData(),
           const RawData &data = RawData());

  //! @brief Returns the domain name.
  RawData name() const;

  //! @brief Returns the type of the DNS entry.
  RawData type() const;

  //! @brief Returns the class of the DNS entry.
  RawData dnsClass() const;

  //! @brief Returns the time-to-live value.
  RawData ttl() const;

  //! @brief Returns the length of the data.
  RawData dataLength() const;

  //! @brief Returns the data associated with the entry.
  RawData data() const;

private:
  //! @brief Domain name.
  RawData m_name{};

  //! @brief Type of the DNS entry.
  RawData m_type{16};

  //! @brief Class of the DNS entry.
  RawData m_class{16};

  //! @brief Time-to-live value.
  RawData m_ttl{32};

  //! @brief The data associated with the entry.
  RawData m_data{};
};
} // namespace NetSim

#endif // DNSENTRY_H
