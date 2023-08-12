#include "headerattributenotfoundexception.h"

using namespace NetSim;

HeaderAttributeNotFoundException::HeaderAttributeNotFoundException(
    const QString &errorMessage) {
  this->m_errorMessage = errorMessage;
}

QString HeaderAttributeNotFoundException::errorMessage() const {
  return m_errorMessage;
}
