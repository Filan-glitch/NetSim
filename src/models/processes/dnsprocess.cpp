#include "dnsprocess.h"
#include "src/models/dnsdata.h"

using namespace NetSim;

DNSProcess::DNSProcess() : Process(Port(53), "DNS Process") {}

DNSData DNSProcess::generateRequest(quint16 transactionID, const RawData &opcode, bool truncated, bool recursionDesired, const QList<DNSEntry> &questions)
{
    RawData flags;
    flags << false; // QR
    flags << opcode;
    flags << false; // AA
    flags << truncated;
    flags << recursionDesired;
    flags << false; // recursion available
    flags << false; // reserved
    flags << false; // reserved
    flags << false; // reserved
    flags << false; // response code
    flags << false; // response code
    flags << false; // response code
    flags << false; // response code


  return DNSData(transactionID, flags, questions);
}
