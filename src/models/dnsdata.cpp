#include "dnsdata.h"

using namespace NetSim;

DNSData::DNSData(const RawData &data) : m_data(data)
{}

DNSData::DNSData(quint16 transactionID, const RawData& flags, const QList<DNSEntry>& questions, const QList<DNSEntry>& answers, const QList<DNSEntry>& authorities, const QList<DNSEntry>& additional)
{
    m_data << transactionID << flags << static_cast<quint16>(questions.size()) << static_cast<quint16>(answers.size()) << static_cast<quint16>(authorities.size()) << static_cast<quint16>(additional.size());
    foreach (DNSEntry entry, questions)
        m_data << entry.data();
    foreach (DNSEntry entry, answers)
        m_data << entry.data();
    foreach (DNSEntry entry, authorities)
        m_data << entry.data();
    foreach (DNSEntry entry, additional)
        m_data << entry.data();
}

quint16 DNSData::transactionID() const
{
    return static_cast<quint16>(m_data.getBytes(0, 2));
}

RawData DNSData::flags() const
{
    return m_data.getBytes(2, 2);
}

quint16 DNSData::questionCount() const
{
    return static_cast<quint16>(m_data.getBytes(4, 2));
}

quint16 DNSData::answerCount() const
{
    return static_cast<quint16>(m_data.getBytes(6, 2));
}

quint16 DNSData::authorityCount() const
{
    return static_cast<quint16>(m_data.getBytes(8, 2));
}

quint16 DNSData::additionalCount() const
{
    return static_cast<quint16>(m_data.getBytes(10, 2));
}

RawData DNSData::data() const
{
    return m_data;
}
