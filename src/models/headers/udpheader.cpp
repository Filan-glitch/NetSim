#include "udpheader.h"
#include <QDebug>

UDPHeader::UDPHeader(const RawData &data)
{
    if(data.size() != 64)
        qWarning() << "udpheader::udpheader: data size is not 8 bytes";
    m_data = data;
}

void UDPHeader::setSourcePort(const RawData &data)
{
    if(data.size() != 16)
        qWarning() << "udpheader::setSourcePort: data size is not 16 bits";
    m_data.setBytes(0, data);
}

void UDPHeader::setDestinationPort(const RawData &data)
{
    if(data.size() != 16)
        qWarning() << "udpheader::setDestinationPort: data size is not 16 bits";
    m_data.setBytes(2, data);
}

void UDPHeader::setLength(const RawData &data)
{
    if(data.size() != 16)
        qWarning() << "udpheader::setLength: data size is not 16 bits";
    m_data.setBytes(4, data);
}

RawData UDPHeader::sourcePort() const
{
    return m_data.getBytes(0, 2);
}

RawData UDPHeader::destinationPort() const
{
    return m_data.getBytes(2, 2);
}

RawData UDPHeader::length() const
{
    return m_data.getBytes(4, 2);
}

RawData UDPHeader::checksum() const
{
    return m_data.getBytes(6, 2);
}

RawData UDPHeader::data() const
{
    return m_data;
}

void UDPHeader::calculateChecksum()
{
    //TODO: implement calculation
    m_data.setBytes(6, RawData(16));
}
