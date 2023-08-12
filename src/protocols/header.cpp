#include "header.h"
#include "src/protocols/headerattributenotfoundexception.h"

using namespace NetSim;

Header::Header(const HeaderType &headerType,
               const QList<HeaderAttribute> &headerList)
    : m_headerType(headerType), m_headerList(headerList) {}

void Header::addHeaderAttribute(const HeaderAttribute &headerAttribute) {
  m_headerList.append(headerAttribute);
}

void Header::setHeaderType(const HeaderType &headerType) {
  this->m_headerType = headerType;
}

QList<HeaderAttribute> Header::headerList() const { return m_headerList; }

HeaderType Header::type() const { return m_headerType; }

quint16 Header::size() const {
  quint16 length = 0;
  for (const HeaderAttribute &headerAttribute : m_headerList) {
    length += headerAttribute.size();
  }
  return length / 8;
}

HeaderAttribute &Header::operator[](const QString &name) {
  for (int i = 0; i < m_headerList.size(); i++) {
    if (m_headerList.at(i).name() == name) {
      return m_headerList[i];
    }
  }
  qDebug() << "HeaderAttribute not found: " << name;
  throw HeaderAttributeNotFoundException(name);
}
