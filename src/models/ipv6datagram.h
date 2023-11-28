#ifndef IPV6DATAGRAM_H
#define IPV6DATAGRAM_H


#include "src/models/ipv6address.h"
#include "src/models/rawdata.h"

namespace NetSim {

class IPv6Datagram
{
    enum Version {
        IPv4 = 4,
        IPv6 = 6
    };

    enum NextHeader {
        HopByHopOptions = 0,
        Routing = 43,
        Fragment = 44,
        AuthenticationHeader = 51,
        EncapsulatingSecurityPayload = 50,
        DestinationOptions = 60,
        Mobility = 135,
        NoNextHeader = 59,
        ICMPv6 = 58,
        TCP = 6,
        UDP = 17,
    };

public:
    IPv6Datagram() = default;
    IPv6Datagram(const RawData& data);
    IPv6Datagram(Version version, const RawData& trafficClass, const RawData& flowLabel, quint16 payloadLength, NextHeader nextHeader, quint8 hopLimit, const IPv6Address& sourceAddress, const IPv6Address& destinationAddress, const RawData& payload);
    Version version() const;
    RawData trafficClass() const;
    RawData flowLabel() const;
    quint16 payloadLength() const;
    NextHeader nextHeader() const;
    quint8 hopLimit() const;
    IPv6Address source() const;
    IPv6Address destination() const;
    RawData data() const;

private:
    RawData m_headerData{320};
    RawData m_payload{};
};
} // namespace NetSim

#endif // IPV6DATAGRAM_H
