#ifndef DNSENTRY_H
#define DNSENTRY_H

#include "src/models/ipaddress.h"
#include <QString>

//! \file dnsentry.h
//! \ingroup NetSimDNSEntry
//! \brief Contains the DNSEntry class definition.

namespace NetSim {

//! Enumeration to represent various Resource Record attributes.
enum RRAttribute { FULL_DATA, NAME, TYPE, CLASS, TTL, DATA_LENGTH, DATA };

//! \defgroup NetSimDNSEntry NetSim DNS Entry
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
  DNSEntry(const QString &name, quint16 type, quint16 dnsClass, quint32 ttl = 0,
           const QVector<quint8> &data = QVector<quint8>());

  //! @brief Returns the domain name.
  QString name() const;

  //! @brief Returns the type of the DNS entry.
  quint16 type() const;

  //! @brief Returns the class of the DNS entry.
  quint16 dnsClass() const;

  //! @brief Returns the time-to-live value.
  quint32 ttl() const;

  //! @brief Returns the length of the data.
  quint16 dataLength() const;

  //! @brief Returns the data associated with the entry.
  QVector<quint8> data() const;

private:
  //! @brief Domain name.
  QString m_name{};

  //! @brief Type of the DNS entry.
  quint16 m_type{0};

  //! @brief Class of the DNS entry.
  quint16 m_class{0};

  //! @brief Time-to-live value.
  quint32 m_ttl{0};

  //! @brief The data associated with the entry.
  QVector<quint8> m_data{};
};
} // namespace NetSim

#endif // DNSENTRY_H
