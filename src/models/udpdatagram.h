#ifndef UDPDATAGRAM_H
#define UDPDATAGRAM_H

#include "src/models/rawdata.h"

class UDPDatagram
{
public:
    UDPDatagram() = default;
    UDPDatagram(const RawData& payload);
    UDPDatagram(const RawData& headerData, const RawData& payload);
    UDPDatagram(const RawData& sourcePort, const RawData& destinationPort, const RawData& payload);
    void setSourcePort(const RawData& sourcePort);
    void setDestinationPort(const RawData& destinationPort);
    void setPayload(const RawData& payload);
    RawData sourcePort() const;
    RawData destinationPort() const;
    RawData length() const;
    RawData checksum() const;
    RawData data() const;


private:
    void calculateChecksum();
    void calculateLength(qsizetype payloadSize);

    RawData m_headerData{64};
    RawData m_payload{};
};

#endif // UDPDATAGRAM_H
