#ifndef RAWDATA_H
#define RAWDATA_H

#include <QString>
#include <QVector>

using namespace std;

class RawData
{
public:
    RawData();
    RawData(const qsizetype size); // in bits
    RawData(const RawData& other);
    void clear();
    void resize(const qsizetype size); // in bits
    void flipBit(const qsizetype byteIndex, const qsizetype bitIndex);
    void setBit(const qsizetype byteIndex, const qsizetype bitIndex, const bool value);
    void setBit(const qsizetype bitIndex, const bool value);
    void setBits(const qsizetype byteIndex, const qsizetype bitIndex, const RawData& value);
    void setBits(const qsizetype bitIndex, const RawData& value);
    void setByte(const qsizetype byteIndex, const quint8 value);
    void setBytes(const qsizetype byteIndex, const RawData& value);
    void setBytes(const qsizetype byteIndex, const quint16 value);
    void setBytes(const qsizetype byteIndex, const quint32 value);
    void truncate(const qsizetype size); // in bits
    quint8 getByte(const qsizetype byteIndex) const;
    RawData getBytes(const qsizetype byteIndex, const qsizetype length) const;
    bool getBit(const qsizetype byteIndex, const qsizetype bitIndex) const;
    bool getBit(const qsizetype bitIndex) const;
    RawData getBits(const qsizetype byteIndex, const qsizetype bitIndex, const qsizetype length) const;
    RawData getBits(const qsizetype bitIndex, const qsizetype length) const;
    QString toString(int base) const;
    QString toString() const;
    qsizetype size() const; // in bits
    unsigned char *data();
    RawData& operator<<(const RawData& other);
    RawData operator<<(const RawData& other) const;
    RawData& operator<<(const quint8 value);
    RawData& operator<<(const quint16 value);
    RawData& operator<<(const quint32 value);
    RawData& operator=(const RawData& other);
    operator quint8() const;
    operator quint16() const;
    operator quint32() const;
private:
    qsizetype m_size{};
    unique_ptr<QVector<quint8>> m_data{};
};

#endif // RAWDATA_H
