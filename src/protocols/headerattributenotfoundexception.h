#ifndef HEADERATTRIBUTENOTFOUNDEXCEPTION_H
#define HEADERATTRIBUTENOTFOUNDEXCEPTION_H

#include <QString>

namespace NetSim {
class HeaderAttributeNotFoundException;
}

class HeaderAttributeNotFoundException {
public:
  HeaderAttributeNotFoundException(const QString &errorMessage);

  QString errorMessage() const;

private:
  QString m_errorMessage;
};

#endif // HEADERATTRIBUTENOTFOUNDEXCEPTION_H
