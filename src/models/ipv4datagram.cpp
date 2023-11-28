#include "ipv4datagram.h"

using namespace NetSim;

IPv4Datagram::IPv4Datagram(const RawData &data)
{
    qsizetype headerSize = (data.getBit(0) | data.getBit(1) << 1 | data.getBit(2) << 2 | data.getBit(3) << 3 ) * 4;
    m_headerData = data.getBytes(0, headerSize);
    m_payload = data.getBytes(headerSize, data.size() - headerSize);
}

IPv4Datagram::IPv4Datagram(const RawData &headerData, const RawData &payload)
    : m_headerData(headerData), m_payload(payload)
{
    calculateChecksum();
}

void IPv4Datagram::setVersion(const Version version)
{
    if(version == Version::IPv4)
    {
        m_headerData.setBit(2, false);
    }
    else if(version == Version::IPv6)
    {
        m_headerData.setBit(1, true);
        m_headerData.setBit(2, true);
    }
    else
    {
        throw std::invalid_argument("Invalid version");
    }
}

void IPv4Datagram::setTOS(const RawData tos)
{
    m_headerData.setBytes(1, tos);
}

void IPv4Datagram::setIdentification(const RawData identification)
{
    m_headerData.setBytes(4, identification);
}

void IPv4Datagram::setFlags(const bool dontFragment, const bool moreFragements)
{
    m_headerData.setBit(6, 6, dontFragment);
    m_headerData.setBit(6, 5, moreFragements);
}

void IPv4Datagram::setFragmentOffset(const RawData fragmentOffset)
{
    m_headerData.setBits(6, 3, fragmentOffset);
}

void IPv4Datagram::setTTL(const RawData ttl)
{
    m_headerData.setBytes(8, ttl);
}

void IPv4Datagram::setProtocol(const Protocol protocol)
{
    switch(protocol) {
        case ICMP:
            m_headerData.setBytes(9, 1);
            break;
         case TCP:
            m_headerData.setBytes(9, 6);
            break;
         case UDP:
            m_headerData.setBytes(9, 17);
            break;
    }
}

void IPv4Datagram::setSource(const IPv4Address &source)
{
    m_headerData.setBytes(12, source.address());
}

void IPv4Datagram::setDestination(const IPv4Address &destination)
{
    m_headerData.setBytes(13, destination.address());
}

void IPv4Datagram::calculateIHL()
{
    IHL ihl = IHL(m_headerData.size() / 8);
    switch(ihl) {
    case IHL::MinIHL:
            m_headerData.setBit(4, true);
            m_headerData.setBit(5, false);
            m_headerData.setBit(6, true);
            m_headerData.setBit(7, false);
            break;
    case IHL::IHL6:
            m_headerData.setBit(4, false);
            m_headerData.setBit(5, true);
            m_headerData.setBit(6, true);
            m_headerData.setBit(7, false);
            break;
    case IHL::IHL7:
            m_headerData.setBit(4, true);
            m_headerData.setBit(5, true);
            m_headerData.setBit(6, true);
            m_headerData.setBit(7, false);
            break;
    case IHL::IHL8:
            m_headerData.setBit(4, false);
            m_headerData.setBit(5, false);
            m_headerData.setBit(6, false);
            m_headerData.setBit(7, true);
            break;
    case IHL::IHL9:
            m_headerData.setBit(4, true);
            m_headerData.setBit(5, false);
            m_headerData.setBit(6, false);
            m_headerData.setBit(7, true);
            break;
    case IHL::IHL10:
            m_headerData.setBit(4, false);
            m_headerData.setBit(5, true);
            m_headerData.setBit(6, false);
            m_headerData.setBit(7, true);
            break;
    case IHL::IHL11:
            m_headerData.setBit(4, true);
            m_headerData.setBit(5, true);
            m_headerData.setBit(6, false);
            m_headerData.setBit(7, true);
            break;
    case IHL::IHL12:
            m_headerData.setBit(4, false);
            m_headerData.setBit(5, false);
            m_headerData.setBit(6, true);
            m_headerData.setBit(7, true);
            break;
    case IHL::IHL13:
            m_headerData.setBit(4, true);
            m_headerData.setBit(5, false);
            m_headerData.setBit(6, true);
            m_headerData.setBit(7, true);
            break;
    case IHL::IHL14:
            m_headerData.setBit(4, false);
            m_headerData.setBit(5, true);
            m_headerData.setBit(6, true);
            m_headerData.setBit(7, true);
            break;
    case IHL::MaxIHL:
            m_headerData.setBit(4, true);
            m_headerData.setBit(5, true);
            m_headerData.setBit(6, true);
            m_headerData.setBit(7, true);
            break;
    }
}

void IPv4Datagram::calculateTotalLength()
{
    RawData totalLength(16);
    for(int i = 0; i < 16; i++)
    {
            totalLength.setBit(i,  (((m_payload.size() + m_headerData.size()) / 8) >> i) & 1);
    }
    m_headerData.setBytes(2, totalLength);
}

void IPv4Datagram::calculateChecksum()
{
    m_headerData.setBytes(10, RawData(16));
}
