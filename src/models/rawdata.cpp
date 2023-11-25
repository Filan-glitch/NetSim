#include "rawdata.h"

RawData::RawData()
{
    this->m_data = new QVector<quint8>();
}

RawData::RawData(const qsizetype size)
{
    this->m_data = new QVector<quint8>(size);
}

RawData::~RawData()
{
    delete this->m_data;
}

void RawData::clear()
{
    this->m_data->clear();
}

void RawData::resize(const qsizetype size)
{
    this->m_data->resize(size);
}

void RawData::flipBit(const qsizetype byteIndex, const qsizetype bitIndex)
{
    this->m_data->operator[](byteIndex) ^= 1 << bitIndex;
}

void RawData::setBit(const qsizetype byteIndex, const qsizetype bitIndex, const bool value)
{
    if (value)
    {
        this->m_data->operator[](byteIndex) |= 1 << bitIndex;
    }
    else
    {
        this->m_data->operator[](byteIndex) &= ~(1 << bitIndex);
    }
}

void RawData::setByte(const qsizetype byteIndex, const quint8 value)
{
    this->m_data->operator[](byteIndex) = value;
}

RawData& RawData::operator=(const RawData &other)
{
    this->m_data = other.m_data;
    return *this;
}

RawData& RawData::operator<<(const RawData &other)
{
    this->m_data->append(*other.m_data);
    return *this;
}
