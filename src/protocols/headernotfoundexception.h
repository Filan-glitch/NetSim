#ifndef HEADERNOTFOUNDEXCEPTION_H
#define HEADERNOTFOUNDEXCEPTION_H

#include <QString>

class HeaderNotFoundException
{
public:
    HeaderNotFoundException(const QString &errorMessage);

    QString getErrorMessage() const;

private:
    QString errorMessage;
};

#endif // HEADERNOTFOUNDEXCEPTION_H
