#ifndef IPV6DATAGRAM_H
#define IPV6DATAGRAM_H


#include "src/models/ipv6address.h"
#include "src/models/rawdata.h"
class IPv6Datagram
{
public:
    IPv6Datagram() = default;
    IPv6Datagram(const RawData& data);
    IPv6Datagram(const RawData& headerData, const RawData& payload);
    void setVersion(const RawData& version);
    void setTrafficClass(const RawData& trafficClass);
    void setFlowLabel(const RawData& flowLabel);
    void setNextHeader(const RawData& nextHeader);
    void setHopLimit(const RawData& hopLimit);
    void setSource(const IPv6Address& source);
    void setDestination(const IPv6Address& destination);
    RawData version() const;
    RawData trafficClass() const;
    RawData flowLabel() const;
    RawData payloadLength() const;
    RawData nextHeader() const;
    RawData hopLimit() const;
    RawData source() const;
    RawData destination() const;
    RawData data() const;

private:
    RawData m_headerData{320};
    RawData m_payload{};
};

#endif // IPV6DATAGRAM_H
