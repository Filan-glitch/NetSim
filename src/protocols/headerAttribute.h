#ifndef HEADERATTRIBUTE_H
#define HEADERATTRIBUTE_H

#include <QString>
#include <QVector>

class HeaderAttribute
{
public:
    HeaderAttribute(const QString &name, quint32 sizeInBit, quint8 content);

    HeaderAttribute(const QString &name, quint32 sizeInBit, quint16 content);

    HeaderAttribute(const QString &name, quint32 sizeInBit, quint32 content);

    HeaderAttribute(const QString &name, quint32 sizeInBit, quint64 content);

    HeaderAttribute(const QString &name, quint32 sizeInBit, const QVector<quint8> &content);

    HeaderAttribute(const QString &name, quint32 sizeInBit, const QString &content);

    HeaderAttribute();

    QString getName() const;

    quint32 getSizeInBit() const;

    quint64 getContentAsInt() const;

    QVector<quint8> getContentAsArray() const;

    void setContent(QVector<quint8> content);

    quint64 getContentAsInt64(int size) const;

private:
    QString name;

    quint32 sizeInBit;

    QVector<quint8> content;
};

#endif // HEADERATTRIBUTE_H
