#include "ipv4datagram.h"

using namespace NetSim;

IPv4Datagram::IPv4Datagram(const RawData &data)
{
    m_data = data;
}

void IPv4Datagram::setVersion(const Version version)
{
    if(version == Version::IPv4)
    {
        m_data.setBit(2, false);
    }
    else if(version == Version::IPv6)
    {
        m_data.setBit(1, true);
        m_data.setBit(2, true);
    }
    else
    {
        throw std::invalid_argument("Invalid version");
    }
}

void IPv4Datagram::setIHL(const IHL ihl)
{
    switch(ihl) {
    case IHL::MinIHL:
        m_data.setBit(4, true);
        m_data.setBit(5, false);
        m_data.setBit(6, true);
        m_data.setBit(7, false);
        break;
    case IHL::IHL6:
        m_data.setBit(4, false);
        m_data.setBit(5, true);
        m_data.setBit(6, true);
        m_data.setBit(7, false);
        break;
    case IHL::IHL7:
        m_data.setBit(4, true);
        m_data.setBit(5, true);
        m_data.setBit(6, true);
        m_data.setBit(7, false);
        break;
    case IHL::IHL8:
        m_data.setBit(4, false);
        m_data.setBit(5, false);
        m_data.setBit(6, false);
        m_data.setBit(7, true);
        break;
    case IHL::IHL9:
        m_data.setBit(4, true);
        m_data.setBit(5, false);
        m_data.setBit(6, false);
        m_data.setBit(7, true);
        break;
    case IHL::IHL10:
        m_data.setBit(4, false);
        m_data.setBit(5, true);
        m_data.setBit(6, false);
        m_data.setBit(7, true);
        break;
    case IHL::IHL11:
        m_data.setBit(4, true);
        m_data.setBit(5, true);
        m_data.setBit(6, false);
        m_data.setBit(7, true);
        break;
    case IHL::IHL12:
        m_data.setBit(4, false);
        m_data.setBit(5, false);
        m_data.setBit(6, true);
        m_data.setBit(7, true);
        break;
    case IHL::IHL13:
        m_data.setBit(4, true);
        m_data.setBit(5, false);
        m_data.setBit(6, true);
        m_data.setBit(7, true);
        break;
    case IHL::IHL14:
        m_data.setBit(4, false);
        m_data.setBit(5, true);
        m_data.setBit(6, true);
        m_data.setBit(7, true);
        break;
    case IHL::MaxIHL:
        m_data.setBit(4, true);
        m_data.setBit(5, true);
        m_data.setBit(6, true);
        m_data.setBit(7, true);
        break;
    }
}

void IPv4Datagram::setTOS(const RawData tos)
{
    m_data.setBytes(1, tos);
}

void IPv4Datagram::setTotalLength(const RawData totalLength)
{
    m_data.setBytes(2, totalLength);
}

void IPv4Datagram::setIdentification(const RawData identification)
{
    m_data.setBytes(4, identification);
}

void IPv4Datagram::setFlags(const bool dontFragment, const bool moreFragements)
{
    m_data.setBit(6, 6, dontFragment);
    m_data.setBit(6, 5, moreFragements);
}

void IPv4Datagram::setFragmentOffset(const RawData fragmentOffset)
{
    m_data.setBits(6, 3, fragmentOffset);
}

void IPv4Datagram::setTTL(const RawData ttl)
{
    m_data.setBytes(8, ttl);
}

void IPv4Datagram::setProtocol(const Protocol protocol)
{

    //m_data.setBytes(9, );
    //TODO: Implement Conversion from Protocol to RawData
}

void IPv4Datagram::setSource(const IPv4Address &source)
{
    //TODO: Implement Conversion from IPv4Address to RawData
}

void IPv4Datagram::setDestination(const IPv4Address &destination)
{
    //TODO: Implement Conversion from IPv4Address to RawData
}
