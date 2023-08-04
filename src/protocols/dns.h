#ifndef DNS_H
#define DNS_H

#include "src/models/package.h"
#include "src/models/dnsentry.h"

class DNS
{
public:
    static void initDNSRequest(Package& data, const QList<DNSEntry> queries, quint16 Flags = 0x0100);
    static void initDNSResponse(Package& data, const QList<DNSEntry> queries, const QList<DNSEntry> answers, const QList<DNSEntry> authoritativeNameservers, const QList<DNSEntry> additionalRecords, quint16 Flags = 0x8180);
};

#endif // DNS_H
