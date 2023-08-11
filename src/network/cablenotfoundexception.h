#ifndef CABLENOTFOUNDEXCEPTION_H
#define CABLENOTFOUNDEXCEPTION_H

#include <QString>

namespace NetSim {
class CableNotFoundException;
}

class CableNotFoundException {
public:
  CableNotFoundException(const QString &errorMessage);

  QString errorMessage() const;

private:
  QString m_errorMessage;
};

#endif // CABLENOTFOUNDEXCEPTION_H
