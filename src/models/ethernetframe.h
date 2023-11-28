#ifndef ETHERNETFRAME_H
#define ETHERNETFRAME_H

#include "src/models/rawdata.h"
#include "src/models/macaddress.h"

namespace NetSim {

class EthernetFrame
{
public:
    EthernetFrame() = default;
    EthernetFrame(const RawData& data);
    EthernetFrame(const MACAddress& destinationAddress, const MACAddress& sourceAddress, quint16 type, const RawData& payload);
    MACAddress destinationAddress() const;
    MACAddress sourceAddress() const;
    quint16 type() const;
    RawData data() const;

private:
    RawData m_headerData{112};
    RawData m_payload{};
};

}

#endif // ETHERNETFRAME_H
