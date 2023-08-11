#ifndef HEADER_H
#define HEADER_H

#include "headerAttribute.h"
#include <QDebug>
#include <QList>

namespace NetSim {
enum HeaderType { HTTP, DNS, TCP, UDP, IP, MAC, UNKNOWN };
class Header;
} // namespace NetSim

class Header {
public:
  Header();

  Header(const NetSim::HeaderType &headerType,
         const QList<HeaderAttribute> &headerList);

  void addHeaderAttribute(const HeaderAttribute &headerAttribute);

  void setHeaderType(const NetSim::HeaderType &headerType);

  QList<HeaderAttribute> headerList() const;

  NetSim::HeaderType type() const;

  quint16 size() const;

  HeaderAttribute &operator[](const QString &name);

private:
  NetSim::HeaderType m_headerType;
  QList<HeaderAttribute> m_headerList;
};

#endif // HEADER_H
