#ifndef TCP_H
#define TCP_H

#include "src/models/ipv4address.h"
#include "src/models/package.h"
#include "src/models/port.h"
#include <QDebug>
#include <QString>
#include <QVector>

//! \file tcp.h
//! \ingroup NetSimTCP
//! \brief Contains the TCP class definition.

namespace NetSim {

//! \enum TCPFlag
//! \brief TCP Flags used for the TCP header.
enum TCPFlag {
  FIN = 0,
  SYN = 1,
  RST = 2,
  PSH = 3,
  ACK = 4,
  URG = 5,
  ECE = 6,
  CWR = 7,
  NS = 8
};

//! \defgroup NetSimTCP TCP
//! \brief The NetSim TCP class provides methods for initializing TCP headers.

/**
 * @class TCP
 * @ingroup NetSimTCP
 * @brief A static class providing methods for initializing TCP headers and
 * managing TCP flags.
 *
 * The TCP class offers functionalities to work with TCP headers, including
 * the initialization of headers and the computation of the TCP checksum.
 */
class TCP {
public:
  /**
   * @brief Initializes a TCP header.
   *
   * @param srcAdress Source IP address.
   * @param destAdress Destination IP address.
   * @param sourcePort Source port.
   * @param destinationPort Destination port.
   * @param seqNumber Sequence number.
   * @param ackNumber Acknowledgment number.
   * @param ack ACK flag.
   * @param psh PSH flag.
   * @param syn SYN flag.
   * @param fin FIN flag.
   * @param window Window size.
   * @param data The package data.
   */
  static void initHeader(const IPAddress &srcAdress,
                         const IPAddress &destAdress, const Port &sourcePort,
                         const Port &destinationPort, quint32 seqNumber,
                         quint32 ackNumber, bool ack, bool psh, bool syn,
                         bool fin, quint16 window, Package &data);

private:
  /**
   * @brief Sets or clears a specific flag in the TCP header flags.
   *
   * @param flags Pointer to the flags variable.
   * @param set If true, sets the flag; if false, clears the flag.
   * @param position Position of the flag to set or clear.
   */
  static void setFlag(quint16 *flags, bool set, quint16 position);

  /**
   * @brief Calculates the TCP checksum for the provided data.
   *
   * @param sourceAddress Source IP address.
   * @param destinationAddress Destination IP address.
   * @param sourcePort Source port.
   * @param destinationPort Destination port.
   * @param seqNumber Sequence number.
   * @param ackNumber Acknowledgment number.
   * @param flags TCP header flags.
   * @param data TCP payload data.
   * @param dataLength Length of the TCP payload data.
   * @retval quint16 The computed TCP checksum.
   */
  static quint16 getTCPChecksum(const QVector<quint8> &sourceAddress,
                                const QVector<quint8> &destinationAddress,
                                quint16 sourcePort, quint16 destinationPort,
                                quint32 seqNumber, quint32 ackNumber,
                                quint16 flags, const char *data,
                                quint16 dataLength);
};

} // namespace NetSim

#endif // TCP_H
