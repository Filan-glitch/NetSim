#include "ethernetframe.h"

using namespace NetSim;

EthernetFrame::EthernetFrame(const RawData &data)
{
    m_headerData = data.getBytes(0, 14);
    m_payload = data.getBytes(14, data.size() - 14);
}

EthernetFrame::EthernetFrame(const MACAddress& destinationAddress, const MACAddress& sourceAddress, quint16 type, const RawData &payload)
    : m_payload(payload)
{
    m_headerData.setBytes(0, sourceAddress.data());
    m_headerData.setBytes(6, destinationAddress.data());
    m_headerData.setBytes(12, type);
}

MACAddress EthernetFrame::destinationAddress() const
{
    return MACAddress(m_headerData.getBytes(6, 6));
}

MACAddress EthernetFrame::sourceAddress() const
{
    return MACAddress(m_headerData.getBytes(0, 6));
}

quint16 EthernetFrame::type() const
{
    return static_cast<quint16>(m_headerData.getBytes(12, 2));
}

RawData EthernetFrame::data() const
{
    return m_headerData;
}
