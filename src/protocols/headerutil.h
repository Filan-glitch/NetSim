#ifndef HEADERUTIL_H
#define HEADERUTIL_H

#include <QString>
#include "src/models/package.h"
#include "tcp.h"
#include "ipv4.h"
#include "dns.h"

/**
 * @brief The HeaderUtil class
 * @par This class gives Utilityfuncionality for packages. All functions are static and return a QString representation of a HeaderAttribute
 */

class HeaderUtil
{
public:

    /**
     * @brief getMacAddress
     * @param data
     * @param src
     * @return Returns the MAC Address, if src is true you get the source Address, otherwise the destination Address
     */
    static QString getMacAddress(const Package &data, bool src);

    /**
     * @brief getEtherType
     * @param data
     * @return Returns the EtherType from the Ethernet II Protocol
     */
    static QString getEtherType(const Package &data);

    /**
     * @brief getIPHeaderLength
     * @param data
     * @return Returns the IP Header Length
     */
    static QString getIPHeaderLength(const Package &data);

    /**
     * @brief getIPTOS
     * @param data
     * @return Returns the IP Type of Service
     */
    static QString getIPTOS(const Package &data);

    /**
     * @brief getIPTotalLength
     * @param data
     * @return Returns the IP Total Length
     */
    static QString getIPTotalLength(const Package &data);

    /**
     * @brief getIPIdentification
     * @param data
     * @return Returns the IP Identification
     */
    static QString getIPIdentification(const Package &data);

    /**
     * @brief getIPTTL
     * @param data
     * @return Returns the IP TTL
     */
    static QString getIPTTL(const Package &data);

    /**
     * @brief getIPAddress
     * @param data
     * @param src
     * @return returns the IPAddress
     * @par Returns the IPAddress of a package. You get the source Address if src is true, otherwise you get the destination Address
     */
    static QString getIPAddress(const Package &data, bool src);

    /**
     * @brief getIPFlag
     * @param data
     * @param flagName
     * @return Returns the IPFlag corresponding to the flag name
     */
    static QString getIPFlags(const Package &data);

    /**
     * @brief getIPFlag
     * @param data
     * @param flagName
     * @return Returns the IPFlag corresponding to the flag name
     */
    static QString getIPFlag(const Package &data, const IPFlag &flagName);

    /**
     * @brief getIPNextProtocol
     * @param data
     * @return Returns the next Protocol after IPv4, currently only UDP and TCP are possible
     */
    static QString getIPNextProtocol(const Package &data);

    /**
     * @brief getIPChecksum
     * @param data
     * @return Returns the IPChecksum
     */
    static QString getIPChecksum(const Package &data);

    /**
     * @brief getIPFragmentOffset
     * @param data
     * @return Returns the IP Fragment Offset
     */
    static QString getIPFragmentOffset(const Package &data);


    /**
     * @brief getPort
     * @param data
     * @param tcp
     * @param src
     * @return returns the port
     * @par Returns the port number of a package. You get the source Port if src is true otherwise you get the destination Port
     */
    static QString getPort(const Package &data, bool src);

    /**
     * @brief getTCPFlag
     * @param data
     * @param flagName
     * @return Returns the tcp flag as true or false corresponding to the flag name
     */
    static QString getTCPFlags(const Package &data);

    /**
     * @brief getTCPFlag
     * @param data
     * @param flagName
     * @return Returns the tcp flag as true or false corresponding to the flag name
     */
    static QString getTCPFlag(const Package &data, const TCPFlag &flagName);

    /**
     * @brief getTCPSequenceNumber
     * @param data
     * @return Returns the TCP Sequence Number
     */
    static QString getTCPSequenceNumber(const Package &data);

    /**
     * @brief getTCPAcknowledgementNumber
     * @param data
     * @return Returns the TCP Acknowledgement Number
     */
    static QString getTCPAcknowledgementNumber(const Package &data);

