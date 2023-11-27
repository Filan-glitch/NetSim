#ifndef UDPHEADER_H
#define UDPHEADER_H

#include "src/models/rawdata.h"
class UDPHeader
{
public:
    UDPHeader() = default;
    UDPHeader(const RawData& data);
    void setSourcePort(const RawData& data);
    void setDestinationPort(const RawData& data);
    void setLength(const RawData& data);
    RawData sourcePort() const;
    RawData destinationPort() const;
    RawData length() const;
    RawData checksum() const;
    RawData data() const;

private:
    void calculateChecksum();

    RawData m_data{64};
};

#endif // UDPHEADER_H
