#include "dnsdata.h"

using namespace NetSim;

DNSData::DNSData(const RawData &data) : m_data(data)
{}

void DNSData::setTransactionID(const RawData &transactionID)
{
    m_data.setBytes(0, transactionID);
}

void DNSData::setFlags(const RawData &flags)
{
    m_data.setBytes(2, flags);
}

void DNSData::addQuestion(const RawData &question)
{

}

void DNSData::addAnswer(const RawData &answer)
{

}

void DNSData::addAuthority(const RawData &authority)
{

}

void DNSData::addAdditional(const RawData &additional)
{

}

RawData DNSData::transactionID() const
{
    return m_data.getBytes(0, 2);
}

RawData DNSData::flags() const
{
    return m_data.getBytes(2, 2);
}

RawData DNSData::questionCount() const
{
    return m_data.getBytes(4, 2);
}

RawData DNSData::answerCount() const
{
    return m_data.getBytes(6, 2);
}

RawData DNSData::authorityCount() const
{
    return m_data.getBytes(8, 2);
}

RawData DNSData::additionalCount() const
{
    return m_data.getBytes(10, 2);
}

RawData DNSData::data() const
{
    return m_data;
}
