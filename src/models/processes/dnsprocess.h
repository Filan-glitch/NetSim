#ifndef DNSPROCESS_H
#define DNSPROCESS_H

#include "process.h"

namespace NetSim {

class DNSProcess : public Process
{
public:
    DNSProcess();
    virtual void handleData(const RawData& data) override;
};
} // namespace NetSim

#endif // DNSPROCESS_H
