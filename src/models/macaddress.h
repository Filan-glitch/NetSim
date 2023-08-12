#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <QRandomGenerator>
#include <QString>
#include <QVector>

//! \file macaddress.h
//! \ingroup NetSimMACAddress
//! \brief Contains the MACAddress class definition.

namespace NetSim {

class MACAddress;
} // namespace NetSim

//! \defgroup NetSimMACAddress NetSim MAC Address
//! \brief Represents a MAC address.

/**
 * @class MACAddress
 * @ingroup NetSimMACAddress
 * @brief Represents a Media Access Control (MAC) address.
 *
 * This class provides functionalities to represent a MAC address,
 * and offers various conversion utilities like converting to string,
 * array or an integer format.
 */
class MACAddress {
public:
  /**
   * @brief Constructs a MACAddress from a given byte array.
   *
   * @param address A byte array representing the MAC address.
   */
  explicit MACAddress(const QVector<quint8> &address);

  //! @brief Default constructor initializing an empty MAC address.
  MACAddress();

  //! @brief Converts the MAC address to a string format.
  QString toString() const;

  //! @brief Converts the MAC address to a byte array.
  QVector<quint8> toArray() const;

  //! @brief Converts the MAC address to an integer format.
  quint64 toInt() const;

  //! @brief Generates a random MAC address.
  static MACAddress getRandomAddress();

  /**
   * @brief Overload of the less than operator.
   *
   * Compares this MAC address to another based on their integer format.
   *
   * @param other The other MAC address to compare against.
   * @return true if this MAC address is less than the other, false otherwise.
   */
  bool operator<(const MACAddress &other) const;

  /**
   * @brief Overload of the equality operator.
   *
   * Checks if this MAC address is equal to another based on their integer
   * format.
   *
   * @param other The other MAC address to compare against.
   * @return true if the MAC addresses are equal, false otherwise.
   */
  bool operator==(const MACAddress &other) const;

private:
  //! @brief A byte array representing the MAC address.
  QVector<quint8> m_address;
};

#endif // MACADDRESS_H
