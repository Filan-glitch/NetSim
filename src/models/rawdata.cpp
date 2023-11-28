#include "rawdata.h"
#include <stdexcept>

RawData::RawData()
{
    this->m_data = make_unique<QVector<quint8>>(QVector<quint8>());
}

RawData::RawData(const qsizetype size)
{
    qsizetype byteSize = size / 8;
    if (size % 8 != 0)
    {
        byteSize++;
    }
    this->m_size = size;
    this->m_data = make_unique<QVector<quint8>>(QVector<quint8>(byteSize));
}

RawData::RawData(const RawData& other)
{
    this->m_size = other.m_size;
    this->m_data =  make_unique<QVector<quint8>>(QVector<quint8>(*other.m_data));
}

void RawData::clear()
{
    this->m_size = 0;
    this->m_data->clear();
}

void RawData::resize(const qsizetype size)
{
    qsizetype byteSize = size / 8;
    if (size % 8 != 0)
    {
        byteSize++;
    }
    this->m_size = size;
    this->m_data->resize(byteSize);
}

void RawData::flipBit(const qsizetype byteIndex, const qsizetype bitIndex)
{
    if (byteIndex*8 + bitIndex >= this->m_data->size())
    {
        throw std::out_of_range("Bit index out of range");
    }
    this->m_data->operator[](byteIndex) ^= 1 << bitIndex;
}

void RawData::setBit(const qsizetype byteIndex, const qsizetype bitIndex, const bool value)
{
    if (byteIndex*8 + bitIndex >= this->m_data->size())
    {
        throw std::out_of_range("Bit index out of range");
    }
    if (value)
    {
        this->m_data->operator[](byteIndex) |= 1 << bitIndex;
    }
    else
    {
        this->m_data->operator[](byteIndex) &= ~(1 << bitIndex);
    }
}

void RawData::setBit(const qsizetype bitIndex, const bool value)
{
    if(bitIndex >= this->size())
    {
        throw std::out_of_range("Bit index out of range");
    }
    this->setBit(bitIndex / 8, bitIndex % 8, value);
}

void RawData::setBits(const qsizetype byteIndex, const qsizetype bitIndex, const RawData &value)
{
    if(byteIndex*8 + bitIndex + value.size() > this->size())
    {
        throw std::out_of_range("Bit index out of range or value too big");
    }
    for(qsizetype i = 0; i < value.size(); i++)
    {
        this->setBit(byteIndex * 8 + bitIndex + i, value.getBit(i));
    }
}

void RawData::setBits(const qsizetype bitIndex, const RawData &value)
{
    if(bitIndex + value.size() > this->size())
    {
        throw std::out_of_range("Bit index out of range or value too big");
    }
    this->setBits(bitIndex / 8, bitIndex % 8, value);
}

void RawData::setByte(const qsizetype byteIndex, const quint8 value)
{
    if(byteIndex*8 >= this->size())
    {
        throw std::out_of_range("Byte index out of range");
    }
    this->m_data->operator[](byteIndex) = value;
}

void RawData::setBytes(const qsizetype byteIndex, const RawData &value)
{
    if(byteIndex*8 + value.size() > this->size()*8)
    {
        throw std::out_of_range("Byte index out of range or value too big");
    }
    for (int i = 0; i < value.size()/8; i++)
    {
        this->m_data->operator[](byteIndex + i) = value.getByte(i);
    }
}

void RawData::truncate(const qsizetype size)
{
    qsizetype byteSize = size / 8;
    if (size % 8 != 0)
    {
        byteSize++;
    }
    this->m_size = size;
    this->m_data->resize(byteSize);
}

quint8 RawData::getByte(const qsizetype byteIndex) const
{
    if(byteIndex*8 >= this->size())
    {
        throw std::out_of_range("Byte index out of range");
    }
    return this->m_data->operator[](byteIndex);
}

RawData RawData::getBytes(const qsizetype byteIndex, const qsizetype length) const
{
    if(byteIndex*8 + length > this->size()*8)
    {
        throw std::out_of_range("Byte index out of range");
    }
    RawData bytes(length);
    for (int i = 0; i < length; i++)
    {
        bytes.setByte(i, this->getByte(byteIndex + i));
    }
    return bytes;
}

bool RawData::getBit(const qsizetype byteIndex, const qsizetype bitIndex) const
{
    if(byteIndex*8 + bitIndex >= this->size()*8)
    {
        throw std::out_of_range("Bit index out of range");
    }
    return (this->m_data->operator[](byteIndex) >> bitIndex) & 1;
}

bool RawData::getBit(const qsizetype bitIndex) const
{
    return this->getBit(bitIndex/8, bitIndex%8);
}

RawData RawData::getBits(const qsizetype byteIndex, const qsizetype bitIndex, const qsizetype length) const
{
    if(byteIndex*8 + bitIndex + length > this->size()*8)
    {
        throw std::out_of_range("Bit index out of range");
    }
    RawData bits(length);
    for (int i = 0; i < length; i++)
    {
        bits.setBit(i, this->getBit(byteIndex * 8 + bitIndex + i));
    }
    return bits;
}

RawData RawData::getBits(const qsizetype bitIndex, const qsizetype length) const
{
    if(bitIndex + length > this->size())
    {
        throw std::out_of_range("Bit index out of range");
    }
    RawData bits(length);
    for (int i = 0; i < length; i++)
    {
        bits.setBit(i, this->getBit(bitIndex + i));
    }
    return bits;
}

QString RawData::toString(int base) const
{
    QString str;
    for (int i = 0; i < this->m_data->size()/8; i++)
    {
        str += QString::number(this->m_data->operator[](i), base);
        str += " ";
    }
    return str;
}

QString RawData::toString() const
{
    QString str;
    for (int i = 0; i < this->m_data->size()/8; i++)
    {
        str += static_cast<char>(this->m_data->operator[](i));
        str += " ";
    }
    return str;
}

qsizetype RawData::size() const
{
    return this->m_size;
}

unsigned char* RawData::data()
{
    return m_data->data();
}

RawData& RawData::operator<<(const RawData &other)
{
    this->m_size += other.m_size;
    this->m_data->append(*other.m_data);
    return *this;
}

RawData RawData::operator<<(const RawData& other) const
{
    RawData data(*this);
    data << other;
    return data;
}

RawData& RawData::operator=(const RawData &other)
{
    this->m_size = other.m_size;
    this->m_data = make_unique<QVector<quint8>>(QVector<quint8>(*other.m_data));
    return *this;
}
