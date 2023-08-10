#ifndef HEADERUTIL_H
#define HEADERUTIL_H

#include <QString>
#include "src/models/package.h"
#include "tcp.h"
#include "ipv4.h"
#include "dns.h"

class HeaderUtil
{
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

    static QString getIPFlag(const Package &data, const IPFlag &flagName);

    static QString getIPNextProtocol(const Package &data);

    static QString getIPChecksum(const Package &data);

    static QString getIPFragmentOffset(const Package &data);

    static QString getPort(const Package &data, bool src);

    static QString getTCPFlags(const Package &data);

    static QString getTCPFlag(const Package &data, const TCPFlag &flagName);

    static QString getTCPSequenceNumber(const Package &data);

    static QString getTCPAcknowledgementNumber(const Package &data);

    static QString getTCPHeaderLength(const Package &data);

    static QString getTCPWindow(const Package &data);

    static QString getTCPChecksum(const Package &data);

    static QString getTCPUrgentPointer(const Package &data);

    static QString getUDPChecksum(const Package &data);

    static QString getUDPLength(const Package &data);

    static QString getHTTPAttribute(const Package &data, const QString &attributeName);

    static bool getHTTPIsResponse(const Package &data);

    static bool getHTTPIsRequest(const Package &data);

    static QString getDNSID(const Package &data);

    static QString getDNSFlags(const Package &data);

    static QString getDNSFlag(const Package &data, const DNSFlag &flagName);

    static QString getDNSQuestions(const Package &data);

    static QString getDNSAnswerRRs(const Package &data);

    static QString getDNSQuery(const Package &data, int index, const RRAttribute &attr = RRAttribute::FULL_DATA);

    static QString getDNSAnswer(const Package &data, int index, const RRAttribute &attr = RRAttribute::FULL_DATA);

    static IPAddress getDNSAnswerIPAddress(const Package &data, int index);

    static QString getPackageLength(const Package &data);

    static HeaderType getTopProtocol(const Package &data);

    static IPAddress getIPAddressAsIPAddress(const Package &data, bool src);

    static Port getPortAsPort(const Package &data, bool src);

private:
    static Header getHeaderByType(const HeaderType &type, const Package &data);

    static HeaderAttribute getHeaderAttributeByName(const QString &name, const Header &header);
};

#endif // HEADERUTIL_H
