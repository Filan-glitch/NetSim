#include "headerattributenotfoundexception.h"

HeaderAttributeNotFoundException::HeaderAttributeNotFoundException(const QString &errorMessage)
{
    this->errorMessage = errorMessage;
}

QString HeaderAttributeNotFoundException::getErrorMessage() const {
    return errorMessage;
}
