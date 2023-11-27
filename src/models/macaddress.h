#ifndef MACADDRESS_H
#define MACADDRESS_H

#include "src/models/rawdata.h"
#include <QRandomGenerator>
#include <QString>
#include <QVector>

//! \file macaddress.h
//! \ingroup NetSimMACAddress
//! \brief Contains the MACAddress class definition.

namespace NetSim {

//! \defgroup NetSimMACAddress MAC Address
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
  //! @brief Default constructor initializing an empty MAC address.
  MACAddress() = default;

  /**
   * @brief Constructs a MACAddress from a given byte array.
   *
   * @param address A byte array representing the MAC address.
   */
  explicit MACAddress(const RawData &address);

  //! @brief Converts the MAC address to a string format.
  QString toString() const;

  //! @brief Returns the MAC address as a byte array.
  RawData data() const;

  //! @brief Generates a random MAC address.
  static MACAddress getRandomAddress();

private:
  //! @brief A byte array representing the MAC address.
  RawData m_address{48};
};
} // namespace NetSim

#endif // MACADDRESS_H
