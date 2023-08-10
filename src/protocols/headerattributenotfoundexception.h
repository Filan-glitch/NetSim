#ifndef HEADERATTRIBUTENOTFOUNDEXCEPTION_H
#define HEADERATTRIBUTENOTFOUNDEXCEPTION_H

#include <QString>

class HeaderAttributeNotFoundException
{
public:
    HeaderAttributeNotFoundException(const QString &errorMessage);

    QString getErrorMessage() const;

private:
    QString errorMessage;
};

#endif // HEADERATTRIBUTENOTFOUNDEXCEPTION_H
