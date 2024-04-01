#ifndef UDPDATAGRAM_H
#define UDPDATAGRAM_H

#include "src/models/rawdata.h"

class UDPDatagram
{
public:
    UDPDatagram() = default;
    UDPDatagram(const RawData& data);
    UDPDatagram(quint16 sourcePort, quint16 destinationPort, const RawData& payload);
    quint16 sourcePort() const;
    quint16 destinationPort() const;
    quint16 length() const;
    quint16 checksum() const;
    RawData data() const;


private:
    void calculateChecksum();
    void calculateLength(qsizetype payloadSize);

    RawData m_headerData{64};
    RawData m_payload{};
};

#endif // UDPDATAGRAM_H
