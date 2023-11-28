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
    IPv4Datagram(const RawData& headerData, const RawData& payload);
    void setVersion(const Version version);
    void setTOS(const RawData tos);
    void setIdentification(const RawData identification);
    void setFlags(const bool dontFragment, const bool moreFragements);
    void setFragmentOffset(const RawData fragmentOffset);
    void setTTL(const RawData ttl);
    void setProtocol(const Protocol protocol);
    void setSource(const IPv4Address& source);
    void setDestination(const IPv4Address& destination);
    void appendOption(const RawData& option);
    void setData(const RawData& data);
    void clearOptions();
    Version version() const;
    IHL ihl() const;
    RawData tos() const;
    RawData totalLength() const;
    RawData identification() const;
    bool dontFragment() const;
    bool moreFragments() const;
    RawData fragmentOffset() const;
    RawData ttl() const;
    Protocol protocol() const;
    IPv4Address source() const;
    IPv4Address destination() const;
    RawData options() const;
    RawData data() const;

private:
    void calculateIHL();
    void calculateTotalLength();
    void calculateChecksum();

    RawData m_headerData{160};
    RawData m_payload{};
};
}

#endif // IPV4DATAGRAM_H
