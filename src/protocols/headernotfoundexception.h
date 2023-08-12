#ifndef HEADERNOTFOUNDEXCEPTION_H
#define HEADERNOTFOUNDEXCEPTION_H

#include <QString>

namespace NetSim {

class HeaderNotFoundException {
public:
  HeaderNotFoundException(const QString &errorMessage);

  QString errorMessage() const;

private:
  QString m_errorMessage{};
};
} // namespace NetSim

#endif // HEADERNOTFOUNDEXCEPTION_H
