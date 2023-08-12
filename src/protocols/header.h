#ifndef HEADER_H
#define HEADER_H

#include "headerAttribute.h"
#include <QDebug>
#include <QList>

namespace NetSim {
enum HeaderType { HTTP, DNS, TCP, UDP, IP, MAC, UNKNOWN };

class Header {
public:
  Header() = default;

  Header(const HeaderType &headerType,
         const QList<HeaderAttribute> &headerList);

  void addHeaderAttribute(const HeaderAttribute &headerAttribute);

  void setHeaderType(const HeaderType &headerType);

  QList<HeaderAttribute> headerList() const;

  HeaderType type() const;

  quint16 size() const;

  HeaderAttribute &operator[](const QString &name);

private:
  HeaderType m_headerType{HeaderType::UNKNOWN};
  QList<HeaderAttribute> m_headerList{};
};
} // namespace NetSim

#endif // HEADER_H
