#include "dnsentry.h"
#include <QDebug>

using namespace NetSim;

DNSEntry::DNSEntry(const RawData& data) : m_data(data) {}

DNSEntry::DNSEntry(const RawData& name, const RawData& type, const RawData& dnsClass)
{
    m_data << name << type << dnsClass;
}

DNSEntry::DNSEntry(const QString& name, quint16 type, quint16 dnsClass, quint32 ttl, quint16 rDataLength, const RawData& rData)
{
    m_data << stringToRawData(name) << type << dnsClass << ttl << rDataLength << rData;
}

QString DNSEntry::name() const
{
    qsizetype nameLength;
    for (nameLength = 0; nameLength < m_data.size()/8; nameLength++) {
        if(m_data.getByte(nameLength) == 0) break;
    }
    return rawDataToString(m_data.getBytes(0, nameLength));
}

quint16 DNSEntry::type() const
{
    qsizetype nameLength;
    for (nameLength = 0; nameLength < m_data.size()/8; nameLength++) {
        if(m_data.getByte(nameLength) == 0) break;
    }
    return static_cast<quint16>(m_data.getBytes(nameLength, 2));
}

quint16 DNSEntry::dnsClass() const
{
    qsizetype nameLength;
    for (nameLength = 0; nameLength < m_data.size()/8; nameLength++) {
        if(m_data.getByte(nameLength) == 0) break;
    }
    return static_cast<quint16>(m_data.getBytes(nameLength + 2, 2));
}

quint32 DNSEntry::ttl() const
{
    qsizetype nameLength;
    for (nameLength = 0; nameLength < m_data.size()/8; nameLength++) {
        if(m_data.getByte(nameLength) == 0) break;
    }
    if(m_data.size() / 8 <= (nameLength + 4)) return 0;
    return static_cast<quint32>(m_data.getBytes(nameLength + 4, 4));
}

quint16 DNSEntry::rDataLength() const {
    qsizetype nameLength;
    for (nameLength = 0; nameLength < m_data.size()/8; nameLength++) {
        if(m_data.getByte(nameLength) == 0) break;
    }
    if(m_data.size() / 8 <= (nameLength + 4)) return 0;
    return static_cast<quint16>(m_data.getBytes(nameLength + 8, 2));
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

RawData DNSEntry::stringToRawData(const QString &string)
{
    //Durch den String iterieren und Punkte durch 0x00 ersetzen
    RawData data{8};
    quint8 amount = 0;
    for (int i = 0; i < string.size(); i++) {
        if(string[i] == '.') {
            data << static_cast<quint8>(0);
            data.setByte(i - amount - 1, amount);
            amount = 0;
        } else {
            data << static_cast<quint8>(string[i].toLatin1());
            amount++;
        }
    }
    return data << static_cast<quint8>(0);
}

QString DNSEntry::rawDataToString(const RawData &data)
{
    QString string;
    for (int i = 0; i < data.size()/8; i++) {
        quint8 byte = data.getByte(i);
        if(byte == 0) break;
        string.append(QChar::fromLatin1(byte));
    }
    return string;
}
