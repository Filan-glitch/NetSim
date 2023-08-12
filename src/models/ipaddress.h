#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QRandomGenerator>
#include <QString>
#include <QTextStream>
#include <QVector>

//! \file ipaddress.h
//! \ingroup NetSimIPAddress
//! \brief Contains the IPAddress class definition.

namespace NetSim {

class IPAddress;
} // namespace NetSim

//! \defgroup NetSimIPAddress NetSim IP Address
//! \brief Represents an IP address.

/**
 * @class IPAddress
 * @ingroup NetSimIPAddress
 * @brief Represents an IPv4 address.
 *
 * This class provides functionalities to represent an IPv4 address,
 * and offers various conversion utilities like converting to string,
 * array or an integer format.
 */
class IPAddress {
public:
  //! @brief Default constructor initializing an empty IP address.
  IPAddress();

  /**
   * @brief Constructs an IPAddress from a given byte array.
   *
   * @param address A byte array representing the IP address.
   */
  IPAddress(const QVector<quint8> &address);

  //! @brief Converts the IP address to a string format.
  QString toString() const;

  //! @brief Converts the IP address to a byte array.
  QVector<quint8> toArray() const;

  //! @brief Converts the IP address to an integer format.
  quint32 toInt() const;

  /**
   * @brief Generates a random IP address.
   *
   * If the isLocal parameter is true, the last byte of the IP address is set
   * to 1.
   *
   * @param isLocal Whether the IP address should be local or not.
   * @return A random IP address.
   */
  static IPAddress getRandomAddress(bool isLocal = false);

  /**
   * @brief Overload of the less than operator.
   *
   * Compares this IP address to another based on their integer format.
   *
   * @param other The other IP address to compare against.
   * @return true if this IP address is less than the other, false otherwise.
   */
  bool operator<(const IPAddress &other) const;

  /**
   * @brief Overload of the equality operator.
   *
   * Checks if this IP address is equal to another based on their integer
   * format.
   *
   * @param other The other IP address to compare against.
   * @return true if the IP addresses are equal, false otherwise.
   */
  bool operator==(const IPAddress &other) const;

private:
  //! @brief A byte array representing the IP address.
  QVector<quint8> m_address;
};

#endif // IPADDRESS_H
