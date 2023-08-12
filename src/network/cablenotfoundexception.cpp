#include "cablenotfoundexception.h"

using namespace NetSim;

CableNotFoundException::CableNotFoundException(const QString &errorMessage) {
  this->m_errorMessage = errorMessage;
}

QString CableNotFoundException::errorMessage() const { return m_errorMessage; }
