#ifndef DNSDATA_H
#define DNSDATA_H

#include "src/models/rawdata.h"
#include <QList>
#include "src/models/dnsentry.h"

namespace NetSim {

class DNSData
{
public:
    DNSData() = default;
    DNSData(const RawData& data);
    DNSData(quint16 transactionID, const RawData& flags, quint16 questionCount,
            quint16 answerCount, quint16 authorityCount, quint16 additionalCount, const QList<DNSEntry>& questions, const QList<DNSEntry>& answers, const QList<DNSEntry>& authorities, const QList<DNSEntry>& additional);
    quint16 transactionID() const;
    RawData flags() const;
    quint16 questionCount() const;
    quint16 answerCount() const;
    quint16 authorityCount() const;
    quint16 additionalCount() const;
    QList<DNSEntry> questions() const;
    QList<DNSEntry> answers() const;
    QList<DNSEntry> authorities() const;
    QList<DNSEntry> additional() const;
    RawData data() const;

private:
    RawData m_data{};
};
} // namespace NetSim

#endif // DNSDATA_H
