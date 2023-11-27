#ifndef TCPHEADER_H
#define TCPHEADER_H

#include "src/models/rawdata.h"
class TCPHeader
{
public:
    TCPHeader() = default;
    TCPHeader(const RawData& data);
    void setSourcePort(const RawData& data);
    void setDestinationPort(const RawData& data);
    void setSequenceNumber(const RawData& data);
    void setAcknowledgementNumber(const RawData& data);
    void setDataOffset(const RawData& data);
    void setReserved(const RawData& data);
    void setFlags(const RawData& data);
    void setWindow(const RawData& data);
    void setUrgentPointer(const RawData& data);
    void setOptions(const RawData& data);
    void setPadding(const RawData& data);
    void setData(const RawData& data);
    RawData sourcePort() const;
    RawData destinationPort() const;
    RawData sequenceNumber() const;
    RawData acknowledgementNumber() const;
    RawData dataOffset() const;
    RawData reserved() const;
    RawData flags() const;
    RawData window() const;
    RawData checksum() const;
    RawData urgentPointer() const;
    RawData options() const;
    RawData padding() const;
    RawData data() const;


private:
    RawData m_data{20};
};

#endif // TCPHEADER_H
