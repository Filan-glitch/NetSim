#include "dnsentry.h"

using namespace NetSim;

QString DNSEntry::name() const { return m_name; }

RawData DNSEntry::type() const { return m_type; }

QBitArray DNSEntry::dnsClass() const { return m_class; }

QBitArray DNSEntry::ttl() const { return m_ttl; }

QBitArray DNSEntry::dataLength() const {
    QBitArray length(16);
    qsizetype dLength = m_data.size() * 8;
    for (auto i = 0; i < 16; i++) {
        length[i] = (dLength >> (i - 1) & 1);
    }
    return length;
}

QBitArray DNSEntry::data() const { return m_data; }

DNSEntry::DNSEntry(const QString &name, const QBitArray &type, const QBitArray &dnsClass,
                   const QBitArray &ttl, const QBitArray &data)
    : m_name(name), m_type(type), m_class(dnsClass),
      m_ttl(ttl), m_data(data) {}
