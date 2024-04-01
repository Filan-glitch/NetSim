#ifndef DNSPROCESS_H
#define DNSPROCESS_H

#include "process.h"
#include "src/models/dnsdata.h"

namespace NetSim {

class DNSProcess : public Process
{
public:
    DNSProcess();
    DNSData generateRequest(quint16 transactionID, const RawData& opcode, bool truncated, bool recursionDesired, const QList<DNSEntry>& questions);
    DNSData handle(DNSData data);
};
} // namespace NetSim

#endif // DNSPROCESS_H
