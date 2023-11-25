#ifndef DNSENTRY_H
#define DNSENTRY_H

#include "src/models/ipaddress.h"
#include "src/models/rawdata.h"
#include <QString>

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
  DNSEntry(const QString &name, const QBitArray &type, const  QBitArray& dnsClass, const QBitArray& ttl = QBitArray(),
           const QBitArray &data = QBitArray());

  //! @brief Returns the domain name.
  QString name() const;

  //! @brief Returns the domain name as a QBitArray.
  RawData nameAsQBitArray() const;

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
  QString m_name{};

  //! @brief Type of the DNS entry.
  RawData m_type{2};

  //! @brief Class of the DNS entry.
  RawData m_class{2};

  //! @brief Time-to-live value.
  RawData m_ttl{4};

  //! @brief The data associated with the entry.
  RawData m_data{};
};
} // namespace NetSim

#endif // DNSENTRY_H
