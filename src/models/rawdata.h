#ifndef RAWDATA_H
#define RAWDATA_H

#include <QVector>
#include <QString>

using namespace std;

class RawData
{
public:
    RawData();
    RawData(const qsizetype size);
    RawData(const RawData& other);
    void clear();
    void resize(const qsizetype size);
    void flipBit(const qsizetype byteIndex, const qsizetype bitIndex);
    void setBit(const qsizetype byteIndex, const qsizetype bitIndex, const bool value);
    void setBit(const qsizetype bitIndex, const bool value);
    void setBits(const qsizetype byteIndex, const qsizetype bitIndex, const RawData& value);
    void setBits(const qsizetype bitIndex, const RawData& value);
    void setByte(const qsizetype byteIndex, const quint8 value);
    void setBytes(const qsizetype byteIndex, const RawData& value);
    quint8 getByte(const qsizetype byteIndex) const;
    RawData getBytes(const qsizetype byteIndex, const qsizetype length) const;
    bool getBit(const qsizetype byteIndex, const qsizetype bitIndex) const;
    bool getBit(const qsizetype bitIndex) const;
    QString toString(int base) const;
    QString toString() const;
    qsizetype size() const; // in bits
    unsigned char *data();
    RawData& operator<<(const RawData& other);
    RawData& operator=(const RawData& other);
private:
    qsizetype m_size{};
    unique_ptr<QVector<quint8>> m_data{};
};

#endif // RAWDATA_H
