#ifndef HEADERATTRIBUTE_H
#define HEADERATTRIBUTE_H

#include <QString>
#include <QVector>

namespace NetSim {

class HeaderAttribute {
public:
  HeaderAttribute(const QString &name, quint32 sizeInBit, quint8 content);

  HeaderAttribute(const QString &name, quint32 sizeInBit, quint16 content);

  HeaderAttribute(const QString &name, quint32 sizeInBit, quint32 content);

  HeaderAttribute(const QString &name, quint32 sizeInBit, quint64 content);

  HeaderAttribute(const QString &name, quint32 sizeInBit,
                  const QVector<quint8> &content);

  HeaderAttribute(const QString &name, quint32 sizeInBit,
                  const QString &content);

  HeaderAttribute() = default;

  QString name() const;

  quint32 size() const;

  quint64 toInt() const;

  QVector<quint8> toArray() const;

  void setContent(QVector<quint8> content);

  quint64 getContentAsInt64(int size) const;

private:
  QString m_name{};

  quint32 m_sizeInBit{0};

  QVector<quint8> m_content{};
};
} // namespace NetSim

#endif // HEADERATTRIBUTE_H
