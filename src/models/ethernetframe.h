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
    void setDestination(const MACAddress& destination);
    void setSource(const MACAddress& source);
    void setType(const RawData& type);
    MACAddress destinationData() const;
    MACAddress sourceData() const;
    RawData type() const;
    RawData data() const;

private:
    RawData m_headerData{112};
    RawData m_payload{368};
};

}

#endif // ETHERNETFRAME_H
