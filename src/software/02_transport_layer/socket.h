#ifndef SOCKET_H
#define SOCKET_H

//! \file socket.h
//! \ingroup NetSimSocket
//! \brief Contains the Socket class definition.

#include "src/software/03_network_layer/ipaddress.h"
#include "src/software/00_common/package.h"
#include "src/software/02_transport_layer/port.h"

namespace NetSim {

//! \defgroup NetSimSocket Socket
//! \brief Contains the Socket class and its related classes.

class Port;

/**
 * @class Socket
 * @ingroup NetSimSocket
 * @brief Represents a networking socket for transmitting and receiving data.
 *
 * The Socket class encapsulates the functionality of both TCP and UDP
 * protocols. It provides a way to add respective headers to the packages.
 */
class Socket {
public:
  //! @brief Default constructor.
  Socket() = default;

  /**
   * @brief Parameterized constructor.
   *
   * @param sourcePort The source port of the socket.
   * @param destinationPort The destination port to which this socket is
   * communicating.
   */
  Socket(const Port &sourcePort, const Port &destinationPort);

  /**
   * @brief Adds a TCP header to the provided data package.
   *
   * @param data The package that will have the TCP header added.
   * @param srcAddress The source IP address for the TCP header.
   * @param destAddress The destination IP address for the TCP header.
   * @param ack TCP ACK flag.
   * @param psh TCP PSH flag.
   * @param syn TCP SYN flag.
   * @param fin TCP FIN flag.
   *
   * This function calls the functionality of the TCP class to init the TCP
   * header and adds the header to the given package.
   */
  void addTCPHeader(Package &data, const IPAddress &srcAddress,
                    const IPAddress &destAddress, bool ack, bool psh, bool syn,
                    bool fin);

  /**
   * @brief Adds a UDP header to the provided data package.
   *
   * @param data The package that will have the UDP header added.
   */
  void addUDPHeader(Package &data);

  //! Simple Getter for source port.
  Port sourcePort() const;

  //! Setter for the source port.
  void setSourcePort(const Port &sourcePort);

  //! Simple Getter for destination port.
  Port destinationPort() const;

  //! Setter for the destination port.
  void setDestinationPort(const Port &destinationPort);

  //! Simple Getter for start sequence.
  quint32 startSeq() const;

  //! Simple Getter for server sequence.
  quint32 serverSeq() const;

  //! Simple Getter for amount of received data.
  quint32 amountReceivedData() const;

private:
  //! @brief The source port for this socket.
  Port m_sourcePort;

  //! @brief The destination port to which this socket is communicating.
  Port m_destinationPort;

  //! @brief The start sequence number for TCP communication.
  quint32 m_startSeq{100};

  //! @brief The server sequence number for TCP communication.
  quint32 m_serverSeq{0};

  //! @brief The amount of data received by this socket.
  quint32 m_amountReceivedData{0};
};
} // namespace NetSim

#endif // SOCKET_H
