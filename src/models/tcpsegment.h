#ifndef TCPSEGMENT_H
#define TCPSEGMENT_H


#include "src/models/rawdata.h"
class TCPSegment
{
public:
    TCPSegment() = default;
    TCPSegment(const RawData& data);
    TCPSegment(quint16 sourcePort, quint16 destinationPort, quint32 sequenceNumber, quint32 achnowledgementNumber, bool CWR, bool ECE, bool URG, bool ACK, bool PSH, bool PST, bool SYN, bool FIN, quint16 windowSize, quint16 urgentPointer, const RawData& payload);
    quint16 sourcePort() const;
    quint16 destinationPort() const;
    quint32 sequenceNumber() const;
    quint32 acknowledgementNumber() const;
    RawData dataOffset() const;
    RawData flags() const;
    quint16 windowSize() const;
    quint16 checksum() const;
    quint16 urgentPointer() const;
    RawData options() const;


private:
    void calculateChecksum();
    void calculateDataOffset();

    RawData m_headerData{160};
    RawData m_payload{};
};

#endif // TCPSEGMENT_H
