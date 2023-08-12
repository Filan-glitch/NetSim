#include "headerAttribute.h"

using namespace NetSim;

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit,
                                 const QVector<quint8> &content)
    : m_name(name), m_sizeInBit(std::move(sizeInBit)), m_content(content) {}

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit,
                                 quint8 content)
    : m_name(name), m_sizeInBit(std::move(sizeInBit)) {
  this->m_content.append(content);
}

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit,
                                 quint16 content)
    : m_name(name), m_sizeInBit(std::move(sizeInBit)) {
  this->m_content.append(content >> 8);
  this->m_content.append(content & 0xFF);
}

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit,
                                 quint32 content)
    : m_name(name), m_sizeInBit(std::move(sizeInBit)) {
  this->m_content.append(content >> 24);
  this->m_content.append((content >> 16) & 0xFF);
  this->m_content.append((content >> 8) & 0xFF);
  this->m_content.append(content & 0xFF);
}

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit,
                                 quint64 content)
    : m_name(name), m_sizeInBit(std::move(sizeInBit)) {
  this->m_content.append(content >> 56);
  this->m_content.append((content >> 48) & 0xFF);
  this->m_content.append((content >> 40) & 0xFF);
  this->m_content.append((content >> 32) & 0xFF);
  this->m_content.append((content >> 24) & 0xFF);
  this->m_content.append((content >> 16) & 0xFF);
  this->m_content.append((content >> 8) & 0xFF);
  this->m_content.append(content & 0xFF);
}

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit,
                                 const QString &content)
    : m_name(name), m_sizeInBit(std::move(sizeInBit)) {
  for (auto i = 0; i < content.length(); i++) {
    this->m_content.append(content.at(i).toLatin1());
  }
}

QString HeaderAttribute::name() const { return this->m_name; }

quint32 HeaderAttribute::size() const { return this->m_sizeInBit; }

quint64 HeaderAttribute::toInt() const {
  quint64 returnInt = m_content[7];
  returnInt = (returnInt << 8) + m_content[6];
  returnInt = (returnInt << 8) + m_content[5];
  returnInt = (returnInt << 8) + m_content[4];
  returnInt = (returnInt << 8) + m_content[3];
  returnInt = (returnInt << 8) + m_content[2];
  returnInt = (returnInt << 8) + m_content[1];
  returnInt = (returnInt << 8) + m_content[0];
  return returnInt;
}

QVector<quint8> HeaderAttribute::toArray() const { return m_content; }

void HeaderAttribute::setContent(QVector<quint8> content) {
  this->m_content = content;
}
