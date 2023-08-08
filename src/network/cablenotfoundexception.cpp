#include "cablenotfoundexception.h"

CableNotFoundException::CableNotFoundException(const QString &errorMessage)
{
    this->errorMessage = errorMessage;
}

QString CableNotFoundException::getErrorMessage() const{
    return errorMessage;
}
