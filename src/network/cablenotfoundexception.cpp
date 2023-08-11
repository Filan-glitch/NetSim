#include "cablenotfoundexception.h"

CableNotFoundException::CableNotFoundException(const QString &errorMessage) {
  this->m_errorMessage = errorMessage;
}

QString CableNotFoundException::errorMessage() const { return m_errorMessage; }
