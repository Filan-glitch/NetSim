#include "dnsprocess.h"
#include "src/models/dnsdata.h"

using namespace NetSim;

DNSProcess::DNSProcess() : Process(Port(53), "DNS Process") {}

void DNSProcess::handleData(const RawData &data)
{
    DNSData dnsData(data);
}

