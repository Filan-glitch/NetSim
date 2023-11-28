#ifndef IPV4DATAGRAM_H
#define IPV4DATAGRAM_H

#include "src/models/ipv4address.h"
#include "src/models/rawdata.h"
namespace NetSim {

class IPv4Datagram
{
    enum Version {
        IPv4 = 4,
        IPv6 = 6
    };

    enum IHL {
        MinIHL = 5,
        IHL6 = 6,
        IHL7 = 7,
        IHL8 = 8,
        IHL9 = 9,
        IHL10 = 10,
        IHL11 = 11,
        IHL12 = 12,
        IHL13 = 13,
        IHL14 = 14,
        MaxIHL = 15
    };

    enum Protocol {
        ICMP = 1,
        TCP = 6,
        UDP = 17
    };

public:
    IPv4Datagram() = default;
    IPv4Datagram(const RawData& data);
    IPv4Datagram(quint8 tos, quint16 totalLength, quint16 identification, bool dontFragment, bool moreFragments, quint16 fragmentOffset, quint8 ttl, Protocol protocol, IPv4Address sourceAddress, IPv4Address destinationAddress, const RawData& payload);
    void hop();
    Version version() const;
    IHL ihl() const;
    quint8 tos() const;
    quint16 totalLength() const;
    quint16 identification() const;
    bool dontFragment() const;
    bool moreFragments() const;
    quint16 fragmentOffset() const;
    quint8 ttl() const;
    Protocol protocol() const;
    quint16 headerChecksum() const;
    IPv4Address source() const;
    IPv4Address destination() const;
    RawData options() const;
    RawData data() const;

private:
    void calculateChecksum();

    RawData m_headerData{160};
    RawData m_payload{};
};
}

#endif // IPV4DATAGRAM_H
