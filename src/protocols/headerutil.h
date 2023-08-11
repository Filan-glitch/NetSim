#ifndef HEADERUTIL_H
#define HEADERUTIL_H

#include "dns.h"
#include "ipv4.h"
#include "src/models/package.h"
#include "tcp.h"
#include <QString>

namespace NetSim {
class HeaderUtil;
}

class HeaderUtil {
public:
  static QString getMacAddress(const Package &data, bool src);

  static QString getEtherType(const Package &data);

  static QString getIPHeaderLength(const Package &data);

  static QString getIPTOS(const Package &data);

  static QString getIPTotalLength(const Package &data);

  static QString getIPIdentification(const Package &data);

  static QString getIPTTL(const Package &data);

  static QString getIPAddress(const Package &data, bool src);

  static QString getIPFlags(const Package &data);

  static QString getIPFlag(const Package &data, const NetSim::IPFlag &flagName);

  static QString getIPNextProtocol(const Package &data);

  static QString getIPChecksum(const Package &data);

  static QString getIPFragmentOffset(const Package &data);

  static QString getPort(const Package &data, bool src);

  static QString getTCPFlags(const Package &data);

  static QString getTCPFlag(const Package &data, const NetSim::TCPFlag &flagName);

  static QString getTCPSequenceNumber(const Package &data);

  static QString getTCPAcknowledgementNumber(const Package &data);

  static QString getTCPHeaderLength(const Package &data);

  static QString getTCPWindow(const Package &data);

  static QString getTCPChecksum(const Package &data);

  static QString getTCPUrgentPointer(const Package &data);

  static QString getUDPChecksum(const Package &data);

  static QString getUDPLength(const Package &data);

  static QString getHTTPAttribute(const Package &data,
                                  const QString &attributeName);

  static bool getHTTPIsResponse(const Package &data);

  static bool getHTTPIsRequest(const Package &data);

  static QString getDNSID(const Package &data);

  static QString getDNSFlags(const Package &data);

  static QString getDNSFlag(const Package &data,
                            const NetSim::DNSFlag &flagName);

  static QString getDNSQuestions(const Package &data);

  static QString getDNSAnswerRRs(const Package &data);

  static QString
  getDNSQuery(const Package &data, int index,
              const NetSim::RRAttribute &attr = NetSim::RRAttribute::FULL_DATA);

  static QString getDNSAnswer(
      const Package &data, int index,
      const NetSim::RRAttribute &attr = NetSim::RRAttribute::FULL_DATA);

  static IPAddress getDNSAnswerIPAddress(const Package &data, int index);

  static QString getPackageLength(const Package &data);

  static NetSim::HeaderType getTopProtocol(const Package &data);

  static IPAddress getIPAddressAsIPAddress(const Package &data, bool src);

  static Port getPortAsPort(const Package &data, bool src);
};

#endif // HEADERUTIL_H
