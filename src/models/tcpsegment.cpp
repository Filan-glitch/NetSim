#include "tcpsegment.h"

TCPSegment::TCPSegment(const RawData &data)
{
    qsizetype headerSize = (data.getBit(4) | data.getBit(5) << 1 | data.getBit(6) << 2 | data.getBit(7) << 3 ) * 4;
    m_headerData = data.getBytes(0, headerSize);
    m_payload = data.getBytes(headerSize, data.size() - headerSize);
    calculateDataOffset();
    calculateChecksum();
}

TCPSegment::TCPSegment(quint16 sourcePort, quint16 destinationPort, quint32 sequenceNumber, quint32 achnowledgementNumber, bool CWR, bool ECE, bool URG, bool ACK, bool PSH, bool PST, bool SYN, bool FIN, quint16 windowSize, quint16 urgentPointer, const RawData &payload)
    : m_payload(payload)
{
    m_headerData.setBytes(0, sourcePort);
    m_headerData.setBytes(2, destinationPort);
    m_headerData.setBytes(4, sequenceNumber);
    m_headerData.setBytes(8, achnowledgementNumber);
    m_headerData.setBit(13, 1, CWR);
    m_headerData.setBit(13, 2, ECE);
    m_headerData.setBit(13, 3, URG);
    m_headerData.setBit(13, 4, ACK);
    m_headerData.setBit(13, 5, PSH);
    m_headerData.setBit(13, 6, PST);
    m_headerData.setBit(13, 7, SYN);
    m_headerData.setBit(13, 8, FIN);
    m_headerData.setBytes(14, windowSize);
    m_headerData.setBytes(16, urgentPointer);
    calculateDataOffset();
    calculateChecksum();
}

quint16 TCPSegment::sourcePort() const
{
    return m_headerData.getBytes(0, 2);
}

quint16 TCPSegment::destinationPort() const
{
    return m_headerData.getBytes(2, 2);
}

quint32 TCPSegment::sequenceNumber() const
{
    return m_headerData.getBytes(4, 4);
}

quint32 TCPSegment::acknowledgementNumber() const
{
    return m_headerData.getBytes(8, 4);
}

RawData TCPSegment::dataOffset() const
{
    return m_headerData.getBits(96, 4);
}

RawData TCPSegment::flags() const
{
    return m_headerData.getBytes(13, 1);
}

quint16 TCPSegment::windowSize() const
{
    return m_headerData.getBytes(14, 2);
}

quint16 TCPSegment::checksum() const
{
    return m_headerData.getBytes(16, 2);
}

quint16 TCPSegment::urgentPointer() const
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
