#include "ethernetframe.h"

using namespace NetSim;

EthernetFrame::EthernetFrame(const RawData &data)
{
    m_headerData = data;
}

void EthernetFrame::setDestination(const MACAddress &destination)
{
    m_headerData.setBytes(0, destination.data());
}

void EthernetFrame::setSource(const MACAddress &source)
{
    m_headerData.setBytes(6, source.data());
}

void EthernetFrame::setType(const RawData &type)
{
    m_headerData.setBytes(12, type);
}

MACAddress EthernetFrame::destinationData() const
{
    return MACAddress(m_headerData.getBytes(6, 6));
}

MACAddress EthernetFrame::sourceData() const
{
    return MACAddress(m_headerData.getBytes(0, 6));
}

RawData EthernetFrame::type() const
{
    return m_headerData.getBytes(12, 2);
}

RawData EthernetFrame::data() const
{
    return m_headerData;
}
