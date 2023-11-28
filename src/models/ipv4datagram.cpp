#include "ipv4datagram.h"

using namespace NetSim;

IPv4Datagram::IPv4Datagram(const RawData &data)
{
    qsizetype headerSize = (data.getBit(0) | data.getBit(1) << 1 | data.getBit(2) << 2 | data.getBit(3) << 3 ) * 4;
    m_headerData = data.getBytes(0, headerSize);
    m_payload = data.getBytes(headerSize, data.size() - headerSize);
}

IPv4Datagram::IPv4Datagram(quint8 tos, quint16 totalLength, quint16 identification, bool dontFragment, bool moreFragments, quint16 fragmentOffset, quint8 ttl, Protocol protocol, IPv4Address sourceAddress, IPv4Address destinationAddress, const RawData &payload)
    : m_payload(payload)
{
    m_headerData.setBit(1, true); //Version
    m_headerData.setBit(5, true);
    m_headerData.setBit(6, true); //IHL
    m_headerData.setByte(1, tos);
    m_headerData.setBytes(2, totalLength);
    m_headerData.setBytes(4, identification);
    m_headerData.setBit(6, 1, dontFragment);
    m_headerData.setBit(6, 2, moreFragments);
    m_headerData.setBits(6, 3, fragmentOffset);
    m_headerData.setByte(8, ttl);
    m_headerData.setByte(9, protocol);
    m_headerData.setBytes(12, sourceAddress.address());
    m_headerData.setBytes(16, destinationAddress.address());
    calculateChecksum();
}

void IPv4Datagram::hop()
{
    if(ttl() - 1 > 0) {
        m_headerData.setByte(8, ttl() - 1);
    } else {
        m_headerData.resize(0);
        m_payload.resize(0);
    }

}

IPv4Datagram::Version IPv4Datagram::version() const
{
    return Version(m_headerData.getBit(0) << 2 | m_headerData.getBit(1) << 1 | m_headerData.getBit(2));
}

IPv4Datagram::IHL IPv4Datagram::ihl() const
{
    return IHL(m_headerData.getBit(4) << 2 | m_headerData.getBit(5) << 1 | m_headerData.getBit(6));
}

quint8 IPv4Datagram::tos() const
{
    return static_cast<quint8>(m_headerData.getByte(1));
}

quint16 IPv4Datagram::totalLength() const
{
    return static_cast<quint16>(m_headerData.getBytes(2, 2));
}

quint16 IPv4Datagram::identification() const
{
    return static_cast<quint16>(m_headerData.getBytes(4, 2));
}

bool IPv4Datagram::dontFragment() const
{
    return m_headerData.getBit(6, 1);
}

bool IPv4Datagram::moreFragments() const
{
    return m_headerData.getBit(6, 2);
}

quint16 IPv4Datagram::fragmentOffset() const
{
    return static_cast<quint16>(m_headerData.getBits(6, 3, 13));
}

quint8 IPv4Datagram::ttl() const
{
    return static_cast<quint8>(m_headerData.getByte(8));
}

IPv4Datagram::Protocol IPv4Datagram::protocol() const
{
    return Protocol(static_cast<quint8>(m_headerData.getByte(9)));
}

quint16 IPv4Datagram::headerChecksum() const
{
    return static_cast<quint16>(m_headerData.getBytes(10, 2));
}

IPv4Address IPv4Datagram::source() const
{
    return IPv4Address(m_headerData.getBytes(12, 4));
}

IPv4Address IPv4Datagram::destination() const
{
    return IPv4Address(m_headerData.getBytes(16, 4));
}

RawData IPv4Datagram::data() const
{
    return m_headerData;
}

void IPv4Datagram::calculateChecksum()
{
    m_headerData.setBytes(10, RawData(16));
}
