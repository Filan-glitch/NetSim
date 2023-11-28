#ifndef TCPSEGMENT_H
#define TCPSEGMENT_H


#include "src/models/rawdata.h"
class TCPSegment
{
public:
    TCPSegment() = default;
    TCPSegment(const RawData& data);
    TCPSegment(const RawData& headerData, const RawData& payload);
    void setSourcePort(const RawData& sourcePort);
    void setDestinationPort(const RawData& destinationPort);
    void setSequenceNumber(const RawData& sequenceNumber);
    void setAcknowledgementNumber(const RawData& acknowledgementNumber);
    //void setReserved(const RawData& reserved);
    void setFlags(const RawData& flags);
    void setWindowSize(const RawData& windowSize);
    void setUrgentPointer(const RawData& urgentPointer);
    void appendOption(const RawData& option);
    void setPayload(const RawData& payload);
    void clearOptions();
    RawData sourcePort() const;
    RawData destinationPort() const;
    RawData sequenceNumber() const;
    RawData acknowledgementNumber() const;
    RawData dataOffset() const;
    RawData reserved() const;
    RawData flags() const;
    RawData windowSize() const;
    RawData checksum() const;
    RawData urgentPointer() const;
    RawData options() const;


private:
    void calculateChecksum();
    void calculateDataOffset();

    RawData m_headerData{160};
    RawData m_payload{};
};

#endif // TCPSEGMENT_H
