#include "header.h"
#include "src/protocols/headerattributenotfoundexception.h"

using namespace NetSim;

Header::Header(const HeaderType &headerType,
               const QBitArray &packageData, int offset)
    : m_headerType(headerType), m_headerList(QList<QBitArray>()) {
    //TODO: Daten extrahieren
}

void Header::addHeaderAttribute(const QBitArray &headerAttribute) {
  m_headerList.append(headerAttribute);
}

void Header::setHeaderType(const HeaderType &headerType) {
  this->m_headerType = headerType;
}

QList<QBitArray> Header::headerList() const { return m_headerList; }

HeaderType Header::type() const { return m_headerType; }

qsizetype Header::size() const {
  qsizetype length = 0;
  for (const QBitArray &attribute : m_headerList) {
    length += attribute.size();
  }
  return length / 8;
}

QBitArray &Header::operator[](int index) {
  if (index >= m_headerList.size()) {
    throw HeaderAttributeNotFoundException("Index out of bounds");
  }
  return m_headerList[index];
}

QBitArray Header::toData() const
{

}
