#ifndef RAWDATA_H
#define RAWDATA_H

#include <QVector>
#include <QString>

class RawData
{
public:
    RawData();
    RawData(const qsizetype size);
    ~RawData();
    void clear();
    void resize(const qsizetype size);
    void flipBit(const qsizetype byteIndex, const qsizetype bitIndex);
    void setBit(const qsizetype byteIndex, const qsizetype bitIndex, const bool value);
    void setByte(const qsizetype byteIndex, const quint8 value);
    quint8 getByte(const qsizetype byteIndex) const;
    bool getBit(const qsizetype byteIndex, const qsizetype bitIndex) const;
    QString toString() const;
    RawData& operator=(const RawData& other);
    RawData& operator<<(const RawData& other);

private:
    QVector<quint8>* m_data{};
};

#endif // RAWDATA_H
