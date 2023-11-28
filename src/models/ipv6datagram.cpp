#include "ipv6datagram.h"

using namespace NetSim;

IPv6Datagram::IPv6Datagram(const RawData &data)
{
    m_headerData = data.getBytes(0, 40);
    m_payload = data.getBytes(40, data.size() - 40);
}

IPv6Datagram::IPv6Datagram(Version version, const RawData& trafficClass, const RawData& flowLabel, quint16 payloadLength, NextHeader nextHeader, quint8 hopLimit, const IPv6Address& sourceAddress, const IPv6Address& destinationAddress, const RawData& payload)
    : m_payload(payload)
{
    m_headerData.setBits(0, 4, version);
    m_headerData.setBits(4, 8, trafficClass);
    m_headerData.setBits(12, 20, flowLabel);
    m_headerData.setBits(32, 16, payloadLength);
    m_headerData.setBits(48, 8, nextHeader);
    m_headerData.setBits(56, 8, hopLimit);
    m_headerData.setBytes(64, sourceAddress.address());
    m_headerData.setBytes(80, destinationAddress.address());
}

IPv6Datagram::Version IPv6Datagram::version() const
{
    return IPv6Datagram::Version(static_cast<quint8>(m_headerData.getBits(0, 4)));
}

RawData IPv6Datagram::trafficClass() const
{
    return m_headerData.getBits(4, 8);
}

RawData IPv6Datagram::flowLabel() const
{
    return m_headerData.getBits(8, 20);
}

quint16 IPv6Datagram::payloadLength() const
{
    return static_cast<quint16>(m_headerData.getBytes(4, 2));
}

IPv6Datagram::NextHeader IPv6Datagram::nextHeader() const
{
    return IPv6Datagram::NextHeader(m_headerData.getByte(6));
}

quint8 IPv6Datagram::hopLimit() const
{
    return static_cast<quint8>(m_headerData.getByte(7));
}

IPv6Address IPv6Datagram::source() const
{
    return IPv6Address(m_headerData.getBytes(8, 16));
}

IPv6Address IPv6Datagram::destination() const
{
    return IPv6Address(m_headerData.getBytes(24, 16));
}

RawData IPv6Datagram::data() const
{
    return m_headerData << m_payload;
}
