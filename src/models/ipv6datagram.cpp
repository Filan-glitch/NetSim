#include "ipv6datagram.h"

IPv6Datagram::IPv6Datagram(const RawData &data)
{
    m_headerData = data.getBytes(0, 40);
    m_payload = data.getBytes(40, data.size() - 40);
}

IPv6Datagram::IPv6Datagram(const RawData &headerData, const RawData &payload)
    : m_headerData(headerData), m_payload(payload) {}

void IPv6Datagram::setVersion(const RawData &version)
{
    m_headerData.setBits(0, version);
}

void IPv6Datagram::setTrafficClass(const RawData &trafficClass)
{
    m_headerData.setBits(4, trafficClass);
}

void IPv6Datagram::setFlowLabel(const RawData &flowLabel)
{
    m_headerData.setBits(8, flowLabel);
}

void IPv6Datagram::setNextHeader(const RawData &nextHeader)
{
    m_headerData.setBytes(6, nextHeader);
}

void IPv6Datagram::setHopLimit(const RawData &hopLimit)
{
    m_headerData.setBytes(7, hopLimit);
}

void IPv6Datagram::setSource(const IPv6Address &source)
{
    m_headerData.setBytes(8, source.address());
}

void IPv6Datagram::setDestination(const IPv6Address &destination)
{
    m_headerData.setBytes(24, destination.address());
}

RawData IPv6Datagram::version() const
{
    return m_headerData.getBits(0, 4);
}

RawData IPv6Datagram::trafficClass() const
{
    return m_headerData.getBits(4, 8);
}

RawData IPv6Datagram::flowLabel() const
{
    return m_headerData.getBits(8, 20);
}

RawData IPv6Datagram::payloadLength() const
{
    return m_headerData.getBytes(4, 2);
}

RawData IPv6Datagram::nextHeader() const
{
    return m_headerData.getBytes(6, 1);
}

RawData IPv6Datagram::hopLimit() const
{
    return m_headerData.getBytes(7, 1);
}

RawData IPv6Datagram::source() const
{
    return m_headerData.getBytes(8, 16);
}

RawData IPv6Datagram::destination() const
{
    return m_headerData.getBytes(24, 16);
}

RawData IPv6Datagram::data() const
{
    return m_headerData << m_payload;
}
