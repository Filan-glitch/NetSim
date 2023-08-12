#ifndef HEADERATTRIBUTENOTFOUNDEXCEPTION_H
#define HEADERATTRIBUTENOTFOUNDEXCEPTION_H

#include <QString>

namespace NetSim {

class HeaderAttributeNotFoundException {
public:
  HeaderAttributeNotFoundException(const QString &errorMessage);

  QString errorMessage() const;

private:
  QString m_errorMessage{};
};
} // namespace NetSim

#endif // HEADERATTRIBUTENOTFOUNDEXCEPTION_H
