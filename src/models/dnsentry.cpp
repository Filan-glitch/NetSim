#include "dnsentry.h"
#include <QDebug>

using namespace NetSim;

DNSEntry::DNSEntry(const RawData& data) : m_data(data) {}

DNSEntry::DNSEntry(const RawData& name, const RawData& type, const RawData& dnsClass)
{
    m_data << name << type << dnsClass;
}

DNSEntry::DNSEntry(const RawData& name, const RawData& type, const RawData& dnsClass, const RawData& ttl, const RawData& rDataLength, const RawData& rData)
{
    m_data << name << type << dnsClass << ttl << rDataLength << rData;
}

RawData DNSEntry::name() const
{
    qsizetype nameLength;
    for (nameLength = 0; nameLength < m_data.size()/8; nameLength++) {
        if(m_data.getByte(nameLength) == 0) break;
    }
    return m_data.getBytes(0, nameLength);
}

RawData DNSEntry::type() const
{
    qsizetype nameLength;
    for (nameLength = 0; nameLength < m_data.size()/8; nameLength++) {
        if(m_data.getByte(nameLength) == 0) break;
    }
    return m_data.getBytes(nameLength, 2);
}

RawData DNSEntry::dnsClass() const
{
    qsizetype nameLength;
    for (nameLength = 0; nameLength < m_data.size()/8; nameLength++) {
        if(m_data.getByte(nameLength) == 0) break;
    }
    return m_data.getBytes(nameLength + 2, 2);
}

RawData DNSEntry::ttl() const
{
    qsizetype nameLength;
    for (nameLength = 0; nameLength < m_data.size()/8; nameLength++) {
        if(m_data.getByte(nameLength) == 0) break;
    }
    if(m_data.size() / 8 <= (nameLength + 4)) return RawData();
    return m_data.getBytes(nameLength + 4, 4);
}

RawData DNSEntry::rDataLength() const {
    qsizetype nameLength;
    for (nameLength = 0; nameLength < m_data.size()/8; nameLength++) {
        if(m_data.getByte(nameLength) == 0) break;
    }
    if(m_data.size() / 8 <= (nameLength + 4)) return RawData();
    return m_data.getBytes(nameLength + 8, 2);
}

RawData DNSEntry::rData() const
{
    qsizetype nameLength;
    for (nameLength = 0; nameLength < m_data.size()/8; nameLength++) {
        if(m_data.getByte(nameLength) == 0) break;
    }
    if(m_data.size() / 8 <= (nameLength + 4)) return RawData();
    return m_data.getBytes(nameLength + 10, m_data.size() - nameLength - 10);
}

RawData DNSEntry::data() const
{
    return m_data;
}

