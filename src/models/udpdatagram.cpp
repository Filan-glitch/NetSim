#include "udpdatagram.h"


UDPDatagram::UDPDatagram(const RawData &data)
{
    m_headerData = data.getBytes(0, 8);
    m_payload = data.getBytes(8, data.size() - 8);
}

UDPDatagram::UDPDatagram(const RawData &headerData, const RawData &payload)
    : m_headerData(headerData), m_payload(payload)
{
    calculateChecksum();
}

UDPDatagram::UDPDatagram(const RawData &sourcePort, const RawData &destinationPort, const RawData &payload)
{
    m_headerData.setBytes(0, sourcePort);
    m_headerData.setBytes(2, destinationPort);
    calculateLength(payload.size()/8);
    m_payload = payload;
    calculateChecksum();
}

void UDPDatagram::setSourcePort(const RawData &sourcePort)
{
    m_headerData.setBytes(0, sourcePort);
    calculateChecksum();
}

void UDPDatagram::setDestinationPort(const RawData &destinationPort)
{
    m_headerData.setBytes(2, destinationPort);
    calculateChecksum();
}

void UDPDatagram::setPayload(const RawData &payload)
{
    m_payload = payload;
    m_headerData.setBytes(4, payload.size()/8);
    calculateLength(payload.size()/8);
    calculateChecksum();
}

RawData UDPDatagram::sourcePort() const
{
    return m_headerData.getBytes(0, 2);
}

RawData UDPDatagram::destinationPort() const
{
    return m_headerData.getBytes(2, 2);
}

RawData UDPDatagram::length() const
{
    return m_headerData.getBytes(4, 2);
}

RawData UDPDatagram::checksum() const
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