    /**
     * @brief getTCPHeaderLength
     * @param data
     * @return Returns the TCP Header Length
     */
    static QString getTCPHeaderLength(const Package &data);

    /**
     * @brief getTCPWindowSize
     * @param data
     * @return Returns the TCP Window Size
     */
    static QString getTCPWindow(const Package &data);

    /**
     * @brief getTCPChecksum
     * @param data
     * @return Returns the TCP Checksum
     */
    static QString getTCPChecksum(const Package &data);

    /**
     * @brief getTCPUrgentPointer
     * @param data
     * @return Returns the TCP Urgent Pointer
     */
    static QString getTCPUrgentPointer(const Package &data);

    /**
     * @brief getUDPChecksum
     * @param data
     * @return Returns the UDP Checksum
     */
    static QString getUDPChecksum(const Package &data);

    /**
     * @brief getUDPLength
     * @param data
     * @return Returns the UDP Length
     */
    static QString getUDPLength(const Package &data);

    /**
     * @brief getHTTPAttributeAsString
     * @param data
     * @param attributeName
     * @return Returns the HTTP Headerattribute corresponding to the attributename
     */
    static QString getHTTPAttribute(const Package &data, const QString &attributeName);

    /**
     * @brief getHTTPISResponse
     * @param data
     * @return Returns the HTTP Headerattribute corresponding to the attributename
     */
    static bool getHTTPIsResponse(const Package &data);

    static bool getHTTPIsRequest(const Package &data);

    /**
     * @brief getDNSID
     * @param data
     * @return Returns the Transaction ID of the DNS Protocol
     */
    static QString getDNSID(const Package &data);

    /**
     * @brief getDNSFlags
     * @param data
     * @return Returns the Flags of the DNS Protocol
     */
    static QString getDNSFlags(const Package &data);

    /**
     * @brief getDNSFlag
     * @param data
     * @return Returns the Flags of the DNS Protocol
     */
    static QString getDNSFlag(const Package &data, const DNSFlag &flagName);

    /**
     * @brief getDNSQuestions
     * @param data
     * @return Returns the Questions of the DNS Protocol
     */
    static QString getDNSQuestions(const Package &data);

    /**
     * @brief getDNSAnswerRRs
     * @param data
     * @return Returns the Answer RRs of the DNS Protocol
     */
    static QString getDNSAnswerRRs(const Package &data);

    /**
     * @brief getDNSQuery
     * @param data
     * @param index
     * @return Returns a Query of the DNS Protocol
     */
    static QString getDNSQuery(const Package &data, int index, const RRAttribute &attr = RRAttribute::FULL_DATA);

    /**
     * @brief getDNSAnswer
     * @param data
     * @param index
     * @return Returns an Answer of the DNS Protocol
     */
    static QString getDNSAnswer(const Package &data, int index, const RRAttribute &attr = RRAttribute::FULL_DATA);

    /**
     * @brief getDNSName
     * @param data
     * @param index
     * @return Returns a Name of the DNS Protocol
     */
    static QString getPackageLength(const Package &data);

    /**
     * @brief getApplication
     * @param data
     * @return Returns the HeaderType of the Application Protocol
     */
    static HeaderType getApplicationProtocol(const Package &data);


     static IPAddress getIPAddressAsIPAddress(const Package &data, bool src);

    static Port getPortAsPort(const Package &data, bool src);
private:
    /**
     * @brief getHeaderByType
     * @param type
     * @param data
     * @return Returns the corresponding Header to a Headertype in a package
     */
    static Header getHeaderByType(const HeaderType &type, const Package &data);

    /**
     * @brief getHeaderAttributeByName
     * @param name
     * @param header
     * @return Returns the corresponging HeaderAttribute to a HeaderAttributeName in a Header
     */
    static HeaderAttribute getHeaderAttributeByName(const QString &name, const Header &header);
};

#endif // HEADERUTIL_H
