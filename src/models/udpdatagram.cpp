#include "udpdatagram.h"


UDPDatagram::UDPDatagram(const RawData &data)
{
    m_headerData = data.getBytes(0, 8);
    m_payload = data.getBytes(8, data.size()/8 - 8);
}

UDPDatagram::UDPDatagram(quint16 sourcePort, quint16 destinationPort, const RawData &payload)
{
    m_headerData.setBytes(0, RawData() << sourcePort);
    m_headerData.setBytes(2, RawData() << destinationPort);
    calculateLength(payload.size()/8);
    m_payload = payload;
    calculateChecksum();
}

quint16 UDPDatagram::sourcePort() const
{
    return m_headerData.getBytes(0, 2);
}

quint16 UDPDatagram::destinationPort() const
{
    return m_headerData.getBytes(2, 2);
}

quint16 UDPDatagram::length() const
{
    return m_headerData.getBytes(4, 2);
}

quint16 UDPDatagram::checksum() const
{
    return m_headerData.getBytes(6, 2);
}

RawData UDPDatagram::data() const
{
    return m_payload;
}

void UDPDatagram::calculateChecksum()
{
    m_headerData.setBytes(6, RawData{16});
}

void UDPDatagram::calculateLength(qsizetype payloadSize)
{
    RawData size{16};
    for(int i = 0; i < 16; i++)
    {
        size.setBit(i, payloadSize >> i & 1);
    }
}
