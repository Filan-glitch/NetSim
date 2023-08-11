#include "dnsentry.h"

QString DNSEntry::name() const { return m_name; }

quint16 DNSEntry::type() const { return m_type; }

quint16 DNSEntry::dnsClass() const { return m_class; }

quint32 DNSEntry::ttl() const { return m_ttl; }

quint16 DNSEntry::dataLength() const { return m_data.size(); }

QVector<quint8> DNSEntry::data() const { return m_data; }

DNSEntry::DNSEntry(const QString &name, quint16 type, quint16 dnsClass,
                   quint32 ttl, const QVector<quint8> &data)
    : m_name(name), m_type(std::move(type)), m_class(std::move(dnsClass)),
      m_ttl(std::move(ttl)), m_data(data) {}
