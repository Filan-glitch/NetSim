#include "Headernotfoundexception.h"

HeaderNotFoundException::HeaderNotFoundException(const QString &errorMessage)
    {
    this->errorMessage = errorMessage;
    }

    QString HeaderNotFoundException::getErrorMessage() const{
        return this->errorMessage;
    }
