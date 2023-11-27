#include "dnsentry.h"
#include <QDebug>

using namespace NetSim;

DNSEntry::DNSEntry(const RawData &name, const RawData &type, const RawData &dnsClass,
                   const RawData &ttl, const RawData &data)
    : m_name(name), m_type(type), m_class(dnsClass),
    m_ttl(ttl), m_data(data) {}


RawData DNSEntry::name() const { return m_name; }

RawData DNSEntry::type() const { return m_type; }

RawData DNSEntry::dnsClass() const { return m_class; }

RawData DNSEntry::ttl() const { return m_ttl; }

RawData DNSEntry::dataLength() const {
    RawData length(16);
    qsizetype dLength = m_data.size()/8;
    if(dLength > 65535) qWarning() << ("DNS data length is too long");
    for (auto i = 0; i < 16; i++) {
        length.setBit(i, (dLength >> i) & 1);
    }
    return length;
}

RawData DNSEntry::data() const { return m_data; }

