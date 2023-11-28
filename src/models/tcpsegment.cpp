#include "tcpsegment.h"

TCPSegment::TCPSegment(const RawData &data)
{
    qsizetype headerSize = (data.getBit(4) | data.getBit(5) << 1 | data.getBit(6) << 2 | data.getBit(7) << 3 ) * 4;
    m_headerData = data.getBytes(0, headerSize);
    m_payload = data.getBytes(headerSize, data.size() - headerSize);
    calculateDataOffset();
    calculateChecksum();
}

TCPSegment::TCPSegment(const RawData &headerData, const RawData &payload)
    : m_headerData(headerData), m_payload(payload)
{
    calculateDataOffset();
    calculateChecksum();
}

void TCPSegment::setSourcePort(const RawData &sourcePort)
{
    m_headerData.setBytes(0, sourcePort);
    calculateChecksum();
}

void TCPSegment::setDestinationPort(const RawData &destinationPort)
{
    m_headerData.setBytes(2, destinationPort);
    calculateChecksum();
}

void TCPSegment::setSequenceNumber(const RawData &sequenceNumber)
{
    m_headerData.setBytes(4, sequenceNumber);
    calculateChecksum();
}

void TCPSegment::setAcknowledgementNumber(const RawData &acknowledgementNumber)
{
    m_headerData.setBytes(8, acknowledgementNumber);
    calculateChecksum();
}

void TCPSegment::setFlags(const RawData &flags)
{
    m_headerData.setBytes(13, flags);
    calculateChecksum();
}

void TCPSegment::setWindowSize(const RawData &windowSize)
{
    m_headerData.setBytes(14, windowSize);
    calculateChecksum();
}

void TCPSegment::setUrgentPointer(const RawData &urgentPointer)
{
    m_headerData.setBytes(18, urgentPointer);
    calculateChecksum();
}

void TCPSegment::appendOption(const RawData &option)
{
    m_headerData << option;
    calculateDataOffset();
    calculateChecksum();
}

void TCPSegment::setPayload(const RawData &payload)
{
    m_payload = payload;
    calculateChecksum();
}

void TCPSegment::clearOptions()
{
    m_headerData.truncate(160);
    calculateDataOffset();
    calculateChecksum();
}

RawData TCPSegment::sourcePort() const
{
    return m_headerData.getBytes(0, 2);
}

RawData TCPSegment::destinationPort() const
{
    return m_headerData.getBytes(2, 2);
}

RawData TCPSegment::sequenceNumber() const
{
    return m_headerData.getBytes(4, 4);
}

RawData TCPSegment::acknowledgementNumber() const
{
    return m_headerData.getBytes(8, 4);
}

RawData TCPSegment::dataOffset() const
{
    return m_headerData.getBits(96, 4);
}

RawData TCPSegment::reserved() const
{
    return RawData(4);
}

RawData TCPSegment::flags() const
{
    return m_headerData.getBytes(13, 1);
}

RawData TCPSegment::windowSize() const
{
    return m_headerData.getBytes(14, 2);
}

RawData TCPSegment::checksum() const
{
    return m_headerData.getBytes(16, 2);
}

RawData TCPSegment::urgentPointer() const
{
    return m_headerData.getBytes(18, 2);
}

RawData TCPSegment::options() const
{
    if(m_headerData.size() == 160)
        return RawData(0);
    return m_headerData.getBytes(20, m_headerData.size()/8 - 20);
}

void TCPSegment::calculateChecksum()
{
    m_headerData.setBytes(16, RawData(16));
}

void TCPSegment::calculateDataOffset()
{
    RawData dataOffset;
    qsizetype size = m_headerData.size() / 32;
    for(int i = 0; i < 4; i++)
    {
        dataOffset.setBit(3 - i, (size >> i) & 1);
    }

    m_headerData.setBits(96, dataOffset);
}
