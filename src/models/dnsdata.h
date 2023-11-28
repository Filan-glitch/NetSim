#ifndef DNSDATA_H
#define DNSDATA_H

#include "src/models/rawdata.h"

namespace NetSim {

class DNSData
{
public:
    DNSData() = default;
    DNSData(const RawData& data);
    void setTransactionID(const RawData& transactionID);
    void setFlags(const RawData& flags);
    void addQuestion(const RawData& question);
    void addAnswer(const RawData& answer);
    void addAuthority(const RawData& authority);
    void addAdditional(const RawData& additional);
    RawData transactionID() const;
    RawData flags() const;
    RawData questionCount() const;
    RawData answerCount() const;
    RawData authorityCount() const;
    RawData additionalCount() const;
    RawData data() const;

private:
    RawData m_data{};
};
} // namespace NetSim

#endif // DNSDATA_H
